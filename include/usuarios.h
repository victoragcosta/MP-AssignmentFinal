/*!
 * @brief Header das estruturas de usuário
*/

#ifndef HEADER_USUARIOS
#define HEADER_USUARIOS

/*!
 * @brief Definições para limite do tamanho dos campos 
 * a respeito das informações do usuário
*/

#define USUARIOS_LIMITE_NOME 40
#define USUARIOS_LIMITE_USUARIO 20
#define USUARIOS_LIMITE_SENHA 20
#define USUARIOS_LIMITE_ENDERECO 40
#define USUARIOS_LIMITE_EMAIL 30

/*!
 * @brief Arquivos do banco de dados a respeito dos usuários
*/
#define USUARIOS_DB "../../db/usuarios.txt"
#define USUARIOS_DB_AMIGOS "../../db/amigos.txt"

/*!
 * @brief Estrutura de numeração para as formas de pagamento
*/

typedef enum {
	BOLETO,
	CARTAO_DEBITO,
	CARTAO_CREDITO,
	PAYPAL
} usuarios_forma_de_pagamento;

/*!
 * @brief Estrutura de numeração para os estados possíveis de um
 * usuário.
 * 
 * Por exemplo estado de usuário inativo por falta de
 * confirmação do email ou usuário inativo por falta de aceitação
 * dos termos de uso.
*/

typedef enum {
	INATIVO_EMAIL,
	INATIVO_TERMOSDEUSO,
	INATIVO_ABUSO,
	ATIVO
} usuarios_estado_de_usuario;

/*! 
 * @brief Estrutura de numeração para os tipos de conta
*/

typedef enum {
	CONSUMIDOR,
	OFERTANTE,
	ADMINISTRADOR
} usuarios_tipo_usuario;

/*!
 * @brief Estrutura de um usuário, 
 * dado a ser referenciado na estrutura de grafos
*/

typedef struct tpUsuario {
	unsigned int identificador;
	char nome[USUARIOS_LIMITE_NOME];
	char usuario[USUARIOS_LIMITE_USUARIO];
	char email[USUARIOS_LIMITE_EMAIL];
	char senha[USUARIOS_LIMITE_SENHA];
	char endereco[USUARIOS_LIMITE_ENDERECO];
	usuarios_forma_de_pagamento formaPagamento;
	usuarios_tipo_usuario tipo;
	usuarios_estado_de_usuario estado;
	double avaliacao;
	unsigned int n_avaliacao;
	unsigned int n_reclamacoes;	
} tpUsuario;

/*!
 * @brief Condições de retorno das funções deste módulo
*/

typedef enum {
	USUARIOS_SUCESSO,
	USUARIOS_FALHA_LERDB,
	USUARIOS_FALHA_ADICIONAR_GRAFO,
	USUARIOS_FALHA_INSERIR_DADOS,
	USUARIOS_FALHA_EMAIL_INVALIDO,
	USUARIOS_FALHA_SENHAS_INVALIDAS,
	USUARIOS_FALHA_GRAFONULL,
	USUARIOS_ARGUMENTOINVALIDO,
	USUARIOS_USUARIOEXISTE,
	USUARIOS_DADOS_REPETICAO,
	USUARIOS_DADOS_OK,
	USUARIOS_FALHA_DADOSINCORRETOS,
	USUARIOS_FALHA_ARGUMENTOSINVALIDOS,
	USUARIOS_FALHA_SESSAOABERTA,
	USUARIOS_FALHA_LIMPAR,
	USUARIOS_FALHA_FECHARSESSAO,
	USUARIOS_FALHA_CARACTERESILEGAIS,
	USUARIOS_DB_CORROMPIDO,
	USUARIOS_GRAFO_CORROMPIDO,
	USUARIOS_FALHA_CRIARAMIZADE,
	USUARIOS_AMIZADEINVALIDA,
	USUARIOS_AMIZADEJASOLICITADA,
	USUARIOS_FALHACRIARAMIZADE,
	USUARIOS_FALHAUSUARIONAOEXISTE,
	USUARIOS_FALHA_INATIVO,
  USUARIOS_FALHA_ACESSORESTRITO
} usuarios_condRet;

/*!
 * @brief Estrutura com a relação entre dois usuários
*/
typedef enum {
	AMIGOS,
	AGUARDANDOCONFIRMACAO, /* Usuário A pede amizade a B e B não respondeu, usuário A está neste estado*/
	ACONFIRMAR, /* Usuário A pede amizade a B e B não respondeu, usuário B está neste estado*/
	NENHUMA,
	ERRO
} usuarios_relacao;

/*!
 * @brief Estrutura para os argumentos da função usuarios_cadastro
*/

typedef struct usuarios_cadastro_argumentos {
	const char *validos;
	int tamanho;
	char *destino;
} usuarios_cadastro_argumentos;

usuarios_condRet usuarios_cadastro(int, ...);
usuarios_condRet usuarios_carregarArquivo();
usuarios_condRet usuarios_login(char *, char *);
usuarios_condRet usuarios_logout();
usuarios_condRet usuarios_retornaDados(unsigned int, char *, void *);
usuarios_condRet usuarios_limpar();
usuarios_condRet usuarios_criarAmizade(unsigned int);
usuarios_relacao usuarios_verificarAmizade(unsigned int);
usuarios_condRet usuarios_atualizarDados(unsigned int, char *, ...);
usuarios_condRet usuarios_listarAmigos(unsigned int);

#endif


