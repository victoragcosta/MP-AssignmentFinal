#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "aleatorio.h"
#include "usuarios.h"
#include "grafo.h"

/*!
 * @brief Grafo de usuários
*/
static grafo *usuarios_grafo = NULL; /* Grafo de usuários */
static unsigned int usuarios_contador = 0; /* Contador de usuários no grafo */
static unsigned int usuarios_identificador_max = 0; /* Contador do maior id de usuário no grafo */

/*!
 * @brief Sessão aberta
*/
static tpUsuario *usuarios_sessao = NULL; /* Inicialmente NULL significa que não há usuário logado */
static unsigned int usuarios_sessao_pos;

/*!
 * @brief Estrutura de usuário temporário para uso do usuarios_args nas funções
*/
static tpUsuario *usuarios_dadosTemp = (tpUsuario *)malloc(sizeof(tpUsuario));

/*!
 * @brief Argumentos padrão aceitáveis pelas funções ao buscar/alterar/definir dados de usuário
*/
static unsigned int usuarios_cadastro_argumentos_n = 5;

static usuarios_cadastro_argumentos usuarios_args[] = {
  {.validos = "usuario", .tamanho = USUARIOS_LIMITE_USUARIO, .destino = usuarios_dadosTemp->usuario},
  {.validos = "nome", .tamanho = USUARIOS_LIMITE_NOME, .destino = usuarios_dadosTemp->nome},
  {.validos = "email", .tamanho = USUARIOS_LIMITE_EMAIL, .destino = usuarios_dadosTemp->email},
  {.validos = "senha", .tamanho = USUARIOS_LIMITE_SENHA, .destino = usuarios_dadosTemp->senha},
  {.validos = "endereco", .tamanho = USUARIOS_LIMITE_ENDERECO, .destino = usuarios_dadosTemp->endereco}
};

/*!
 * @brief Copiamos os dados de uma lista de argumentos para usuarios_dadosTemp
*/
void usuarios_copiarDadosTemp(unsigned int n, va_list argumentos){
  unsigned int i=0,j;
  char *argumento;
  for(;i<n;i++){
    argumento = va_arg(argumentos, char *);
    for(j=0;j<usuarios_cadastro_argumentos_n;j++)
      if(!strcmp(argumento, usuarios_args[j].validos)) strncpy(usuarios_args[j].destino, va_arg(argumentos, char *), usuarios_args[j].tamanho);
    
    /* Casos especiais diferentes de char * */
    if(!strcmp(argumento, "formaPagamento")) 
      usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(argumentos, int);
    if(!strcmp(argumento, "tipo")) 
      usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(argumentos, int);
  }
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
  unsigned int i = 0; /* Contador dos nós */
  tpUsuario *informacao;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  /* Buscamos por um usuario igual */
  if(!strcmp(argumento, "usuario")) {
    for(i=0;i<usuarios_contador;i++){
      informacao = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
      /* Asertiva */
      if(informacao == NULL) return USUARIOS_GRAFO_CORROMPIDO;
      
      /* São iguais */ 
      //printf("'%s' == '%s'\n", informacao->usuario, dado);
      if(!strcmp(informacao->usuario, dado)) return USUARIOS_DADOS_REPETICAO;
    }
    return USUARIOS_DADOS_OK;
  }
  
  /* Buscamos por um email igual (REPETIÇÃO DE CÓDIGO) */
  if(!strcmp(argumento, "email")) {
    for(i=0;i<usuarios_contador;i++){
      informacao = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
      /* Asertiva */
      if(informacao == NULL) return USUARIOS_GRAFO_CORROMPIDO;
      
      /* São iguais */ 
      //printf("'%s' == '%s'\n", informacao->email, dado);
      if(!strcmp(informacao->email, dado)) return USUARIOS_DADOS_REPETICAO;
    }
    return USUARIOS_DADOS_OK;
  }
  
  return USUARIOS_ARGUMENTOINVALIDO;
}

/*!
 * @brief Condição de parada para encontrar identificador
*/
int usuarios_condParada_identificador(tpUsuario *corrente, va_list argumentos){
  return corrente->identificador == va_arg(argumentos, unsigned int);
}

/*!
 * @brief Condição de parada para usuario e senha corretos do login
*/
int usuarios_condParada_login(tpUsuario *corrente, va_list argumentos){
  return !strcmp(corrente->usuario, va_arg(argumentos, char *)) && !strcmp(corrente->senha, va_arg(argumentos, char *));
}

