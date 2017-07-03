#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../include/aleatorio.h"
#include "../include/grafo.h"
#include "../include/usuarios.h"

/*!
 * @brief Grafo de usuários
*/
static grafo *usuarios_grafo = NULL; 

/*!
 * @brief Contador do número de usuários no grafo
*/
static unsigned int usuarios_contador = 0;

/*!
 * @brief Contador do número de relações entre os nodos
*/
static int usuarios_contador_amizades = 0;

/*!
 * @brief Sessão aberta
*/
static tpUsuario *usuarios_sessao = NULL; /* Inicialmente NULL significa que não há usuário logado */

/*!
 * @brief Estrutura de usuário temporário para uso do usuarios_args nas funções
*/
static tpUsuario usuarios_dadosTemp;

/*!
 * @brief Argumentos padrão aceitáveis pelas funções ao buscar/alterar/definir dados de usuário
*/
static unsigned int usuarios_cadastro_argumentos_n = 5;

/*!
 * @brief Usado para detecção de argumentos válidos
*/
static usuarios_cadastro_argumentos usuarios_args[] = {
  {.validos = "usuario", .tamanho = USUARIOS_LIMITE_USUARIO, .destino = usuarios_dadosTemp.usuario},
  {.validos = "nome", .tamanho = USUARIOS_LIMITE_NOME, .destino = usuarios_dadosTemp.nome},
  {.validos = "email", .tamanho = USUARIOS_LIMITE_EMAIL, .destino = usuarios_dadosTemp.email},
  {.validos = "senha", .tamanho = USUARIOS_LIMITE_SENHA, .destino = usuarios_dadosTemp.senha},
  {.validos = "endereco", .tamanho = USUARIOS_LIMITE_ENDERECO, .destino = usuarios_dadosTemp.endereco}
};


/*!
 * @brief Função que retorna o identificador máximo de usuário do programa
 * 
 * Serve para mostrar os usuários do programa pois o identificador é 
 * único e ordenado de 1,2,3,...,max
 *
 * Para mostrar mais dados basta rodar a função usuarios_retornaDados
*/

int usuarios_max(){
  return usuarios_contador;
}

/*!
 * @brief Função que verifica se há repetição nos dados
 * 
 * A função busca no grafo de usuários se já há algum usuário com o dado
 * igual ao do argumento passado
 * 
 * @code
 * usuarios_verificaRepeticao("nome", "João Antônio");
 * @endcode
 * Vai retornar USUARIOS_DADOS_REPETICAO caso já haja um usuário com este nome
 * e USUARIOS_DADOS_OK caso contrário.
 *
 * Observação, a verificação de nome ignora se o caracter é caixa alta ou não
*/
static usuarios_condRet usuarios_verificaRepeticao(const char *argumento, char *dado){
  grafo_no *nodo;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Selecionamos o argumento passado */
  if(!strcmp(argumento, "usuario")) {
  
    /* Primeiro usuário */
    nodo = (grafo_no *)grafo_busca_no(usuarios_grafo, 1, 0);
    
    /* Percorremos o grafo */
    for(; nodo != NULL ; nodo = (grafo_no *)nodo->prox_no) {
    
      if(nodo->dados == NULL) return USUARIOS_GRAFO_CORROMPIDO; /* Asertiva */
              
      /* São iguais */ 
      if(!strcmp(((tpUsuario *)nodo->dados)->usuario, dado)) return USUARIOS_DADOS_REPETICAO;
    }
    
    return USUARIOS_DADOS_OK;
  }
  else if(!strcmp(argumento, "email")) {
  
    /* Primeiro usuário */
    nodo = (grafo_no *)grafo_busca_no(usuarios_grafo, 1, 0);
    
    /* Percorremos o grafo */
    for(; nodo != NULL ; nodo = (grafo_no *)nodo->prox_no) {
      if(nodo->dados == NULL) return USUARIOS_GRAFO_CORROMPIDO; /* Asertiva */
              
      /* São iguais */ 
      if(!strcmp(((tpUsuario *)nodo->dados)->email, dado)) return USUARIOS_DADOS_REPETICAO;
    }
    
    return USUARIOS_DADOS_OK;
  }
  
  return USUARIOS_ARGUMENTOINVALIDO;
}

/*!
 * @brief Condição de parada para usuario e senha corretos do login, usado em usuarios_busca
*/
static int usuarios_condParada_login(tpUsuario *corrente, va_list argumentos){
  return !strcmp(corrente->usuario, va_arg(argumentos, char *)) && !strcmp(corrente->senha, va_arg(argumentos, char *));
}

