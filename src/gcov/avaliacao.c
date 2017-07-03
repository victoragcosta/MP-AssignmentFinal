#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "avaliacao.h"
#include "usuarios.h"

/*!
 * @brief Identificador máximo já atribuido a uma avaliação
*/
static unsigned int avaliacao_contador = 0;

/*!
 * @brief Função que atualiza o contador de avaliações e cria o banco de dados caso não exista
*/
avaliacao_condRet avaliacao_atualizarContador(){
  FILE *db_avaliacao;
  db_avaliacao = fopen(AVALIACAO_DB, "r+");
  if(db_avaliacao == NULL) {
    db_avaliacao = fopen(AVALIACAO_DB, "w");
    if(db_avaliacao == NULL) return AVALIACAO_FALHA_CRIARDB;
  }
  fprintf(db_avaliacao, "%-4u\n", ++avaliacao_contador);
  fclose(db_avaliacao);
  return AVALIACAO_SUCESSO;
}

/*!
 * @brief Função que lê o contador de avaliações
*/
avaliacao_condRet avaliacao_pegarContador(){
  FILE *db_avaliacao;
  db_avaliacao = fopen(AVALIACAO_DB, "r");
  if(db_avaliacao == NULL) return AVALIACAO_FALHA_ABRIRDB;
  fscanf(db_avaliacao, "%4u\n", &avaliacao_contador);
  fclose(db_avaliacao);
  return AVALIACAO_SUCESSO;
}

/*!
 * @brief Função que inicia uma avaliação
*/
avaliacao *avaliacao_iniciar(){
  avaliacao *novo = (avaliacao *)calloc(1, sizeof(avaliacao));
  novo->identificador = avaliacao_contador;
  return novo;
}

/*!
 * @brief Função que limpa uma avaliação
*/
avaliacao_condRet avaliacao_limpar(avaliacao **dado){
  free(*dado);
  *dado = NULL;
  return AVALIACAO_SUCESSO;
}

/*!
 * @brief Função que atribui dados a transação
*/
avaliacao_condRet avaliacao_definir(avaliacao *retorno, const char *nome, ...){
  /* Lista de argumentos */
  va_list arg;
  va_start(arg, nome);

  /* Comparamos o nome com os valores possíveis */
  if(!strcmp("avaliador", nome)) retorno->avaliador = va_arg(arg, unsigned int);
  else if(!strcmp("avaliado", nome)) retorno->avaliado = va_arg(arg, unsigned int);
  else if(!strcmp("nota", nome)) retorno->nota = va_arg(arg, unsigned int);
  else if(!strcmp("comentario", nome)) strncpy(retorno->comentario, va_arg(arg, char *), AVALIACAO_LIMITE_COMENTARIO);

  va_end(arg);

  return AVALIACAO_SUCESSO;
}

