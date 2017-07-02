// Módulo de avaliações

/**
 * @file avaliacao.c
 * @brief Implementação do módulo de avaliações
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "usuarios.h"
#include "avaliacao.h"

/*!
 * @brief Identificador máximo já atribuido a uma avaliação
*/
static unsigned int avaliacao_contador = 0;

/*!
 * @brief Função DEPRECATED, o carregamento do contador ocorre automaticamente na realização de avaliações
*/
avaliacao_condRet avaliacao_pegarContador(){
  return AVALIACAO_SUCESSO;
}

/*!
 * @fn avaliacao_condRet avaliacao_atualizarContador()
 * @brief Função que atualiza o contador de avaliações e cria o banco de dados caso não exista
 * @return Retorna uma instância avaliacao_condRet que assume:
 *  - AVALIACAO_FALHA_CRIARDB se não conseguir criar um banco de dados;
 *  - AVALIACAO_SUCESSO se conseguir criar ou atualizar o contador no arquivo e na variável global estática avaliacao_contador
 *
 * Assertivas de entrada:
 *  - Há permissões para escrever e atualizar no arquivo de avaliações definido em avaliacoes.h
 *
 * Assertivas de saída:
 *  - Haverá um arquivo de avaliações
 *  - O início do arquivo conterá o contador de avaliações atualizado
 *  - O contador global do módulo será atualizado
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - O valor do contador global será acrescido de 1
 *
 * Requisitos:
 *  - stdio.h
 *
 * Hipóteses:
 *  - Nenhuma
 */