/*!
 * @brief Função de busca no grafo de usuários dada uma condição de parada condParada
 * 
 * Recebe uma função de condição de parada, e retorna por referência os dados de usuário e o índice no grafo (identificador)
 * Recebe uma lista de argumentos depois disso exigidos pela função de condição de parada passados
 * É uma função estática do módulo
 * 
 * @code
 * usuarios_busca(usuarios_condParada_login, &retorno, NULL, "joão", "123456");
 * @endcode
 * 
 * Este exemplo encontra no grafo um usuário joão de senha 123456 e retorna por referência a retorno.
 * Retorna por valor a condição de retorno, se for USUARIOS_SUCESSO, significa que a atribuição a retorno foi 
 * feita com sucesso. Se não encontrar retorna USUARIOS_FALHA_DADOSINCORRETOS. É uma função estática do módulo
*/
static usuarios_condRet usuarios_busca(int condParada(tpUsuario *, va_list), tpUsuario **retorno, unsigned int *indice, ...){
  unsigned int i = 0;
  tpUsuario *corrente;
  grafo_no *nodo;
  
  va_list argumentos, passado;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  va_start(argumentos, indice);
  
  /* Primeiro usuário */
  nodo = (grafo_no *)grafo_busca_no(usuarios_grafo, 1, 0);
  
  /* Percorremos o grafo */
  for(; nodo != NULL ; nodo = (grafo_no *)nodo->prox_no) {
    corrente = (tpUsuario *)nodo->dados;
    /* Assertiva */
    if(corrente == NULL) {
      va_end(argumentos);
      return USUARIOS_GRAFO_CORROMPIDO;
    }
    va_copy(passado, argumentos);
    if(condParada(corrente, passado)){
      va_end(passado);
      if(retorno != NULL) *retorno = corrente;
      if(indice != NULL) *indice = i;
      return USUARIOS_SUCESSO;
    }
    va_end(passado);
  }
  
  va_end(argumentos);
  return USUARIOS_FALHA_DADOSINCORRETOS;
}

/*!
 * @brief Função leitora de string em um arquivo de dados
 * 
 * Lê uma string do arquivo e salva em dstStr previamente alocada,
 * recebe um limite de gravação. É uma função estática
*/
static void usuarios_lerString(FILE *arquivo, char *dstStr, unsigned int limite){
  unsigned int i = 0, espaco = 0;
  char caracter;
  
  while (
    !feof(arquivo) && \
    (caracter = fgetc(arquivo)) != '\t' && \
    caracter != '\n' && \
    i < limite
  ) {
    /* Controle para evitar strings cheias de espaços no final */
    if(caracter != ' ') espaco = i; 
    dstStr[i++] = caracter;
  }
    
  dstStr[espaco+1] = '\0';
  
  /* Se o próximo não for \t ou \n voltamos um byte */
  if((caracter = fgetc(arquivo)) != '\t' && caracter != '\n')
    fseek(arquivo, -1, SEEK_CUR);
  
}

/*!
 * @brief Função carregadora do arquivo 
 * de usuários e suas relações
 *
 * A relação de um usuário com o outro é a relação de amizade, 
 * o grafo é direcionado, assim a relação entre A e B 
 * de fato existe se e só se existir uma aresta
 * indo de A a B e outra indo de B a A.
 * Se isso não ocorrer temos a pendencia de uma relação, na qual
 * aguarda-se a confirmação da parte solicitada para criá-la.
 * 
 * Retorna USUARIOS_SUCESSO caso tenha carregado o arquivo corretamente e gerado o grafo de usuário.
 * Deve ser a primeira função a ser carregada para que o módulo funcione.
*/

