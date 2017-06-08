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
	USUARIOS_DADOS_OK
} usuarios_condRet;

usuarios_condRet usuarios_cadastro(char *, char *, char *, char *, char *, char *, usuarios_forma_de_pagamento, usuarios_tipo_usuario);
usuarios_condRet usuarios_carregarArquivo();

#endif


