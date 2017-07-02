// Módulo de usuários

/**
 * @file usuarios.c
 * @brief Implementação do módulo de usuários
 */

#include "usuarios.h"

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
 * @fn int usuarios_max()
 * @brief Função que retorna o identificador máximo de usuário do programa. Serve para mostrar os usuários do programa pois o identificador é único e ordenado de 1,2,3,...,max
 *
 * @return Retorna o identificador máximo do usuário
 *
 * Assertivas de entrada:
 *  - Existe um grafo de usuários consistente já carregado no módulo
 *
 * Assertivas de saída:
 *  - O grafo de usuários não será afetado com essa leitura
 *
 * Assertivas estruturais:
 *  - Nenhuma
 * 
 * Assertivas de contrato:
 *  - Nenhuma
 * 
 * Requisitos:
 *  - Nenhum
 *
 * Hipóteses:
 *  - Nenhuma
 *
 */

int usuarios_max(){
  return usuarios_contador;
}

/*!
 * @fn static usuarios_condRet usuarios_verificaRepeticao(const char *argumento, char *dado)
 * @brief Função que verifica se há repetição nos dados
 * @param argumento Define o tipo de dado a ser verificado no grafo de usuários
 * @param dado O dado a verificar repetição no grafo de usuários
 * @return Retorna uma instância usuarios_condRet:
 *  - USUARIOS_FALHA_GRAFONULL se não houver um grafo de usuários carregado; 
 *  - USUARIOS_GRAFO_CORROMPIDO se durante o percorrimento for detectado uma contradição na estrutura; 
 *  - USUARIOS_DADOS_REPETICAO se o dado passado for repetido;
 *  - USUARIOS_DADOS_OK se não for encontrado nenhum dado desse campo igual no grafo; 
 *  - USUARIOS_ARGUMENTOINVALIDO se o tipo de argumento passado não for válido
 * 
 * A função busca no grafo de usuários se já há algum usuário com o dado
 * igual ao do argumento passado
 * 
 * @code
 * usuarios_verificaRepeticao("nome", "João Antônio");
 * @endcode
 *
 * Observação, a verificação de nome ignora se o caracter é caixa alta ou não
 *
 * Assertivas de entrada:
 *  - Há um grafo carregado
 *  - O argumento passado é um desses: "usuario", "email"
 *
 * Assertivas de saída:
 *  - Nenhum dado passado para a função será alterado
 *  - Nenhum dado global do módulo será alterado
 *
 * Assertivas estruturais:
 *  - Os dados são um strings finalizadas com '\0'
 * 
 * Assertivas de contrato:
 *  - Nenhuma
 * 
 * Requisitos:
 *  - Nenhum
 *
 * Hipóteses:
 *  - Nenhuma
 * 
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
 * @fn static int usuarios_condParada_login(tpUsuario *corrente, va_list argumentos)
 * @brief Condição de parada para usuario e senha corretos do login, usado em usuarios_busca
 * @param corrente Ponteiro para uma estrutura de tipo de usuário
 * @param va_list argumentos Lista de argumentos passados na seguinte ordem: string de usuário e string de senha
 * @return Inteiro não nulo se os usuário e senha de corrente coincidirem com os passados via va_list, inteiro nulo caso contrário
 *
 * Assertivas de entrada:
 *  - corrente deve ser não nulo
 *  - va_list tem dois argumentos do tipo char *
 * 
 * Assertivas de saida:
 *  - Nenhum dado é alterado
 *
 * Assertivas estruturais:
 *  - Os elementos de tpUsuario usuario e senha são strings finalizadas com '\0'
 *  - Os argumentos passados via va_list são strings finalizadas com '\0'
 *
 * Assertivas de contrato:
 *  - A função vai retornar verdade quando os dois parâmetros para login de corrente for igual aos parâmetros passados em va_list.
 *
 * Requisitos:
 *  - Biblioteca string.h e stdarg.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
 */

static int usuarios_condParada_login(tpUsuario *corrente, va_list argumentos){
  return !strcmp(corrente->usuario, va_arg(argumentos, char *)) && !strcmp(corrente->senha, va_arg(argumentos, char *));
}