/*!
 * @brief Função que busca a n-ésima avaliação de um usuário
 *
 * Recebe o id do usuário, se receber 0 trabalha com a sessão
 *
 * Recebe a posição da avaliação a ser lida
 *
 * Recebe AVALIADOR ou AVALIADO para listar as avaliações em que o
 * usuário avaliou ou as que ele foi avaliado
 *
 * Retorna por referência uma avaliação
*/
avaliacao_condRet avaliacao_obterAvaliacao(unsigned int identificador, unsigned int n, avaliacao_tipo tipo, avaliacao *retorno){
  unsigned int i=0;
  FILE *db_avaliacao;

  /* Verificamos se o valor passado é correto */
  if(n == 0) return AVALIACAO_VALORINVALIDO;

  /* Se avaliador for 0 pegamos a sessão */
  if(identificador == 0){
    if(!usuarios_sessaoAberta()) return AVALIACAO_FALHA_SEMSESSAO;
    if(usuarios_retornaDados(0, "identificador", &identificador) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  }

  db_avaliacao = fopen(AVALIACAO_DB, "r");
  if(db_avaliacao == NULL) return AVALIACAO_FALHA_ABRIRDB;
  fseek(db_avaliacao, 5, SEEK_SET);


  /* Buscamos no arquivo */
  avaliacao *corrente = (avaliacao *)malloc(sizeof(avaliacao));
  while(!feof(db_avaliacao)){

    /* Lê-se uma linha de dados */
    fscanf(db_avaliacao, "%4u\t%4u\t%4u\t%199[^\n]\n", &corrente->avaliador, &corrente->avaliado, &corrente->nota, corrente->comentario);


    if(tipo == AVALIADO && corrente->avaliado == identificador) i++;
    else if(tipo == AVALIADOR && corrente->avaliador == identificador) i++;

    /* Achamos a n-esima avaliação */
    if(i == n) {
      /* Devemos retirar os espaços finais de corrente->comentario */
      unsigned int j = 198;
      while(corrente->comentario[j] == ' ' && j) corrente->comentario[j--] = '\0';
      memcpy(retorno, corrente, sizeof(avaliacao));
      break;
    }
  }

  free(corrente);
  fclose(db_avaliacao);
  return AVALIACAO_SUCESSO;
}

/*!
 * @brief Função que avalia um usuário
 *
 * Modo de uso:
 * @code
 * avaliacao_fazerAvaliacao(avaliacao);
 * @endcode
 *
*/
avaliacao_condRet avaliacao_fazerAvaliacao(avaliacao *dados) {
  unsigned int n_avaliacao;
  double avaliacao;
  FILE *db_avaliacao;

  /* Evitamos autoavaliação */
  if(dados->avaliador == dados->avaliado) return AVALIACAO_FALHA_AUTOAVALIACAO;

  /* Verificamos o intervalo da nota */
  if(dados->nota > 5) return AVALIACAO_FALHA_NOTAINVALIDA;

  /* Obtemos os dados iniciais */
  if(usuarios_retornaDados(dados->avaliado, "n_avaliacao", (void *)&n_avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  if(usuarios_retornaDados(dados->avaliado, "avaliacao", (void *)&avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;

  /* Calculamos a nova avaliação e atualizamos no grafo de usuários */
  avaliacao = (double)(n_avaliacao*avaliacao+dados->nota)/(++n_avaliacao);
  if(usuarios_atualizarDados(dados->avaliado, "n_avaliacao", n_avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  if(usuarios_atualizarDados(dados->avaliado, "avaliacao", avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  
  /* Atualizamos o contador de avaliações */
  avaliacao_atualizarContador();

  /* Salvamos no banco de dados, cria-se um caso não haja */
  db_avaliacao = fopen(AVALIACAO_DB, "a+");
  if(db_avaliacao == NULL) return AVALIACAO_FALHA_CRIARDB;

  fprintf(db_avaliacao, AVALIACAO_DB_ESTRUTURA, dados->avaliador, dados->avaliado, dados->nota, dados->comentario);

  fclose(db_avaliacao);

  return AVALIACAO_SUCESSO;

}

/*!
 * @brief Função que cria uma avaliação e já avalia
 *
 * Recebe como parâmetros o id do avaliador, id do avaliado, a nota e um comentário
 *
 * Se avaliador for zero usa o id da sessão
*/
avaliacao_condRet avaliacao_avaliar(unsigned int avaliador, unsigned int avaliado, unsigned int nota, char *comentario){
  avaliacao *a;

  /* Se avaliador for 0 pegamos a sessão */
  if(avaliador == 0){
    if(!usuarios_sessaoAberta()) return AVALIACAO_FALHA_SEMSESSAO;
    if(usuarios_retornaDados(0, "identificador", &avaliador) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  }

  /* Compomos a avaliação */
  a = avaliacao_iniciar();

  if(avaliacao_definir(a, "avaliador", avaliador) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_DEFINIR;
  if(avaliacao_definir(a, "avaliado", avaliado) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_DEFINIR;
  if(avaliacao_definir(a, "nota", nota) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_DEFINIR;
  if(avaliacao_definir(a, "comentario", comentario) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_DEFINIR;

  /* Enviamos */
  if(avaliacao_fazerAvaliacao(a) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_AVALIAR;
  if(avaliacao_limpar(&a) != AVALIACAO_SUCESSO) return AVALIACAO_FALHA_FREE;

  return AVALIACAO_SUCESSO;
}