usuarios_condRet usuarios_carregarArquivo(){
  FILE *db_usuarios = fopen(USUARIOS_DB, "r");
  FILE *db_amigos;
    
  /* Cria-se o grafo de usuários */
  usuarios_grafo = cria_grafo("Usuários");
  
  /* Verificamos se o arquivo existe */
  if(db_usuarios == NULL){
    db_usuarios = fopen(USUARIOS_DB, "w");
    fclose(db_usuarios);
    return USUARIOS_SUCESSO;
  }
  
  /* Índice dos usuários carregados (para acesso via funções de grafo) */
  int i = 1;
  
  /* Identificadores para os amigos */
  unsigned int identificador_A, identificador_B;
  int valorAresta;
  
  usuarios_condRet busca;

  
  while(!feof(db_usuarios)){
    /* Dados do usuário corrente */
    tpUsuario *corrente = (tpUsuario *)malloc(sizeof(tpUsuario));
    
    /* Lemos do arquivo */
    fscanf(db_usuarios, "%u%*[^\t]\t", &(corrente->identificador));
    if(corrente->identificador == 0) break;
    
    
    /*fscanf(db_usuarios, "%4u %20[^\t] %40[^\t]\t%30[^\t]\t%20[^\t]\t%40[^\t]\t%4d%*c%4d%*c%4d%*c%9lf%*c%4u%*c%4u\n", 
      &(corrente->identificador),
      corrente->usuario,
      corrente->nome,
      corrente->email,
      corrente->senha,
      corrente->endereco,
      (int *)&(corrente->formaPagamento),
      (int *)&(corrente->tipo),
      (int *)&(corrente->estado),
      &(corrente->avaliacao),
      &(corrente->n_avaliacao),
      &(corrente->n_reclamacoes)
    );*/
    
    if(corrente->identificador == 0) break;
    
    usuarios_lerString(db_usuarios, corrente->usuario, USUARIOS_LIMITE_USUARIO);
    usuarios_lerString(db_usuarios, corrente->nome, USUARIOS_LIMITE_NOME);
    usuarios_lerString(db_usuarios, corrente->email, USUARIOS_LIMITE_EMAIL);
    usuarios_lerString(db_usuarios, corrente->senha, USUARIOS_LIMITE_SENHA);
    usuarios_lerString(db_usuarios, corrente->endereco, USUARIOS_LIMITE_ENDERECO);
    
    fscanf(db_usuarios, "%d%*[^\t]\t%d%*[^\t]\t%d%*[^\t]\t%lf%*[^\t]\t%u%*[^\t]\t%u%*[^\n]\n", 
      (int *)&(corrente->formaPagamento),
      (int *)&(corrente->tipo),
      (int *)&(corrente->estado),
      &(corrente->avaliacao),
      &(corrente->n_avaliacao),
      &(corrente->n_reclamacoes)
    );
    
    /*printf("%u|%s|%s|%s|%s|%s|%d|%d|%d|%lf|%u|%u\n", 
      corrente->identificador,
      corrente->usuario,
      corrente->nome,
      corrente->email,
      corrente->senha,
      corrente->endereco,
      (int)corrente->formaPagamento,
      (int)corrente->tipo,
      (int)corrente->estado,
      corrente->avaliacao,
      corrente->n_avaliacao,
      corrente->n_reclamacoes
    );*/
    
    /* Adicionamos ao grafo */
    if(adiciona_vertice(usuarios_grafo, i) != SUCESSO) {
      fclose(db_usuarios);
      free(corrente);
      return USUARIOS_FALHA_ADICIONAR_GRAFO;
    }
    
    /* Definimos o valores correntes no vértice */
    if(muda_valor_vertice(usuarios_grafo, i, (void *)corrente) != SUCESSO) {
      fclose(db_usuarios);
      free(corrente);
      return USUARIOS_FALHA_INSERIR_DADOS;
    }
    
    i++;
    
  }
  
  fclose(db_usuarios);
  
  usuarios_contador = i-1; /* Número de usuários carregados */
  
  /* Análogo para amigos */
  db_amigos = fopen(USUARIOS_DB_AMIGOS, "r");
  if(db_amigos == NULL){
    db_amigos = fopen(USUARIOS_DB_AMIGOS, "w");
    fclose(db_amigos);
    return USUARIOS_SUCESSO;
  }
  
  /* Agora carregamos os amigos */
  while(!feof(db_amigos)){
    /* Lemos do arquivo */
    fscanf(db_amigos, "%4d%4u%*[^\t]\t%4u%*[^\n]\n", &valorAresta, &identificador_A, &identificador_B);
    /* Pulamos relações mortas */
    if(valorAresta){
      /* Vemos se já há um arco entre eles nesta direção, uma assertiva */
      if(grafo_busca_arco(usuarios_grafo, identificador_A, identificador_B) != NULL){
        fclose(db_amigos);
         destroi_grafo(&usuarios_grafo);
        return USUARIOS_DB_CORROMPIDO;
      }
      
      /* Colocamos e definimos o id da aresta */
      if(
         adiciona_aresta(usuarios_grafo, identificador_A, identificador_B) != SUCESSO ||
         muda_valor_aresta(usuarios_grafo, identificador_A, identificador_B, valorAresta) != SUCESSO
      ){
        fclose(db_amigos);
        destroi_grafo(&usuarios_grafo);
        return USUARIOS_FALHA_CRIARAMIZADE;
      }
      
      /* Atualizamos o contador */
      usuarios_contador_amizades++;
    }
  }
  
  fclose(db_amigos);
  
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função de cadastro de usuários
 * 
 * Recebe como parâmetros nome, endereço, email, senha repetida duas vezes, forma de 
 * pagamento, tipo de usuário da seguinte maneira:
 * 
 * @code 
 * usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR);
 * @endcode
 *
 * Assertiva de entrada: o arquivo USUARIOS_DB já existe,
 * isto é a função usuarios_carregarArquivo já foi executada. E devem ser passados o número correto de argumentos
*/