/*!
 * @fn static usuarios_condRet usuarios_busca(int condParada(tpUsuario *, va_list), tpUsuario **retorno, unsigned int *indice, ...)
 * @brief Função de busca no grafo de usuários dada uma condição de parada condParada
 * @param condParada uma função que retorne um inteiro e receba como argumentos um ponteiro para tpUsuario e um va_list, deve ser a condição de parada de busca no grafo retornando verdade caso chege-se a um nodo que satisfaz a condição
 * @param retorno um endereço de um ponteiro para tpUsuario
 * @param indice um endereço para um inteiro
 * @param ... os argumentos a serem passados a cada iteração para a função de condição de parada
 * @return Retorna uma instância usuarios_condRet que assume: 
 *  - USUARIOS_FALHA_GRAFONULL se o grafo de usuários do módulo for NULL; 
 *  - USUARIOS_GRAFO_CORROMPIDO se durante o percorrimento do grafo for encontrado uma inconsistência na estrutura; 
 *  - USUARIOS_SUCESSO caso seja encontrado um nodo que satisfaz a condição passada junto aos argumentos em ...;
 *  - USUARIOS_FALHA_DADOSINCORRETOS se percorreu todo o grafo e nenhum nodo satisfez a condição.
 * 
 * Recebe uma função de condição de parada, e retorna por referência os dados de usuário e o índice no grafo (identificador)
 * Recebe uma lista de argumentos depois disso exigidos pela função de condição de parada passados
 * É uma função estática do módulo
 * 
 * @code
 * usuarios_busca(usuarios_condParada_login, &retorno, NULL, "joão", "123456");
 * @endcode
 * 
 * Este exemplo encontra no grafo um usuário joão de senha 123456 e retorna por referência a retorno. Retorna por valor a condição de retorno, se for USUARIOS_SUCESSO, significa que a atribuição a retorno foi feita com sucesso. Se não encontrar retorna USUARIOS_FALHA_DADOSINCORRETOS. É uma função estática do módulo
 *
 * Assertivas de entrada:
 *  - O grafo de usuários não é nulo e é consistente
 *  - Foi passado o número correto de argumentos na elípse dada a condição de parada condParada
 *
 * Assertivas de saída:
 *  - Nenhum nodo do grafo é afetado
 *  - retorno aponta para o nodo que satisfaz a condição se o retorno da função for USUARIOS_SUCESSO e retorno for não nulo.
 *  - o valor referenciado por indice contém a posição do nodo no grafo (seu identificador) se o retorno da função for USUARIOS_SUCESSO e indice for não nulo.
 *
 * Assertivas estruturais:
 *  - O grafo do módulo é consistente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - stdarg.h, stdlib.h, string.h, grafo.h
 * 
 * Hipóteses:
 *  - Nenhuma.
 *
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
 * @fn static void usuarios_lerString(FILE *arquivo, char *dstStr, unsigned int limite)
 * @brief Função leitora de string em um arquivo de dados
 * @param arquivo O arquivo a ser lido
 * @param dstStr String já alocada estaticamente que receberá o dado do arquivo
 * @param limite Um inteiro indicando o limite de caracteres a serem colocados em dstStr sem incluir '\0', portanto dstStr deve ter ao menos limite+1 bytes alocados
 * @return Não retorna
 * 
 * Lê uma string do arquivo e salva em dstStr previamente alocada,
 * recebe um limite de gravação. É uma função estática. Lê uma string enquanto o limite não for alcançado, e não for encontrado os caracteres '\t' e '\n'
 *
 * Assertivas de entrada:
 *  - O arquivo já foi aberto com permissões de leitura
 *  - dstStr foi alocado previamente com pelo menos limite+1 bytes
 *  - se limite é 0, dstStr tem pelo menos 2 bytes alocados
 * 
 * Assertivas de saída:
 *  - O arquivo não é alterado, mas seu ponteiro de posição é colocado no próximo caractere depois do fim da string, se o próximo caracter for '\t' ou '\n' os pulamos
 * 
 * Assertivas de contrato:
 *  - dstStr será uma string finalizada com '\0' com as informações do arquivo dado o limite a posição inicial no arquivo e os limitadores '\t', '\n' e EOF.
 *
 * Requisitos:
 *  - stdio.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
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
 * @fn usuarios_condRet usuarios_carregarArquivo()
 * @brief Função carregadora do arquivo de usuários e suas relações
 * @return Uma instância usuarios_condRet que assume: 
 *  - USUARIOS_SUCESSO se conseguir carregar com sucesso o grafo de usuários a partir do arquivo; 
 *  - USUARIOS_FALHA_ADICIONAR_GRAFO se falhar em criar um vértice no grafo; 
 *  - USUARIOS_FALHA_INSERIR_DADOS se falhar em definir os dados tirados do arquivo no vértice que acabou de ser criado; 
 *  - USUARIOS_DB_CORROMPIDO se ao ler o arquivo de amizades encontrar uma aresta que já existe no grafo; 
 *  - USUARIOS_FALHA_CRIARAMIZADE se não conseguir criar e definir uma aresta entre dois nós do grafo para representar uma amizade;
 *  - USUARIOS_FALHA_ALOCAR se não conseguir alocar memória para um nó do grafo.
 *
 * A relação de um usuário com o outro é a relação de amizade, 
 * o grafo é direcionado, assim a relação entre A e B 
 * de fato existe se e só se existir uma aresta
 * indo de A a B e outra indo de B a A.
 * Se isso não ocorrer temos a pendencia de uma relação, na qual
 * aguarda-se a confirmação da parte solicitada para criá-la.
 * 
 * Retorna USUARIOS_SUCESSO caso tenha carregado o arquivo corretamente e gerado o grafo de usuário. Deve ser a primeira função a ser carregada para que o módulo funcione.
 *
 * Assertivas de entrada:
 *  - O arquivo indicado por USUARIOS_DB existe e é legível pelo programa, se não existir a função criará um arquivo e fechará com um grafo não nulo mas sem nós.
 *  - O arquivo indicado por USUARIOS_DB_AMIGOS existe e é legível pelo programa, se não existir mas houverem usuários a função criará um arquivo e fechará com um grafo sem arestas.
 *
 * Assertivas de saída:
 *  - O grafo de usuários é carregado junto as relações entre os nós
 *  - Haverão arquivos USUARIOS_DB e USUARIOS_DB_AMIGOS
 *  - Os contadores globais do módulo de usuários usuarios_contador e usuarios_contador_amizades conterão os maiores identificadores de vértices no grafo e arestas no grafo respectivamente.
 *
 * Assertivas de contrato:
 *  - O arquivo deve ter a estrutura indicada por USUARIOS_DB_ESTRUTURA
 * 
 * Requisitos:
 *  - stdio.h, stdlib.h, grafo.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
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
    if(corrente == NULL) {
      fclose(db_usuarios);
      return USUARIOS_FALHA_ALOCAR;
    }
    
    /* Lemos do arquivo */
    fscanf(db_usuarios, "%u%*[^\t]\t", &(corrente->identificador));
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
 * @fn usuarios_condRet usuarios_cadastro(int n, ...)
 * @brief Função de cadastro de usuários
 * @param Recebe n=8 como parâmetro (necessário para uso da elipse)
 * @param (...) Deverá conter 8 pares de argumentos seguindo essa ordem: const char *tipo, dado com dado podendo assumir os tipos char *, usuarios_forma_de_pagamento, usuarios_tipo_usuario
 * @return Retorna uma instância usuarios_condRet que assume: 
 *  - USUARIOS_FALHA_GRAFONULL se o grafo de usuários for NULL; 
 *  - USUARIOS_FALHA_ARGUMENTOSINVALIDOS se n não for 8; 
 *  - USUARIOS_FALHA_CARACTERESILEGAIS se houver algum caracter inválido nos argumentos passados como '\\t' e '\\n'; 
 *  - USUARIOS_FALHA_EMAIL_INVALIDO se o email não for válido; 
 *  - USUARIOS_FALHA_SENHAS_INVALIDAS se as senhas não coincidem; 
 *  - USUARIOS_USUARIOEXISTE se houver repetição de dados; 
 *  - USUARIOS_FALHA_ADICIONAR_GRAFO se não conseguir criar um vértice no grafo; 
 *  - USUARIOS_FALHA_INSERIR_DADOS se não conseguir atribuir valores ao vértice no grafo; 
 *  - USUARIOS_SUCESSO se tiver criado um vértice com sucesso no grafo e atualizado o arquivo de dados com ele
 * 
 * Recebe como parâmetros nome, endereço, email, senha repetida duas vezes, forma de pagamento, tipo de usuário da seguinte maneira:
 * 
 * @code 
 * usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR);
 * @endcode
 *
 * Assertivas de entrada: 
 *  - o arquivo USUARIOS_DB já existe, isto é a função usuarios_carregarArquivo já foi executada. 
 *  - Devem ser passados o número correto de argumentos
 *  - Todos os argumentos devem ser passados: usuario, nome, email, endereco, senha, senha_confirmacao, formaPagamento e tipo.
 *
 * Assertivas de saída:
 *  - O arquivo de dados de usuário é atualizado com o novo usuário
 *  - O grafo passa a ter o novo vértice para o usuário
 *  - Nenhum outro vértice ou aresta do grafo é afetado
 *  - O usuário é ATIVO imediatamente depois do cadastro
 *  - O usuário tem um identificador maior que todos os outros no grafo
 *  - A variável global do módulo usuarios_contador é acrescida de 1
 *
 * Assertivas estruturais:
 *  - O grafo é consistente e não nulo
 *  - Todas as strings passadas na elipse são terminadas com '\0'
 *
 * Assertivas de contrato:
 *  - A função cria um nó para o usuário no cadastro se atender aos requisitos de validação no cadastro e houver memória para o arquivo de dados e na RAM
 *
 * Requisitos:
 *  - stdarg.h, stdio.h, stdlib.h, grafo.h
 * 
 * Hipóteses:
 *  - Nenhuma.
 *
 */