static avaliacao_condRet avaliacao_atualizarContador() {
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
 * @fn avaliacao *avaliacao_iniciar()
 * @brief Função que inicia uma avaliação
 * @return Retorna o endereço de uma avaliação alocada dinamicamente
 *
 * Inicialmente todos os valores da transação são 0
 *
 * @code
 * avaliacao *a = avaliacao_iniciar();
 * @code
 *
 * Assertivas de entrada:
 *  - Há memória suficiente
 *
 * Assertivas de saída:
 *  - Alocará memória para uma avaliação e retornará o ponteiro por valor
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - stdlib.h
 *
 * Hipóteses:
 *  - Nenhuma.
 *
 */

avaliacao *avaliacao_iniciar(){
  avaliacao *novo = (avaliacao *)calloc(1, sizeof(avaliacao));
  novo->identificador = avaliacao_contador;
  return novo;
}

/*!
 * @fn avaliacao_condRet avaliacao_limpar(avaliacao **dado)
 * @brief Função que limpa uma avaliação
 * @param dado Ponteiro para o ponteiro da avaliação
 * @return Instância avaliacao_condRet que retornará AVALIACAO_SUCESSO
 *
 * É usado para desalocar memória de uma avaliação:
 * @code
 * avaliacao *a = avaliacao_iniciar();
 * //...
 * avaliacao_limpar(&a);
 * @endcode
 *
 * Assertivas de entrada:
 *  - dado é diferente de NULL
 *
 * Assertivas de saída:
 *  - o conteúdo de dado será NULL
 *  - Memória ocupado pelo conteúdo de dado será desalocada
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - o conteúdo de dado será NULL e a memória apontada por esse conteúdo será desalocada.
 *
 * Requisitos:
 *  - stdlib.h
 *
 * Hipóteses:
 *  - dado é diferente de NULL
 *
 */

avaliacao_condRet avaliacao_limpar(avaliacao **dado){
  free(*dado);
  *dado = NULL;
  return AVALIACAO_SUCESSO; 
}

/*!
 * @fn avaliacao_condRet avaliacao_definir(avaliacao *retorno, const char *nome, ...)
 * @brief Função que atribui dados a avaliação
 * @param retorno Endereço da avaliação a definir um valor
 * @param nome Argumento válido que identificará o que definir: "avaliador", "avaliado", "nota", "comentario"
 * @param (...) Um argumento dos tipos unsigned int ou char * É o valor a se definir na avaliação
 * @return Retorna uma instância avaliacao_condRet que assume AVALIACAO_SUCESSO.
 *
 * Exemplo de uso:
 * @code
 * avaliacao *a = avaliacao_iniciar();
 * avaliacao_definir(a, "avaliador", 5);
 * avaliacao_definir(a, "avaliado", 6);
 * avaliacao_definir(a, "nota", 2);
 * avaliacao_definir(a, "comentario", (char *)"Muito bom!");
 * avaliacao_limpar(&a);
 * @endcode
 *
 * Assertivas de entrada:
 *  - É passado exatamente um argumento na elípse do tipo unsigned int ou char *
 *  - O nome passado é algum desses: "avaliador", "avaliado", "nota", "comentario"
 *  - retorno não é NULL
 * 
 * Assertivas de saída:
 *  - O argumento na elipse de dado passado passa a definir um valor na avaliação
 *
 * Assertivas estruturais:
 *  - As strings passadas na elipse terminam com '\0'
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Resquisitos:
 *  - string.h, stdarg.h
 *
 * Hipóteses:
 *  - retorno não é NULL
 *  - Há exatamente 1 argumento em (...) do tipo especificado
 * 
 */

avaliacao_condRet avaliacao_definir(avaliacao *retorno, const char *nome, ...) {
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
 * @fn avaliacao_condRet avaliacao_obterAvaliacao(unsigned int identificador, unsigned int n, avaliacao_tipo tipo, avaliacao *retorno)
 * @brief Função que busca a n-ésima avaliação de um usuário
 * @param identificador Id de um usuário, se for 0 usa a sessão (Se usar a sessão o módulo de usuários deve ter sido carregado!)
 * @param n n-ésima avaliação do usuário a ler
 * @param tipo O tipo da avaliação podendo ser AVALIADOR ou AVALIADO, se for AVALIADOR busca as avaliações em que o identificador é o avaliador se for AVALIADO busca as avaliações em que identificador é avaliado.
 * @param retorno Retorno da avaliação pretendida por referência, já deve estar alocado anteriormente a execução da função
 * @return Instância avaliacao_condRet que assume: 
 *  - AVALIACAO_VALORINVALIDO se n=0;
 *  - AVALIACAO_FALHA_SEMSESSAO se não houver sessão aberta;
 *  - AVALIACAO_FALHA_USUARIOS se não conseguir obter o id do usuário na sessão;
 *  - AVALIACAO_FALHA_ABRIRDB se não consegue abrir para leitura "r" o arquivo de avaliações;
 *  - AVALIACAO_NAO_ENCONTRADO se não encontrou uma avaliação com esse valor de n;
 *  - AVALIACAO_SUCESSO se encontrou uma avaliação e a copiou para retorno com sucesso
 * 
 * Recebe o id do usuário, se receber 0 trabalha com a sessão
 *
 * Recebe a posição da avaliação a ser lida
 * 
 * Recebe AVALIADOR ou AVALIADO para listar as avaliações em que o usuário avaliou ou as que ele foi avaliado
 * 
 * Retorna por referência uma avaliação
 *
 * Assertivas de entrada:
 *  - n é diferente de 0 e há pelo menos n avaliações referentes ao usuário identificado com o tipo passado
 *  - retorno já está alocado
 *
 * Assertivas de saída
 *  - retorno conterá n-ésima a avaliação
 *  - O arquivo de dados não é alterado
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - Se as condições forem satisfeitas o retorno terá a n-ésima avaliação
 *
 * Requisitos:
 *  - stdio.h, usuarios.h
 *
 * Hipóteses:
 *  - Há memória alocada para o retorno
 */
 
avaliacao_condRet avaliacao_obterAvaliacao(unsigned int identificador, unsigned int n, avaliacao_tipo tipo, avaliacao *retorno) {
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
  
  if(i == n) return AVALIACAO_SUCESSO;
  else return AVALIACAO_NAO_ENCONTRADO;
}

/*!
 * @fn avaliacao_condRet avaliacao_fazerAvaliacao(avaliacao *dados)
 * @param dados Avaliação de onde sairão os dados a serem gravados em disco
 * @brief Adiciona uma avaliação ao arquivo de dados a partir de do tipo avaliacao
 * @return Instância do tipo avaliacao_condRet que assume:
 *  - AVALIACAO_FALHA_AUTOAVALIACAO se os ids de avaliador e avaliados forem os mesmos
 *  - AVALIACAO_FALHA_NOTAINVALIDA se a nota passada for maior que 5
 *  - AVALIACAO_FALHA_USUARIOS se não conseguir obter os dados no grafo de usuários do avaliado referentes ao número de avaliações e à avaliação. Também retorna esse erro se não conseguir atualizar no grafo de usuários e consequentemente no arquivo de dados dos usuários
 *  - AVALIACAO_FALHA_CRIARDB se não conseguir criar/acessar o banco de dados de avaliações com permissão "a+"
 *  - AVALIACAO_SUCESSO se tiver salvo a avaliação no arquivo de dados com sucesso e atualizado os parâmetros nas configurações do usuário avaliado.
 *
 * Modo de uso:
 * @code
 * avaliacao_fazerAvaliacao(avaliacao);
 * @endcode
 *
 * Assertivas de entrada:
 *  - dados é não nulo
 *  - avaliador e avaliado são distintos
 *  - nota pertence a {0,1,2,3,4,5}
 *  - Programa tem acesso "a+" ao arquivo de dados de avaliações
 *  - Módulo de usuários foi carregado com a função usuarios_carregarArquivo
 *
 * Assertivas de saída:
 *  - Os dados da avaliação estarão no arquivo de avaliações
 *
 * Assertivas estruturais:
 *  - O comentário termina com um '\0'
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - usuarios.h, stdio.h 
 *
 * Hipóteses:
 *  - dados é diferente de NULL
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
 * @fn avaliacao_condRet avaliacao_avaliar(unsigned int avaliador, unsigned int avaliado, unsigned int nota, char *comentario)
 * @brief Função que cria uma avaliação e já avalia
 * @param avaliador identificador do avaliador, se for 0 usa a sessão (precisa do módulo de usuários carregado)
 * @param avaliado identificador do avaliado
 * @param nota Nota do avaliador ao avaliado, deve pertencer ao conjunto {0,1,2,3,4,5}
 * @param comentario comentário que não exceda o limite de AVALIACAO_LIMITE_COMENTARIO-1 caracteres
 * @retorno Retorna uma instância avaliacao_condRet que assume:
 *  - AVALIACAO_FALHA_SEMSESSAO, se avaliador for 0 e não houver sessão
 *  - AVALIACAO_FALHA_USUARIOS se não conseguir obter o id da sessão
 *  - AVALIACAO_FALHA_DEFINIR se não conseguir definir algum dos parâmetros em uma avaliação local da função
 *  - AVALIACAO_FALHA_AVALIAR se não conseguir realizar a avaliação
 *  - AVALIACAO_FALHA_FREE se não conseguir liberar o espaço alocado dinamicamente dentro da função
 *  - AVALIACAO_SUCESSO se conseguir avaliar atualizando no grafo de usuários e no arquivo de avaliações e de usuários
 *
 * Recebe como parâmetros o id do avaliador, id do avaliado, a nota e um comentário
 *
 * Se avaliador for zero usa o id da sessão
 * Alternativa simples ao uso de avaliacao_fazerAvaliacao
 *
 * Assertivas de entrada:
 *  - O grafo de usuários foi carregado
 *  - avaliador, avaliado pertencem ao grafo
 *  - nota pertence ao conjunto {0,1,2,3,4,5}
 *  - comentario não ultrapassa o limite de AVALIACAO_LIMITE_COMENTARIO-1 caracteres
 *
 * Assertivas de saída:
 *  - O arquivo de avaliação é atualizado com o contador e a nova avaliação
 *  - O arquivo de usuários é atualizado com o novo valor médio de avaliação para o usuário avaliado
 *  - O grafo de usuários é atualizado com o novo valor médio de avaliação para o usuário avaliado
 *
 * Assertivas estruturais:
 *  - Nenhuma
 * 
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - usuarios.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
 */
 
avaliacao_condRet avaliacao_avaliar(unsigned int avaliador, unsigned int avaliado, unsigned int nota, char *comentario) {
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