usuarios_condRet usuarios_cadastro(int n, ...){
  FILE *db_usuarios;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Retorna USUARIOS_FALHA_ARGUMENTOSINVALIDOS se n for diferente de 8 */
  if(n!=8) return USUARIOS_FALHA_ARGUMENTOSINVALIDOS;
  
  /* Dados a armazenar */
  tpUsuario *novo;
  char senha_confirmacao[USUARIOS_LIMITE_SENHA];
  
  /* Argumentos */  
  va_list argumentos;
  va_start(argumentos, n);
  unsigned int i = 0, j;
  
  
  
  /* Percorremos os argumentos, armazenamos os dados em usuarios_dadosTemp */
  for(;i<n;i++){
    char *argumento = va_arg(argumentos, char *);
    for(j=0;j<usuarios_cadastro_argumentos_n;j++)
      if(!strcmp(argumento, usuarios_args[j].validos)) {
      	strncpy(usuarios_args[j].destino, va_arg(argumentos, char *), usuarios_args[j].tamanho-1);
        usuarios_args[j].destino[usuarios_args[j].tamanho-1] = '\0';
      }
      
    /* Casos especiais diferentes de char * */
    if(!strcmp(argumento, "senha_confirmacao")) 
      strncpy(senha_confirmacao, va_arg(argumentos, char *), USUARIOS_LIMITE_SENHA-1);
    if(!strcmp(argumento, "formaPagamento")) 
      usuarios_dadosTemp.formaPagamento = (usuarios_forma_de_pagamento)va_arg(argumentos, int);
    if(!strcmp(argumento, "tipo")) 
      usuarios_dadosTemp.tipo = (usuarios_tipo_usuario)va_arg(argumentos, int);
  }
  
  usuarios_dadosTemp.estado = ATIVO;
  usuarios_dadosTemp.avaliacao = 0;
  usuarios_dadosTemp.n_avaliacao = 0;
  usuarios_dadosTemp.n_reclamacoes = 0;
  
  va_end(argumentos);
  
  /* Verificamos se o grafo de usuários foi iniciado */
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Procuramos por caracteres ilegais, '\n' e '\t' pois são separadores */
  for(j=0;j<usuarios_cadastro_argumentos_n;j++)
    if(strstr(usuarios_args[j].destino, "\t") != NULL || strstr(usuarios_args[j].destino, "\n") != NULL)
      return USUARIOS_FALHA_CARACTERESILEGAIS;
  
  /* Verificamos se o email é válido */
  if(strstr(usuarios_dadosTemp.email, "@") == NULL || strstr(usuarios_dadosTemp.email, ".") == NULL) return USUARIOS_FALHA_EMAIL_INVALIDO;
  
  /* Verificamos se as senhas coincidem */
  if(strcmp(usuarios_dadosTemp.senha, senha_confirmacao)) return USUARIOS_FALHA_SENHAS_INVALIDAS;
  
  /* Verificamos se já há um usuário desse */
  if(usuarios_verificaRepeticao("usuario", usuarios_dadosTemp.usuario) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
    
  /* Verificamos se já há um email desse */
  if(usuarios_verificaRepeticao("email", usuarios_dadosTemp.email) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
  
  /* Define-se o identificador */
  usuarios_dadosTemp.identificador = ++usuarios_contador;
  
  /* Copiamos o valor temporário para o alocado */
  novo = (tpUsuario *)malloc(sizeof(tpUsuario));
  memcpy(novo, &usuarios_dadosTemp, sizeof(tpUsuario));
  
  
  /* Devemos percorrer o grafo usuarios_grafo e salvar no arquivo */
  db_usuarios = fopen(USUARIOS_DB, "a+");
  
  /* Gravamos no arquivo */
  fprintf(db_usuarios, USUARIOS_DB_ESTRUTURA, 
    novo->identificador,
    novo->usuario,
    novo->nome,
    novo->email,
    novo->senha,
    novo->endereco,
    (int)novo->formaPagamento,
    (int)novo->tipo,
    (int)novo->estado,
    novo->avaliacao,
    novo->n_avaliacao,
    novo->n_reclamacoes
  );
  
  /* Adicionamos ao grafo */
  
  if(adiciona_vertice(usuarios_grafo, novo->identificador) != SUCESSO) {
    fclose(db_usuarios);
    free(novo);
    return USUARIOS_FALHA_ADICIONAR_GRAFO;
  }
  
  /* Definimos o valores correntes no vértice */
  if(muda_valor_vertice(usuarios_grafo, novo->identificador, (void *)novo) != SUCESSO) {
    fclose(db_usuarios);
    free(novo);
    return USUARIOS_FALHA_INSERIR_DADOS;
  }
      
  fclose(db_usuarios);
  
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função que verifica se há uma sessão aberta
 * 
 * Retorna verdade caso haja uma sessão, retorna mentira caso contrário
*/
int usuarios_sessaoAberta(){
  if(usuarios_sessao == NULL) return 0;
  return 1;
}

/*!
 * @brief Buscamos a conta correspondente ao login e senha passados
 * 
 * Recebe as strings usuário e senha
*/
usuarios_condRet usuarios_login(char* usuario, char* senha) {

  tpUsuario *corrente;
  usuarios_condRet busca;
  unsigned int posicao;
  if(usuarios_sessaoAberta()) return USUARIOS_FALHA_SESSAOABERTA;
  
  busca = usuarios_busca(usuarios_condParada_login, &corrente, &posicao, usuario, senha);
  if(busca != USUARIOS_SUCESSO) return busca;
  
  if(corrente == NULL) return USUARIOS_GRAFO_CORROMPIDO;
  
  /* Vemos se o usuário está ativo */
  if(corrente->estado == ATIVO) {
    usuarios_sessao = corrente;
    return USUARIOS_SUCESSO;
  }
  else return USUARIOS_FALHA_INATIVO;
}

/*!
 * @brief Função de logout
 * 
 * Finaliza a sessão aberta
*/

usuarios_condRet usuarios_logout(){
  usuarios_sessao = NULL;
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função verifica um usuário é amigo do usuário na sessão
 * 
 * Assertiva de entrada, há uma sessão aberta
 * 
 * Recebe o identificador do usuário a ser verificada a relação de amizade com 
 * o usuário da sessão
 *
 * Retorna usuarios_sessao, podendo ser ERRO, AMIGOS, NENHUMA, ACONFIRMAR ou AGUARDANDOCONFIRMACAO
 * 
 * ERRO, caso algum erro ocorra, como a assertiva de entrada não ser respeitada
 * 
 * AMIGOS, se forem amigos
 * 
 * NENHUMA, se não existir relação entre eles
 * 
 * ACONFIRMAR, se o usuário pesquisado não tiver confirmado a amizade
 * 
 * AGUARDANDOCONFIRMACAO, se o usuário da sessão estiver por aceitar a amizade ou não
*/
usuarios_relacao usuarios_verificarAmizade(unsigned int identificador){
  grafo_arco *A, *B;
  
  if(usuarios_grafo == NULL) return ERRO;
  
  /* Verificamos se há sessão */
  if(!usuarios_sessaoAberta()) return ERRO;
  
  /* Verificamos se não quer observar uma amizade consigo mesmo */  
  if(identificador == usuarios_sessao->identificador) return ERRO;
    
  A = grafo_busca_arco(usuarios_grafo, usuarios_sessao->identificador, identificador);
  B = grafo_busca_arco(usuarios_grafo, identificador, usuarios_sessao->identificador);
  
  if(A != NULL && B != NULL) return AMIGOS;
  if(A == NULL && B == NULL) return NENHUMA;
  if(A == NULL && B != NULL) return ACONFIRMAR;
  if(A != NULL && B == NULL) return AGUARDANDOCONFIRMACAO;
  
}

/*!
 * @brief Função que cria parte de uma relação de amizade na sesão iniciada para algum
 * outro cliente
 *
 * Deve receber o identificador do amigo pretendido
 * 
 * Retorna USUARIOS_SUCESSO se não houver falhas
*/
usuarios_condRet usuarios_criarAmizade(unsigned int identificador){
  FILE *db_amigos;
  grafo_no *nodo;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Verificamos se há sessão */
  if(!usuarios_sessaoAberta()) return USUARIOS_FALHA_SESSAONULA;
  
  /* Verificamos se não é o próprio usuário querendo criar uma amizade consigo mesmo */
  if(identificador == usuarios_sessao->identificador) return USUARIOS_AMIZADEINVALIDA;
  
  /* Buscamos no grafo o identificador */
  nodo = (grafo_no *)grafo_busca_no(usuarios_grafo, 1, 0); /* Primeiro usuário */
  for(; nodo != NULL; nodo = (grafo_no *)nodo->prox_no ){
    
    tpUsuario *corrente = (tpUsuario *)nodo->dados;
    if(corrente == NULL) return USUARIOS_GRAFO_CORROMPIDO; /* Assertiva */
    
    if(corrente->identificador == identificador){
    
      /* Criamos uma aresta entre eles se não existir uma */
      if(grafo_busca_arco(usuarios_grafo, usuarios_sessao->identificador, corrente->identificador) != NULL)
        return USUARIOS_AMIZADEJASOLICITADA;
      
      if(adiciona_aresta(usuarios_grafo, usuarios_sessao->identificador, corrente->identificador) == SUCESSO){
        /* Definimos um valor para a aresta */
        usuarios_contador_amizades++;
        if(muda_valor_aresta(usuarios_grafo, usuarios_sessao->identificador, corrente->identificador, usuarios_contador_amizades) != SUCESSO)
          return USUARIOS_FALHA_CRIARAMIZADE;
        
        db_amigos = fopen(USUARIOS_DB_AMIGOS, "a+");
        if(db_amigos == NULL) return USUARIOS_FALHACRIARAMIZADE;
        
        /* Gravamos no arquivo */
        fprintf(db_amigos, "%*d\t%*u\t%*u\n", -USUARIOS_LIMITE_INT, usuarios_contador_amizades, -USUARIOS_LIMITE_INT, usuarios_sessao->identificador, -USUARIOS_LIMITE_INT, identificador);
        fclose(db_amigos);
        return USUARIOS_SUCESSO;
        
      }
      else return USUARIOS_FALHACRIARAMIZADE;
    }
  }
  return USUARIOS_FALHAUSUARIONAOEXISTE;
}

/*!
 * @brief Função que remove uma relação de amizade
 * 
 * Recebe os identificadores dos usuários A e B, se A for 0 assume que é da sessão
*/
usuarios_condRet usuarios_removerAmizade(unsigned int identificador_A, unsigned int identificador_B){
  int valorAresta;
  FILE *db_amigos;
  /* Verificamos se o grafo existe */
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Pegamos o identificador da sessão */
  if(identificador_A == 0) {
    if(!usuarios_sessaoAberta()) return USUARIOS_FALHA_SESSAONULA;
    if(usuarios_retornaDados(0, "identificador", &identificador_A) != USUARIOS_SUCESSO)
      return USUARIOS_FALHA_DADOSINCORRETOS;
  }
  
  /* Removemos do arquivo */
  db_amigos = fopen(USUARIOS_DB_AMIGOS, "r+");
  if(db_amigos == NULL) return USUARIOS_FALHA_LERDB;
  
  /* Removemos de A para B, se tiver */
  valorAresta = retorna_valor_aresta(usuarios_grafo, identificador_A, identificador_B);
  if(valorAresta){
    fseek(db_amigos, USUARIOS_DB_AMIGOS_REGISTRO_TAMANHO*(valorAresta-1), SEEK_SET);
    fprintf(db_amigos, "%4d\t%4u\t%4u\n", 0, (unsigned int)0, (unsigned int)0);
    
    if(remove_aresta(usuarios_grafo, identificador_A, identificador_B) != SUCESSO){
      fclose(db_amigos);
      return USUARIOS_FALHA_REMOVER_AMIZADE;
    }
  }
  
  /* Removemos de B para A, se tiver */
  valorAresta = retorna_valor_aresta(usuarios_grafo, identificador_B, identificador_A);
  if(valorAresta){
    fseek(db_amigos, USUARIOS_DB_AMIGOS_REGISTRO_TAMANHO*(valorAresta-1), SEEK_SET);
    fprintf(db_amigos, "%4d\t%4u\t%4u\n", 0, (unsigned int)0, (unsigned int)0);
    
    /* Removemos no grafo */
    if(remove_aresta(usuarios_grafo, identificador_B, identificador_A) != SUCESSO){
      fclose(db_amigos);
      return USUARIOS_FALHA_REMOVER_AMIZADE;
    }
  }
  
  fclose(db_amigos);
  return USUARIOS_SUCESSO;
  
  
}

/*!
 * @brief Retorna os dados do usuário do identificador passado
 *
 * Se identificador for zero, retornamos os dados da sessão
 * 
 * Retorna o dado por referência, recebe uma string com o dado a ser buscado
 * 
 * @code
 * usuarios_retornaDados(0, "nome", (void *)string_nome);
 * @endcode
 * 
 * Retorna o nome do usuário da sessão e salva em string_nome
 * 
 * Argumentos válidos: "identificador", "usuario", "nome", "senha", "email", "endereco", 
 * "formaPagamento", "tipo", "estado", "avaliacao", "n_avaliacao", "n_reclamacoes"
*/
usuarios_condRet usuarios_retornaDados(unsigned int identificador, const char *nomeDado, void *retorno) {
  unsigned int i = 0;
  tpUsuario *dados;
    
  printf("teste: %d\n", identificador);

  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Pegamos o nodo com o identificador passado */
  if(identificador) dados = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, identificador);
  /* Se foi passado 0, então pega-se o da sessão */
  else dados = usuarios_sessao;
  
  if(dados == NULL) return USUARIOS_GRAFO_CORROMPIDO; /* Assertiva */
  
  /* Copiamos os dados para usuarios_dadosTemp */
  memcpy(&usuarios_dadosTemp, dados, sizeof(tpUsuario));
  
  /* Dados possíveis */
  for(;i<usuarios_cadastro_argumentos_n;i++)
    if(!strcmp(nomeDado, usuarios_args[i].validos)) {
      strncpy((char *)retorno, usuarios_args[i].destino, usuarios_args[i].tamanho);
    }
  /* Outros casos (não char *) */
  if(!strcmp(nomeDado, "identificador")) 
    *((int *)retorno) = usuarios_dadosTemp.identificador;
  if(!strcmp(nomeDado, "formaPagamento")) 
    *((usuarios_forma_de_pagamento *)retorno) = usuarios_dadosTemp.formaPagamento;
  if(!strcmp(nomeDado, "tipo")) 
    *((usuarios_tipo_usuario *)retorno) = usuarios_dadosTemp.tipo;
  if(!strcmp(nomeDado, "estado")) 
    *((usuarios_estado_de_usuario *)retorno) = usuarios_dadosTemp.estado;
  if(!strcmp(nomeDado, "avaliacao")) 
    *((double *)retorno) = usuarios_dadosTemp.avaliacao;
  if(!strcmp(nomeDado, "n_avaliacao")) 
    *((unsigned int *)retorno) = usuarios_dadosTemp.n_avaliacao;
  if(!strcmp(nomeDado, "n_reclamacoes")) 
    *((unsigned int *)retorno) = usuarios_dadosTemp.n_reclamacoes;
  
  return USUARIOS_SUCESSO;
  
}

/*!
 * @brief Atualiza dados do usuário de identificador passado
 *
 * Se identificador for zero, altera os dados da sessão
 *  
 * @code
 * usuarios_atualizarDados(0, "nome", "João Ninguém");
 * @endcode
 *
 * O último argumento pode ser de qualquer tipo, exemplo:
 * 
 * @code
 * usuarios_atualizarDados(0, "estado", INATIVO_ABUSO);
 * @endcode
 * 
 * Argumentos válidos: "identificador", "usuario", "nome", "senha", "email", "endereco", 
 * "formaPagamento", "tipo", "estado", "avaliacao", "n_avaliacao", "n_reclamacoes"
*/
usuarios_condRet usuarios_atualizarDados(unsigned int identificador, const char *nomeDado, ...){
  unsigned int i;
  tpUsuario *corrente;
  FILE *db_usuarios;
  va_list arg;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Pegamos o nodo com o identificador passado */
  if(identificador) corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, identificador);
  /* Se foi passado 0, então pega-se o da sessão */
  else corrente = usuarios_sessao;
  
  if(corrente == NULL) return USUARIOS_GRAFO_CORROMPIDO; /* Assertiva */
      
  va_start(arg, nomeDado);
  
  /* Analizamos os argumentos passados armazenando em usuarios_dadosTemp */
  memcpy(&usuarios_dadosTemp, corrente, sizeof(tpUsuario));
  
  for(i=0;i<usuarios_cadastro_argumentos_n;i++)
    if(!strcmp(nomeDado, usuarios_args[i].validos)) {
      strncpy(usuarios_args[i].destino, va_arg(arg, char *), usuarios_args[i].tamanho);
    }
  /* Outros casos (não char *) */
  if(!strcmp(nomeDado, "formaPagamento")) 
    usuarios_dadosTemp.formaPagamento = (usuarios_forma_de_pagamento)va_arg(arg, int);
  if(!strcmp(nomeDado, "tipo")) 
    usuarios_dadosTemp.tipo = (usuarios_tipo_usuario)va_arg(arg, int);
  if(!strcmp(nomeDado, "estado")) 
    usuarios_dadosTemp.estado = (usuarios_estado_de_usuario)va_arg(arg, int);
  if(!strcmp(nomeDado, "avaliacao")) 
    usuarios_dadosTemp.avaliacao = va_arg(arg, double);
  if(!strcmp(nomeDado, "n_avaliacao")) 
    usuarios_dadosTemp.n_avaliacao = va_arg(arg, unsigned int);
  if(!strcmp(nomeDado, "n_reclamacoes")) 
    usuarios_dadosTemp.n_reclamacoes = va_arg(arg, unsigned int);
    
  va_end(arg);
  
  /* Copiamos no grafo */
  memcpy(corrente, &usuarios_dadosTemp, sizeof(tpUsuario));
  
  /* Atualizamos no arquivo de dados */
  db_usuarios = fopen(USUARIOS_DB, "r+");
  if(db_usuarios == NULL) return USUARIOS_FALHA_LERDB;
  
  fseek(db_usuarios, (corrente->identificador-1)*(
    USUARIOS_LIMITE_INT + 1 +
    USUARIOS_LIMITE_USUARIO + 1 +
    USUARIOS_LIMITE_NOME + 1 +
    USUARIOS_LIMITE_EMAIL + 1 +
    USUARIOS_LIMITE_SENHA + 1 +
    USUARIOS_LIMITE_ENDERECO + 1 +
    USUARIOS_LIMITE_INT + 1 +
    USUARIOS_LIMITE_INT + 1 +
    USUARIOS_LIMITE_INT + 1 +
    USUARIOS_LIMITE_DOUBLE + 1 +
    USUARIOS_LIMITE_INT + 1 +
    USUARIOS_LIMITE_INT + 1
	), SEEK_SET);
  
  fprintf(db_usuarios, USUARIOS_DB_ESTRUTURA, 
    corrente->identificador,
    corrente->usuario,
    corrente->nome,
    corrente->email,
    corrente->senha,
    corrente->endereco,
    (int)corrente->formaPagamento,
    (int)corrente->tipo,
    (int)corrente->estado,
    corrente->avaliacao,
    corrente->n_avaliacao,
    corrente->n_reclamacoes
  );
  
  fclose(db_usuarios);
  
  return USUARIOS_SUCESSO;
  
  
}

/*!
 * @brief Apaga o grafo de usuários da memória e faz logout na sessão aberta
 * 
 * Retorna USUARIOS_SUCESSO se não ocorrerem erros.
*/
usuarios_condRet usuarios_limpar(){
  /* Fechamos qualquer sessão aberta */
  if(usuarios_logout() != USUARIOS_SUCESSO) return USUARIOS_FALHA_FECHARSESSAO;
  /* Limpamos o grafo */
  if(destroi_grafo(&usuarios_grafo) != SUCESSO) return USUARIOS_FALHA_LIMPAR;
  
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função que retorna uma lista de identificadores dos amigos
 * do usuário passado pretendido, se o identificador for 0, retorna da sessão
 *
 * Retorna por referência um array de unsigned int
 * positivo (usuarios_uintarray). O array deve ser alocado estaticamente:
 * 
 * @code
 * usuarios_uintarray array;
 * usuarios_listarAmigos(0, &array);
 * @endcode
 * 
 * Vai compor o array com os identificadores dos amigos.
*/
usuarios_condRet usuarios_listarAmigos(unsigned int identificador, usuarios_uintarray *retorno) {
  tpUsuario *usuario;
  grafo_lista_no *listaVizinhos, *tmp;
  
  /* Pegamos o nodo com o identificador passado */
  if(identificador) usuario = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, identificador);
  /* Se foi passado 0, então pega-se o da sessão */
  else usuario = usuarios_sessao;
  
  if(usuario == NULL) return USUARIOS_FALHA_ACESSORESTRITO; /* Assertiva */
 
  /* Geramos o vetor */
  //*retorno = (usuarios_uintarray *)malloc(sizeof(usuarios_uintarray));
  retorno->length = 0;
  retorno->array = NULL;
  
  /* Buscamos os nós vizinhos */
  listaVizinhos = vizinhos(usuarios_grafo, usuario->identificador);
  for(tmp=listaVizinhos;tmp != NULL;tmp=(grafo_lista_no *)tmp->prox_no){
    
    /* Verificamos se há um arco vindo no sentido contrário */
    if(adjacente(usuarios_grafo, tmp->valor, usuario->identificador) == ADJACENTES)  {
      retorno->array = (unsigned int *)realloc(retorno->array, (++retorno->length)*sizeof(unsigned int));
      retorno->array[retorno->length-1] = tmp->valor;
    }
  }
  
  grafo_lista_no_limpar(&listaVizinhos);
  return USUARIOS_SUCESSO;
  
}

/*!
 * @brief Função que retorna uma lista de identificadores de usuários que solicitaram amizade
 * ao usuário da sessão
 *
 * Retorna por referência um array de unsigned int
 * positivo (usuarios_uintarray). O array deve ser alocado estaticamente:
 * 
 * @code
 * usuarios_uintarray array;
 * usuarios_listarAmigosPendentes(0, &array);
 * @endcode
 * 
 * Vai compor o array com os identificadores dos amigos.
*/
usuarios_condRet usuarios_listarAmigosPendentes(unsigned int identificador, usuarios_uintarray *retorno) {
  tpUsuario *corrente;
  unsigned int i;
  
  /* Pegamos o nodo com o identificador passado */
  if(identificador) corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, identificador);
  /* Se foi passado 0, então pega-se o da sessão */
  else corrente = usuarios_sessao;
  
  if(corrente == NULL) return USUARIOS_FALHA_ACESSORESTRITO; /* Assertiva */
  
  /* Geramos o vetor */
  //*retorno = (usuarios_uintarray *)malloc(sizeof(usuarios_uintarray));
  retorno->length = 0;
  retorno->array = NULL;
  
  /* Buscamos em todo o grafo */
  for(i=0;i<usuarios_contador;i++){
    /* Vemos se há um arco do usuário i ao usuário identificador e que não há um no sentido contrário */
    if(grafo_busca_arco(usuarios_grafo, i, identificador) != NULL &&
       grafo_busca_arco(usuarios_grafo, identificador, i) == NULL){
      /* Adicionamos ao array */
      retorno->length++;
      retorno->array = (unsigned int*)realloc(retorno->array, retorno->length*sizeof(unsigned int));
      if(retorno->array == NULL) {
        retorno->length = 0;
        return USUARIOS_FALHA_INSERIR_DADOS;
      }
      retorno->array[retorno->length-1] = i;
    }
  }
  
  return USUARIOS_SUCESSO;
  
}

/*!
 * @brief Função que lista os amigos de amigos (excluíndo amigos)
 *
*/
usuarios_condRet usuarios_listarAmigosdeAmigos(unsigned int identificador, usuarios_uintarray *retorno){
  usuarios_uintarray amigos, amigosdeamigos;
  unsigned int i,j,k;
  
  /* Listamos os amigos do usuário */
  if(usuarios_listarAmigos(identificador, &amigos) != USUARIOS_SUCESSO) 
    return USUARIOS_FALHA_LISTARAMIGOS;
  
  retorno->length = 0;
  retorno->array = NULL;
  
  /* Para cada amigo buscamos os amigos */
  for(i=0;i<amigos.length;i++){
    if(usuarios_listarAmigos(amigos.array[i], &amigosdeamigos) != USUARIOS_SUCESSO) 
      return USUARIOS_FALHA_LISTARAMIGOS;
      
    /* Inserimos um a um de temporário no retorno, se ainda não estiver */
    for(j=0;j<amigosdeamigos.length;j++){
      /* Impedimos autoinclusão */
      if(amigosdeamigos.array[j] != identificador) {
        /* Para cada temporário buscamos no retorno se já existe e não esteja em amigos */
        for(k=0;k<retorno->length;k++){
          if(retorno->array[k] == amigosdeamigos.array[j]) break;
        }
        /* Adicionamos ao retorno */
        if(k == retorno->length) {
          retorno->length++;
          retorno->array = (unsigned int *)realloc(retorno->array, retorno->length*sizeof(unsigned int));
          retorno->array[retorno->length-1] = amigosdeamigos.array[j];
        }
      }
    }
    usuarios_freeUint(&amigosdeamigos);
  }
  
  usuarios_freeUint(&amigos);
  return USUARIOS_SUCESSO;  
}

/*!
 * @brief Função que desaloca memória de usuarios_uintarray
 * 
 * Recebe o endereço de usuarios_uintarray
*/
usuarios_condRet usuarios_freeUint(usuarios_uintarray *vetor){
  if(vetor->array != NULL) free(vetor->array);
  vetor->array = NULL;
  vetor->length = 0;
  return USUARIOS_SUCESSO;
}