usuarios_condRet usuarios_cadastro(int n, ...){
  FILE *db_usuarios;
  
  /* Verificamos se o grafo de usuários foi iniciado */
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
 * @fn int usuarios_sessaoAberta()
 * @brief Função que verifica se há uma sessão aberta
 * @return Retorna 0 se não tiver e 1 se tiver
 * 
 * Assertivas de entrada:
 *  - Nenhuma.
 * 
 * Assertivas de saída:
 *  - O retorno será 1 ou 0
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - A função garante que usuarios_sessao é não nulo, indicativo suficiente de que haja sessão ou não. Mas se usuarios_sessao não for consistente com o grafo, esta função não detectará
 *
 * Requisitos:
 *  - Nenhum
 * 
 * Hipóteses:
 *  - usuarios_sessao é consistente com o grafo
 *
 */

int usuarios_sessaoAberta(){
  if(usuarios_sessao == NULL) return 0;
  return 1;
}

/*!
 * @fn usuarios_condRet usuarios_login(char *usuario, char *senha)
 * @brief Buscamos a conta correspondente ao login e senha passados
 * @param usuario string finalizada com '\0' indicando o usuário a ser buscado no grafo
 * @param senha string finalizada com '\0' indicando a senha a ser buscada no grafo
 * @return Instância usuarios_condRet que assume: 
 *  - USUARIOS_FALHA_SESSAOABERTA se já houver uma sessão aberta; 
 *  - USUARIOS_GRAFO_CORROMPIDO se não encontrar o usuário; 
 *  - USUARIOS_FALHA_INATIVO se o usuário for INATIVO; 
 *  - USUARIOS_SUCESSO se encontrar e iniciar a sessão com sucesso.
 * 
 * Recebe as strings usuário e senha, se ambos coincidirem para um nó, esse nó passa ser o nó da sessão
 *
 * Assertivas de entrada:
 *  - O grafo foi carregado e é consistente
 * 
 * Assertivas de saída:
 *  - O grafo não será alterado
 *  - Haverá sessão se e só se os dados coincidirem
 *
 * Assertivas estruturais:
 *  - Usuario e senha terminam com '\0' e não excedem o limite de cada um definido em usuarios.h
 *
 * Assertivas de contrato:
 *  - Nenhuma.
 *
 * Requisitos:
 *  - grafo.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
 */

usuarios_condRet usuarios_login(char *usuario, char *senha){
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
 * @fn usuarios_condRet usuarios_logout()
 * @brief Função de logout
 * @retorno Sempre retorna USUARIOS_SUCESSO
 * 
 * Finaliza a sessão aberta
 *
 * Assertivas de entrada:
 *  - Nenhuma
 * 
 * Assertivas de saída:
 *  - o global do módulo usuarios_sessao é NULL
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Assertivas estruturais:
 *  - Nenhuma
 * 
 * Requisitos:
 *  - Nenhum
 * 
 * Hipóteses:
 *  - Nenhuma
 *
 */

usuarios_condRet usuarios_logout(){
  usuarios_sessao = NULL;
  return USUARIOS_SUCESSO;
}

/*!
 * @fn usuarios_relacao usuarios_verificarAmizade(unsigned int identificador)
 * @brief Função verifica um usuário é amigo do usuário na sessão
 * @param identificador Um inteiro positivo que represete o id de um usuário no grafo.
 * @return Retorna usuarios_relacao, podendo ser ERRO, AMIGOS, NENHUMA, ACONFIRMAR ou AGUARDANDOCONFIRMACAO. 
 *  - ERRO, caso algum erro ocorra, como a assertiva de entrada não ser respeitada; AMIGOS, se forem amigos; 
 *  - NENHUMA, se não existir relação direta entre eles; 
 *  - ACONFIRMAR, se o usuário pesquisado não tiver confirmado a amizade; 
 *  - AGUARDANDOCONFIRMACAO, se o usuário da sessão estiver por aceitar a amizade ou não.
 *
 * Recebe o identificador do usuário a ser verificada a relação de amizade com o usuário da sessão
 * 
 * Assertivas de entrada:
 *  - Há uma sessão aberta
 *  - o identificador refere-se a um nó no grafo
 * 
 * Assertivas de saída:
 *  - O grafo não é alterado
 *
 * Assertivas estruturais:
 *  - Nenhuma
 *
 * Assertivas de contrato:
 *  - Nenhuma
 * 
 * Requisitos:
 *  - grafo.h
 *
 * Hipóteses:
 *  - O usuário é ATIVO
 * 
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
 * @fn usuarios_condRet usuarios_criarAmizade(unsigned int identificador)
 * @brief Função que cria parte de uma relação de amizade na sesão iniciada para algum outro cliente
 * @param identificador Um inteiro positivo que represete o id de um usuário no grafo.
 * @return Retorna uma instância usuarios_condRet que assume:
 * - USUARIOS_FALHA_GRAFONULL se o grafo de usuários for NULL
 * - USUARIOS_FALHA_SESSAONULA se não houver sessão
 * - USUARIOS_AMIZADEINVALIDA se o identificador passado for o mesmo da sessão
 * - USUARIOS_GRAFO_CORROMPIDO se o grafo estiver inconsistente
 * - USUARIOS_AMIZADEJASOLICITADA se a aresta na direção SESSÃO -> identificador já existir
 * - USUARIOS_FALHA_CRIARAMIZADE se não conseguir criar uma aresta ou não conseguir definir um valor para ela
 * - USUARIOS_FALHAUSUARIONAOEXISTE se o usuário passado inexiste
 * - USUARIOS_SUCESSO se gravou no arquivo e salvou no grafo uma aresta que vai da SESSAO para identificador representando um lado da relação.
 *
 * Deve receber o identificador do amigo pretendido
 * 
 * Assertivas de entrada:
 *  - O identificador representa um nó do grafo
 *  - O identificador não é igual ao identificador da sessão
 *  - Há uma sessão aberta
 *  - O programa tem permissão de a+ sobre o arquivo de amizades definido em USUARIOS_DB_AMIGOS
 *
 * Assertivas de saída:
 *  - Haverá uma aresta entre o nó da sessão e o nó identificado pelo identificador
 *  - Nenhum dado de usuário é alterado
 *  - O arquivo de amizades USUARIOS_DB_AMIGOS terá a relação entre os nós
 * 
 * Assertivas estruturais:
 *  - O grafo é consistente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - grafo.h
 *
 * Hipóteses:
 *  - identificador se refere a um usuário ATIVO
 *
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
 * @fn usuarios_condRet usuarios_removerAmizade(unsigned int identificador_A, unsigned int identificador_B)
 * @brief Função que remove uma relação de amizade
 * @param identificador_A id de um nó no grafo, se for 0 do nó da sessão
 * @param identificador_B id de um outro nó no grafo
 * @return Retorna uma instância usuarios_condRet que assume:
 *  - USUARIOS_FALHA_GRAFONULL se o grafo for NULL;
 *  - USUARIOS_FALHA_SESSAONULA se passou 0 em identificador_A e não há sessão aberta;
 *  - USUARIOS_FALHA_DADOSINCORRETOS se não consegue carregar o usuário da sessão;
 *  - USUARIOS_FALHA_LERDB se falha ao ler com permissão de atualização USUARIOS_DB_AMIGOS ("r+")
 *  - USUARIOS_FALHA_REMOVER_AMIZADE se não conseguir remover as arestas no grafo
 *  - USUARIOS_SUCESSO se tiver atualizado o arquivo de amizades e deletado as arestas do grafo
 *
 * Recebe os identificadores dos usuários A e B, se A for 0 assume que é da sessão
 *
 * Assertivas de entrada:
 *  - os identificadores passados são nós diferentes no grafo
 *  - o grafo foi carregado
 *  - se identificador_A é 0, há sessão aberta
 *  - o arquivo USUARIOS_DB_AMIGOS existe e o programa pode usá-lo com permissão "r+"
 * 
 * Assertivas de saída:
 *  - Não haverá arcos indo na direção de A até B nem de B até A
 *  - No arquivo USUARIOS_DB_AMIGOS os registros referentes aos arcos serão sobrescritos com 0.
 *
 * Assertivas estruturais:
 *  - O grafo é consistente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - grafo.h, stdio.h
 *
 * Hipóteses:
 *  - Nenhuma
 *
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
 * @fn usuarios_condRet usuarios_retornaDados(unsigned int identificador, const char *nomeDado, void *retorno)
 * @brief Retorna os dados do usuário do identificador passado
 * @param identificador Identificador do nó a buscar o dado, se for 0 usa-se o nó da sessão
 * @param nomeDado o dado a ser buscado. Valores válidos: "identificador", "usuario", "nome", "senha", "email", "endereco", 
 * "formaPagamento", "tipo", "estado", "avaliacao", "n_avaliacao", "n_reclamacoes"
 * @param retorno Retorno por referência do dado pretendido, deve ser feito casting para void *
 * @return Instância usuarios_condRet que assume:
 *  - USUARIOS_FALHA_GRAFONULL se o grafo for NULL;
 *  - USUARIOS_GRAFO_CORROMPIDO se o nó relativo ao id for NULL;
 *  - USUARIOS_SUCESSO se conseguir passar por referência o dado pretendido ou se o argumento passado for inválido;
 *
 * Se identificador for zero, retornamos os dados da sessão
 * 
 * Retorna o dado por referência, recebe uma string com o dado a ser buscado
 * 
 * @code
 * usuarios_retornaDados(0, "nome", (void *)string_nome);
 * @endcode
 * 
 * Assertivas de entrada:
 *  - O grafo é consistente e não nulo
 *  - O identificador refere-se a um nó do grafo ou, se for 0, há uma sessão aberta
 *  - nomeDado é uma string válida
 *  - retorno é um ponteiro para void 
 *  - Se retorno for um ponteiro para string, essa string já está alocada como limite associado a ela corretamente.
 * 
 * Assertivas de saída:
 *  - O grafo não é alterado
 *  - Se o retorno for string, essa string será uma cópia dos dados no grafo, não um ponteiro para eles
 *
 * Assertivas estruturais:
 *  - nomeDado termina com '\0'
 *
 * Assertivas de contrato:
 *  - Nenhuma.
 *
 * Requisitos:
 *  - stdlib.h, string.h
 *
 * Hipóteses:
 *  - Nenhuma
 */
 
usuarios_condRet usuarios_retornaDados(unsigned int identificador, const char *nomeDado, void *retorno) {
  unsigned int i = 0;
  tpUsuario *dados;
    
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
 * @fn usuarios_condRet usuarios_atualizarDados(unsigned int identificador, const char *nomeDado, ...)
 * @brief Atualiza dados do usuário de identificador passado
 * @param identificador Id do usuário no grafo a alterar um dado, se for 0 assume-se da sessão
 * @param nomeDado o dado a ser alterado, pode ser: "identificador", "usuario", "nome", "senha", "email", "endereco", "formaPagamento", "tipo", "estado", "avaliacao", "n_avaliacao", "n_reclamacoes".
 * @param (...) Um argumento de tipo char *, usuarios_forma_de_pagamento, usuarios_tipo_usuario, usuarios_estado_de_usuario, double ou unsigned int
 * @return Uma instância do tipo usuarios_condRet que assume:
 *  - USUARIOS_FALHA_GRAFONULL se o grafo for NULL;
 *  - USUARIOS_GRAFO_CORROMPIDO se o nodo associado ao id for NULL;
 *  - USUARIOS_FALHA_LERDB se não consegue abrir o banco de dados de usuários USUARIOS_DB como "r+";
 *  - USUARIOS_SUCESSO se atualizar no grafo e no arquivo a alteração pretendida ou se o nomeDado não for válido;
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
 * Assertivas de entrada:
 *  - O grafo é consistente e não nulo
 *  - Se identificador é 0, há sessão
 *  - É passado exatamente 1 argumento na elípse (...)
 *  - nomeDado é válido
 *  - Há permissões para abrir o arquivo USUARIOS_DB como "r+"
 *
 * Assertivas de saída:
 *  - O dado pretendido é atualizado no grafo e no arquivo respeitando os limites do campo
 *  - Nenhum outro dado é alterado
 * 
 *  Assertivas estruturais:
 *  - String passadas na elipse terminam com '\0' e respeitam o limite dos campos
 * 
 * Assertivas de contrato:
 *  - Os dados no grafo e no arquivo a serem alterados serão alterados usando os dados passados pelos parâmetros
 *
 * Requisitos:
 *  - grafo.h, string.h, stdlib.h, stdio.h 
 *
 * Hipóteses:
 *  - Nenhuma
 * 
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
 * @fn usuarios_condRet usuarios_limpar()
 * @brief Apaga o grafo de usuários da memória e faz logout na sessão aberta
 * @return Retorna uma instância do tipo usuarios_condRet que assume:
 *  - USUARIOS_FALHA_FECHARSESSAO se não conseguir fazer logout na sessão se houver sessão aberta;
 *  - USUARIOS_FALHA_LIMPAR se não conseguir destruir o grafo da memória.
 *  - Retorna USUARIOS_SUCESSO se não ocorrerem erros.
 *
 * Assertivas de entrada:
 *  - Nenhuma
 *
 * Assertivas de saída:
 *  - Não haverá mais grafo nem sessão
 *
 * Assertivas estruturais:
 *  - O grafo é consistente
 * 
 * Assertivas de contrato:
 *  - Nenhuma
 * 
 * Requisitos:
 *  - grafo.h
 *
 * Hipóteses:
 *  - Nenhuma
 * 
 */
 
usuarios_condRet usuarios_limpar(){
  /* Fechamos qualquer sessão aberta */
  if(usuarios_logout() != USUARIOS_SUCESSO) return USUARIOS_FALHA_FECHARSESSAO;
  /* Limpamos o grafo */
  if(destroi_grafo(&usuarios_grafo) != SUCESSO) return USUARIOS_FALHA_LIMPAR;
  
  return USUARIOS_SUCESSO;
}

/*!
 * @fn usuarios_condRet usuarios_listarAmigos(unsigned int identificador, usuarios_uintarray *retorno)
 * @brief Função que retorna uma lista de identificadores dos amigos do usuário passado pretendido, se o identificador for 0, usa a sessão
 * @param identificador Id do usuário a buscar amigos, se for 0 usa a sessão
 * @param retorno Lista de amigos a ser passada por referência e alocada na função. A cabeça do array deve ser alocada estaticamente:
 * 
 * @code
 * usuarios_uintarray array;
 * usuarios_listarAmigos(0, &array);
 * @endcode
 * 
 * Vai compor o array com os identificadores dos amigos.
 *
 * Deve-se liberar o array quando não mais usado usando usuarios_freeUint.
 *
 * @return A função retorna uma instância que assume:
 *  - USUARIOS_FALHA_ACESSORESTRITO se o usuário do identificador for NULL;
 *  - USUARIOS_SUCESSO se gerar o array com sucesso.
 *
 * Assertivas de entrada:
 *  - identificador é um nó do grafo
 *  - o grafo já foi carregado e é consistente
 *  - a cabeça array já foi alocada estaticamente
 *
 * Assertivas de saída:
 *  - O array conterá o número de amigos e os identificadores dos amigos do usuário passado no parâmetro
 *  - O grafo não é afetado
 * 
 * Assertivas estruturais:
 *  - o retorno é o endereço da cabeça de um usuarios_uintarray já alocado anteriormente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - grafo.h, stdlib.h
 *
 * Hipóteses:
 *  - Nenhuma
 * 
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
 * @fn usuarios_condRet usuarios_listarAmigosPendentes(unsigned int identificador, usuarios_uintarray *retorno)
 * @brief Função que retorna uma lista de identificadores dos amigos pendentes do usuário passado pretendido, se o identificador for 0, usa a sessão
 * @param identificador Id do usuário a buscar amigos pendentes, se for 0 usa a sessão
 * @param retorno Lista de amigos pendentes a ser passada por referência e alocada na função. A cabeça do array deve ser alocada estaticamente:
 * 
 * @code
 * usuarios_uintarray array;
 * usuarios_listarAmigosPendentes(0, &array);
 * @endcode
 * 
 * Vai compor o array com os identificadores dos amigos pendentes.
 *
 * Deve-se liberar o array quando não mais usado usando usuarios_freeUint.
 *
 * @return A função retorna uma instância que assume:
 *  - USUARIOS_FALHA_ACESSORESTRITO se o usuário do identificador for NULL;
 *  - USUARIOS_SUCESSO se gerar o array com sucesso.
 *
 * Assertivas de entrada:
 *  - identificador é um nó do grafo
 *  - o grafo já foi carregado e é consistente
 *  - a cabeça array já foi alocada estaticamente
 *
 * Assertivas de saída:
 *  - O array conterá o número de amigos pendentes e os identificadores dos amigos pendentes do usuário passado no parâmetro
 *  - O grafo não é afetado
 * 
 * Assertivas estruturais:
 *  - o retorno é o endereço da cabeça de um usuarios_uintarray já alocado anteriormente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - grafo.h, stdlib.h
 *
 * Hipóteses:
 *  - Nenhuma
 * 
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
 * @fn usuarios_condRet usuarios_listarAmigosdeAmigos(unsigned int identificador, usuarios_uintarray *retorno)
 * @brief Função que lista os amigos de amigos (excluíndo amigos)
 * @param identificador Id do usuário a buscar amigos de amigos, se for 0 usa a sessão
 * @param retorno Lista de amigos pendentes a ser passada por referência e alocada na função. A cabeça do array deve ser alocada estaticamente:
 * 
 * @code
 * usuarios_uintarray array;
 * usuarios_listarAmigosdeAmigos(0, &array);
 * @endcode
 * 
 * Vai compor o array com os identificadores dos amigos de amigos.
 *
 * Deve-se liberar o array quando não mais usado usando usuarios_freeUint.
 *
 * @return A função retorna uma instância que assume:
 *  - USUARIOS_FALHA_ACESSORESTRITO se o usuário do identificador for NULL;
 *  - USUARIOS_SUCESSO se gerar o array com sucesso.
 *
 * Assertivas de entrada:
 *  - identificador é um nó do grafo
 *  - o grafo já foi carregado e é consistente
 *  - a cabeça array já foi alocada estaticamente
 *
 * Assertivas de saída:
 *  - O array conterá o número de amigos de amigos e os identificadores dos amigos de amigos do usuário passado no parâmetro
 *  - O grafo não é afetado
 * 
 * Assertivas estruturais:
 *  - o retorno é o endereço da cabeça de um usuarios_uintarray já alocado anteriormente
 *
 * Assertivas de contrato:
 *  - Nenhuma
 *
 * Requisitos:
 *  - grafo.h, stdlib.h
 *
 * Hipóteses:
 *  - Nenhuma
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
 * @fn usuarios_condRet usuarios_freeUint(usuarios_uintarray *vetor)
 * @brief Função que desaloca memória de um usuarios_uintarray
 * @param vetor A cabeça do vetor usuarios_uintarray a ser desalocado
 * @return Retorna uma instância usuarios_condRet que assume:
 *  - USUARIOS_SUCESSO
 * 
 * Recebe o endereço de usuarios_uintarray
 *
 * Assertivas de entrada:
 *  - vetor não é NULL
 *
 * Assertivas de saída:
 *  - vetor->array será NULL e vetor->length será 0;
 *  - os dados em vetor->array serão perdidos e a memória liberada;
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
 *  - Nenhuma
 */

usuarios_condRet usuarios_freeUint(usuarios_uintarray *vetor){
  if(vetor->array != NULL) free(vetor->array);
  vetor->array = NULL;
  vetor->length = 0;
  return USUARIOS_SUCESSO;
}