/*!
 * @brief Busca no grafo de usuários
*/
static usuarios_condRet usuarios_busca(int condParada(tpUsuario *, va_list), tpUsuario **retorno, unsigned int *indice ...){
  unsigned int i = 0;
  tpUsuario *corrente;
  
  va_list argumentos, passado;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  va_start(argumentos, indice);
  
  for(;i<usuarios_contador;i++){
    corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
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
*/
static void usuarios_lerString(FILE *arquivo, char *dstStr, unsigned int limite){
  unsigned int i = 0, espaco = 0;
  char caracter;
  
  while (
    !feof(arquivo) && \
    (caracter = fgetc(arquivo)) != '\t' && \
    caracter != '\n' && \
    i < limite - 1
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
  int i = 0;
  
  /* Identificadores para os amigos */
  unsigned int identificador_A, identificador_B, posicao_A, posicao_B;
  
  usuarios_condRet busca;

  /* Dados do usuário corrente */
  tpUsuario *corrente;
  while(!feof(db_usuarios)){
    corrente = (tpUsuario *)malloc(sizeof(tpUsuario));
    
    /* Lemos do arquivo */
    fscanf(db_usuarios, "%u%*[^\t]\t", &(corrente->identificador));
    if(corrente->identificador == 0) break;
    usuarios_lerString(db_usuarios, corrente->usuario, USUARIOS_LIMITE_USUARIO);
    usuarios_lerString(db_usuarios, corrente->nome, USUARIOS_LIMITE_NOME);
    usuarios_lerString(db_usuarios, corrente->email, USUARIOS_LIMITE_EMAIL);
    usuarios_lerString(db_usuarios, corrente->senha, USUARIOS_LIMITE_SENHA);
    usuarios_lerString(db_usuarios, corrente->endereco, USUARIOS_LIMITE_ENDERECO);
    
    fscanf(db_usuarios, "%d%*[^\t]\t%d%*[^\t]\t%d%*[^\t]\t%lf%*[^\t]\t%u%*[^\t]\t%u%*[^\n]", 
      (int *)&(corrente->formaPagamento), \
      (int *)&(corrente->tipo), \
      (int *)&(corrente->estado), \
      &(corrente->avaliacao), \
      &(corrente->n_avaliacao), \
      &(corrente->n_reclamacoes)
    );
    
    printf("%u|%s|%s|%s|%s|%s|%d|%d|%d|%lf|%u|%u\n", 
      corrente->identificador,  \
      corrente->usuario, \
      corrente->nome, \
      corrente->email, \
      corrente->senha, \
      corrente->endereco, \
      (int)corrente->formaPagamento, \
      (int)corrente->tipo, \
      (int)corrente->estado, \
      corrente->avaliacao, \
      corrente->n_avaliacao, \
      corrente->n_reclamacoes
    );
    
    /* Atualizamos o máximo */
    if(corrente->identificador > usuarios_identificador_max)
      usuarios_identificador_max = corrente->identificador;
    
    
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
  
  usuarios_contador = i; /* Número de usuários carregados */
  
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
    fscanf(db_amigos, "%*u\t%*u\n", -USUARIOS_LIMITE_INT, &identificador_A, -USUARIOS_LIMITE_INT, &identificador_B);
    
    /* Buscamos o identificador no grafo */
    busca = usuarios_busca(usuarios_condParada_identificador, NULL, &posicao_A, identificador_A);
    if(busca != USUARIOS_SUCESSO) return USUARIOS_GRAFO_CORROMPIDO;
    
    busca = usuarios_busca(usuarios_condParada_identificador, NULL, &posicao_B, identificador_B);
    if(busca != USUARIOS_SUCESSO) return USUARIOS_GRAFO_CORROMPIDO;
    
    /* Vemos se já há um arco entre eles nesta direção, uma assertiva */
    if(grafo_busca_arco(usuarios_grafo, posicao_A, posicao_B) != NULL){
      fclose(db_amigos);
      return USUARIOS_DB_CORROMPIDO;
    }
    
    if(adiciona_aresta(usuarios_grafo, posicao_A, posicao_B) != SUCESSO){
      fclose(db_amigos);
      return USUARIOS_FALHA_CRIARAMIZADE;
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
  
  char *argumento;
  
  /* Percorremos os argumentos, armazenamos os dados em usuarios_dadosTemp */
  for(;i<n;i++){
    argumento = va_arg(argumentos, char *);
    for(j=0;j<usuarios_cadastro_argumentos_n;j++)
      if(!strcmp(argumento, usuarios_args[j].validos)) strncpy(usuarios_args[j].destino, va_arg(argumentos, char *), usuarios_args[j].tamanho);
      
    /* Casos especiais diferentes de char * */
    if(!strcmp(argumento, "senha_confirmacao")) 
      strncpy(senha_confirmacao, va_arg(argumentos, char *), USUARIOS_LIMITE_SENHA);
    if(!strcmp(argumento, "formaPagamento")) 
      usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(argumentos, int);
    if(!strcmp(argumento, "tipo")) 
      usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(argumentos, int);
  }
  
  usuarios_dadosTemp->estado = ATIVO;
  usuarios_dadosTemp->avaliacao = 0;
  usuarios_dadosTemp->n_avaliacao = 0;
  usuarios_dadosTemp->n_reclamacoes = 0;
  
  va_end(argumentos);
  
  /* Verificamos se o grafo de usuários foi iniciado */
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Procuramos por caracteres ilegais, '\n' e '\t' pois são separadores */
  for(j=0;j<usuarios_cadastro_argumentos_n;j++)
    if(strstr(usuarios_args[j].destino, "\t") != NULL || strstr(usuarios_args[j].destino, "\n") != NULL)
      return USUARIOS_FALHA_CARACTERESILEGAIS;
  
  /* Verificamos se o email é válido */
  if(strstr(usuarios_dadosTemp->email, "@") == NULL || strstr(usuarios_dadosTemp->email, ".") == NULL) return USUARIOS_FALHA_EMAIL_INVALIDO;
  
  /* Verificamos se as senhas coincidem */
  if(strcmp(usuarios_dadosTemp->senha, senha_confirmacao)) return USUARIOS_FALHA_SENHAS_INVALIDAS;
  
  /* Verificamos se já há um usuário desse */
  if(usuarios_verificaRepeticao("usuario", usuarios_dadosTemp->usuario) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
    
  /* Verificamos se já há um email desse */
  if(usuarios_verificaRepeticao("email", usuarios_dadosTemp->email) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
  
  /* Define-se o identificador */
  usuarios_dadosTemp->identificador = ++usuarios_identificador_max;
  
  /* Copiamos o valor temporário para o alocado */
  novo = (tpUsuario *)malloc(sizeof(tpUsuario));
  memcpy(novo, usuarios_dadosTemp, sizeof(tpUsuario));
  
  /* Devemos percorrer o grafo usuarios_grafo e salvar no arquivo */
  db_usuarios = fopen(USUARIOS_DB, "a+");
  
  /* Gravamos no arquivo */
  int fprintf_retorno = fprintf(db_usuarios, "%*u\t%*s\t%*s\t%*s\t%*s\t%*s\t%*d\t%*d\t%*d\t%*lf\t%*u\t%*u\n", 
    -USUARIOS_LIMITE_INT, usuarios_identificador_max,  \
    -USUARIOS_LIMITE_USUARIO, novo->usuario, \
    -USUARIOS_LIMITE_NOME, novo->nome, \
    -USUARIOS_LIMITE_EMAIL, novo->email, \
    -USUARIOS_LIMITE_SENHA, novo->senha, \
    -USUARIOS_LIMITE_ENDERECO, novo->endereco, \
    -USUARIOS_LIMITE_INT, (int)novo->formaPagamento, \
    -USUARIOS_LIMITE_INT, (int)novo->tipo, \
    -USUARIOS_LIMITE_INT, (int)novo->estado, \
    -USUARIOS_LIMITE_DOUBLE, novo->avaliacao, \
    -USUARIOS_LIMITE_INT, novo->n_avaliacao, \
    -USUARIOS_LIMITE_INT, novo->n_reclamacoes
  );
  
  /* Adicionamos ao grafo */
  
  if(adiciona_vertice(usuarios_grafo, usuarios_contador) != SUCESSO) {
    fclose(db_usuarios);
    free(novo);
    return USUARIOS_FALHA_ADICIONAR_GRAFO;
  }
  
  /* Definimos o valores correntes no vértice */
  if(muda_valor_vertice(usuarios_grafo, usuarios_contador, (void *)novo) != SUCESSO) {
    fclose(db_usuarios);
    free(novo);
    return USUARIOS_FALHA_INSERIR_DADOS;
  }
  
  usuarios_contador++; /* Atualizamos o número de usuários */
  
  fclose(db_usuarios);
  
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Buscamos a conta correspondente ao login e senha passados
*/
usuarios_condRet usuarios_login(char *usuario, char *senha){
  tpUsuario *corrente;
  usuarios_condRet busca;
  unsigned int posicao;
  if(usuarios_sessao != NULL) return USUARIOS_FALHA_SESSAOABERTA;
  
  busca = usuarios_busca(usuarios_condParada_login, &corrente, &posicao, usuario, senha);
  
  if(busca != USUARIOS_SUCESSO) return busca;
  
  /* Vemos se o usuário está ativo */
  if(corrente->estado == ATIVO) {
    usuarios_sessao = corrente;
    usuarios_sessao_pos = posicao;
    return USUARIOS_SUCESSO;
  }
  else return USUARIOS_FALHA_INATIVO;
}

/*!
 * @brief Função de logout
*/

usuarios_condRet usuarios_logout(){
  usuarios_sessao = NULL;
  usuarios_sessao_pos = 0; /* Não é fator de verificação da sessão, então pode ser qualquer valor */
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função de busca do usuário a partir do identificador
 * fazendo restrição a sessão, caso o usuário não seja administrador
 *
 * Interface:
 * @code
 * usuarios_condRet usuarios_buscaLimitada(unsigned int identificador, tpUsuario **retorno, unsigned int *indice = NULL);
 * @endcode
 * Exemplo, busca os dados *tpUsuario do usuário de identificador 5 e 
 * retorna por referência para dados.
 * @code
 * usuarios_buscaLimitada(5, &dados, NULL);
 * @endcode
 * Retorna também por referência a posição no grafo do 
 * usuário (terceiro argumento), retornado por referência
 * @code
 * usuarios_buscaLimitada(5, &dados, &pos);
 * @endcode
*/
static usuarios_condRet usuarios_buscaLimitada(unsigned int identificador, tpUsuario **retorno, unsigned int *indice){  
  tpUsuario *corrente;
  usuarios_condRet busca;
  /* Se passado 0 retornamos o usuário da sessão */
  if(identificador){
    if(1){
        /* Buscamos o identificador caso o usuário seja ADMINISTRADOR */
        busca = usuarios_busca(usuarios_condParada_identificador, &corrente, indice, identificador);
        if(busca == USUARIOS_SUCESSO) *retorno = corrente;
        return busca;
    }
    else {
      *retorno = NULL;
      return USUARIOS_FALHA_ACESSORESTRITO;
    }
  }
  else *retorno = usuarios_sessao;
}

/*!
 * @brief Função verifica um usuário é amigo do usuário na sessão
*/
usuarios_relacao usuarios_verificarAmizade(unsigned int identificador){
  unsigned int i=0, posicao;
  tpUsuario *corrente;
  grafo_arco *A, *B;
  usuarios_condRet busca;
  if(usuarios_grafo == NULL) return ERRO;
  
  /* Verificamos se há sessão */
  if(usuarios_sessao == NULL) return ERRO;
  
  /* Buscamos o identificador no grafo */
  busca = usuarios_busca(usuarios_condParada_identificador, &corrente, &posicao, identificador);
  if(busca != USUARIOS_SUCESSO) return ERRO;
  
  if(identificador == usuarios_sessao->identificador) return ERRO;
  
  A = grafo_busca_arco(usuarios_grafo, usuarios_sessao_pos, posicao);
  B = grafo_busca_arco(usuarios_grafo, posicao, usuarios_sessao_pos);
  
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
*/
usuarios_condRet usuarios_criarAmizade(unsigned int identificador){
  unsigned int i=0;
  tpUsuario *corrente;
  FILE *db_amigos;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Verificamos se há sessão */
  if(usuarios_sessao == NULL) return USUARIOS_FALHA_SESSAONULA;
  
  /* Verificamos se não é o próprio usuário querendo criar uma amizade consigo mesmo */
  if(identificador == usuarios_sessao->identificador) return USUARIOS_AMIZADEINVALIDA;
  
  /* Buscamos no grafo o identificador */
  for(;i<usuarios_contador;i++){
    corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
    if(corrente == NULL) return USUARIOS_GRAFO_CORROMPIDO;
    
    if(corrente->identificador == identificador){
      /* Criamos uma aresta entre eles se não existir uma */
      if(grafo_busca_arco(usuarios_grafo, usuarios_sessao_pos, i) != NULL)
        return USUARIOS_AMIZADEJASOLICITADA;
      
      if(adiciona_aresta(usuarios_grafo, usuarios_sessao_pos, i) == SUCESSO){
        db_amigos = fopen(USUARIOS_DB_AMIGOS, "a+");
        if(db_amigos == NULL) return USUARIOS_FALHACRIARAMIZADE;
        
        /* Gravamos no arquivo */
        fprintf(db_amigos, "%*u\t%*u\n", -USUARIOS_LIMITE_INT, usuarios_sessao->identificador, -USUARIOS_LIMITE_INT, identificador);
        fclose(db_amigos);
        return USUARIOS_SUCESSO;
        
      }
      else return USUARIOS_FALHACRIARAMIZADE;
    }
  }
  return USUARIOS_FALHAUSUARIONAOEXISTE;
}

/*!
 * @brief Retorna os dados do usuário do identificador passado
 *
 * Se identificador for zero, retornamos os dados da sessão
*/
usuarios_condRet usuarios_retornaDados(unsigned int identificador, char *nomeDado, void *retorno) {
  unsigned int i = 0;
  tpUsuario *dados;
    
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;

  usuarios_buscaLimitada(identificador, &dados, NULL);
  if(dados == NULL) return USUARIOS_FALHA_ACESSORESTRITO;
  
  
  /* Copiamos os dados para usuarios_dadosTemp */
  memcpy(usuarios_dadosTemp, dados, sizeof(tpUsuario));
  
  /* Dados possíveis */
  for(;i<usuarios_cadastro_argumentos_n;i++)
    if(!strcmp(nomeDado, usuarios_args[i].validos)) {
      *((char **)retorno) = usuarios_args[i].destino;
    }
  /* Outros casos (não char *) */
  if(!strcmp(nomeDado, "formaPagamento")) 
    *((usuarios_forma_de_pagamento *)retorno) = usuarios_dadosTemp->formaPagamento;
  if(!strcmp(nomeDado, "tipo")) 
    *((usuarios_tipo_usuario *)retorno) = usuarios_dadosTemp->tipo;
  if(!strcmp(nomeDado, "estado")) 
    *((usuarios_estado_de_usuario *)retorno) = usuarios_dadosTemp->estado;
  if(!strcmp(nomeDado, "avaliacao")) 
    *((double *)retorno) = usuarios_dadosTemp->avaliacao;
  if(!strcmp(nomeDado, "n_avaliacao")) 
    *((unsigned int *)retorno) = usuarios_dadosTemp->n_avaliacao;
  if(!strcmp(nomeDado, "n_reclamacoes")) 
    *((unsigned int *)retorno) = usuarios_dadosTemp->n_reclamacoes;
  
  return USUARIOS_SUCESSO;
  
}

/*!
 * @brief Atualiza dados do usuário de identificador passado
*/
usuarios_condRet usuarios_atualizarDados(unsigned int identificador, char *nomeDado, ...){
  unsigned int i, j;
  usuarios_condRet busca;
  tpUsuario *corrente;
  FILE *db_usuarios;
  va_list arg;
  
  if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
  
  /* Buscamos o identificador */
  usuarios_buscaLimitada(identificador, &corrente, NULL);
  if(corrente == NULL) return USUARIOS_FALHA_ACESSORESTRITO;
    
  va_start(arg, nomeDado);
  
  /* Analizamos os argumentos passados armazenando em usuarios_dadosTemp */
  memcpy(usuarios_dadosTemp, corrente, sizeof(tpUsuario));
  
  for(i=0;i<usuarios_cadastro_argumentos_n;i++)
    if(!strcmp(nomeDado, usuarios_args[i].validos)) {
      strncpy(usuarios_args[i].destino, va_arg(arg, char *), usuarios_args[i].tamanho);
    }
  /* Outros casos (não char *) */
  if(!strcmp(nomeDado, "formaPagamento")) 
    usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(arg, int);
  if(!strcmp(nomeDado, "tipo")) 
    usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(arg, int);
  if(!strcmp(nomeDado, "estado")) 
    usuarios_dadosTemp->estado = (usuarios_estado_de_usuario)va_arg(arg, int);
  if(!strcmp(nomeDado, "avaliacao")) 
    usuarios_dadosTemp->avaliacao = va_arg(arg, double);
  if(!strcmp(nomeDado, "n_avaliacao")) 
    usuarios_dadosTemp->n_avaliacao = va_arg(arg, unsigned int);
  if(!strcmp(nomeDado, "n_reclamacoes")) 
    usuarios_dadosTemp->n_reclamacoes = va_arg(arg, unsigned int);
    
  va_end(arg);
  
  /* Copiamos no grafo */
  memcpy(corrente, usuarios_dadosTemp, sizeof(tpUsuario));
  
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
  
  int fprintf_retorno = fprintf(db_usuarios, "%*u\t%*s\t%*s\t%*s\t%*s\t%*s\t%*d\t%*d\t%*d\t%*lf\t%*u\t%*u\n", 
    -USUARIOS_LIMITE_INT, corrente->identificador,  \
    -USUARIOS_LIMITE_USUARIO, corrente->usuario, \
    -USUARIOS_LIMITE_NOME, corrente->nome, \
    -USUARIOS_LIMITE_EMAIL, corrente->email, \
    -USUARIOS_LIMITE_SENHA, corrente->senha, \
    -USUARIOS_LIMITE_ENDERECO, corrente->endereco, \
    -USUARIOS_LIMITE_INT, (int)corrente->formaPagamento, \
    -USUARIOS_LIMITE_INT, (int)corrente->tipo, \
    -USUARIOS_LIMITE_INT, (int)corrente->estado, \
    -USUARIOS_LIMITE_DOUBLE, corrente->avaliacao, \
    -USUARIOS_LIMITE_INT, corrente->n_avaliacao, \
    -USUARIOS_LIMITE_INT, corrente->n_reclamacoes
  );
  
  fclose(db_usuarios);
  
  return USUARIOS_SUCESSO;
  
  
}

usuarios_condRet usuarios_limpar(){
  /* Fechamos qualquer sessão aberta */
  if(usuarios_logout() != USUARIOS_SUCESSO) return USUARIOS_FALHA_FECHARSESSAO;
  /* Limpamos o grafo */
  if(destroi_grafo(&usuarios_grafo) != SUCESSO) return USUARIOS_FALHA_LIMPAR;
  
  return USUARIOS_SUCESSO;
}

/*!
 * @brief Função que retorna o identificador máximo de usuário do programa
 * 
 * Serve para mostrar os usuários do programa pois o identificador é 
 * único e ordenado de 1,2,3,...,max
 *
 * Para mostrar mais dados basta rodar a função usuarios_retornaDados
*/
unsigned int usuarios_maxIdentificador(){
  return usuarios_identificador_max;
}

/*!
 * @brief Função que retorna uma lista de identificadores dos amigos
 * do usuário passado pretendido
 *
 * Retorna por referência um array de unsigned int
 * positivo.
*/
usuarios_condRet usuarios_listarAmigos(unsigned int identificador, usuarios_uintarray *retorno) {
  tpUsuario *nodo, *corrente;
  grafo_lista_no *listaVizinhos;
  unsigned int posicaoGrafo;
    
  /* Devemos buscar o nodo de identificador passado */
  usuarios_buscaLimitada(identificador, &nodo, &posicaoGrafo);
  if(nodo == NULL) return USUARIOS_FALHA_ACESSORESTRITO;
  
  /* Geramos o vetor */
  //*retorno = (usuarios_uintarray *)malloc(sizeof(usuarios_uintarray));
  retorno->length = 0;
  retorno->array = NULL;
  
  /* Buscamos os nós vizinhos */
  listaVizinhos = vizinhos(usuarios_grafo, posicaoGrafo);
  for(;listaVizinhos != NULL;listaVizinhos=(grafo_lista_no *)listaVizinhos->prox_no){
    corrente = (tpUsuario *)grafo_busca_no(usuarios_grafo, listaVizinhos->valor, 0)->dados;
    
    /* Verificamos se há um arco vindo no sentido contrário */
    if(adjacente(usuarios_grafo, listaVizinhos->valor, posicaoGrafo) == ADJACENTES)  {
      retorno->array = (unsigned int *)realloc(retorno->array, (++retorno->length)*sizeof(unsigned int));
      retorno->array[retorno->length-1] = corrente->identificador;
    }
  }
  
  return USUARIOS_SUCESSO;
  
}

