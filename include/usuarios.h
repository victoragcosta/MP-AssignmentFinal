// Módulo de usuários - Cabeçalho

/**
 * @file usuarios.h
 * @brief Cabeçalho do módulo de usuários.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "aleatorio.h"
#include "grafo.h"

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
#define USUARIOS_LIMITE_DOUBLE 9
#define USUARIOS_LIMITE_INT 4

/*!
 * @brief Arquivos do banco de dados a respeito dos usuários
*/

#define USUARIOS_DB "../../db/usuarios.txt"
#define USUARIOS_DB_ESTRUTURA "%-4u\t%-20s\t%-40s\t%-30s\t%-20s\t%-40s\t%-4d\t%-4d\t%-4d\t%-9lf\t%-4u\t%-4u\n"
#define USUARIOS_DB_ESTRUTURA_SCAN "%4u%*c%20[^\t]\t%40[^\t]\t%30[^\t]\t%20[^\t]\t%40[^\t]\t%4d%*c%4d%*c%4d%*c%9lf%*c%4u%*c%4u\n"
#define USUARIOS_DB_AMIGOS "../db/amigos.txt"
#define USUARIOS_DB_AMIGOS_REGISTRO_TAMANHO 15 

/*!
 * @enum usuarios_forma_de_pagamento
 * @brief Estrutura de numeração para as formas de pagamento
*/

typedef enum {
	BOLETO, /**< Forma de pagamento em boleto bancário */
	CARTAO_DEBITO, /**< Forma de pagamento em cartão de débito */
	CARTAO_CREDITO, /**< Forma de pagamento em cartão de crédito */
	PAYPAL /**< Forma de pagamento usando PAYPAL */
} usuarios_forma_de_pagamento;

/*!
 * @enum usuarios_estado_de_usuario
 * @brief Estrutura de numeração para os estados possíveis de um
 * usuário.
 * 
 * Por exemplo estado de usuário inativo por falta de
 * confirmação do email ou usuário inativo por falta de aceitação
 * dos termos de uso.
*/

typedef enum {
	INATIVO_EMAIL, /**< Usuário não está ativo pois o e-mail não foi confirmado */
	INATIVO_TERMOSDEUSO, /**< Usuário inativo por não aceitar os termos de uso */
	INATIVO_ABUSO, /**< Usuário inativo por abuso */
	ATIVO /**< O usuário está ativo */
} usuarios_estado_de_usuario;

/*! 
 * @enum usuarios_tipo_usuario
 * @brief Estrutura de numeração para os tipos de conta
*/

typedef enum {
	CONSUMIDOR, /**< O usuário é consumidor */
	OFERTANTE, /**< O usuário é ofertante */
	ADMINISTRADOR  /**< O usuário é administrador */
} usuarios_tipo_usuario;

/*!
 * @typedef tpUsuario
 * @brief Estrutura de um usuário, dado a ser referenciado na estrutura de grafos
*/

typedef struct tpUsuario {
	unsigned int identificador; /**< Identificador único do usuário no grafo e no arquivo de dados */
	char nome[USUARIOS_LIMITE_NOME]; /**< Nome do cliente, não deve ultrapassar o limite de USUARIOS_LIMITE_NOME-1 caracteres */
	char usuario[USUARIOS_LIMITE_USUARIO]; /**< Usuário do cliente, único, não deve ultrapassar o limite de USUARIOS_LIMITE_USUARIO-1 caracteres */
	char email[USUARIOS_LIMITE_EMAIL]; /**< E-mail do cliente, não deve ultrapassar o limite de USUARIOS_LIMITE_EMAIL-1 caracteres */
	char senha[USUARIOS_LIMITE_SENHA]; /**< Senha do cliente, não deve ultrapassar o limite de USUARIOS_LIMITE_SENHA-1 caracteres */
	char endereco[USUARIOS_LIMITE_ENDERECO]; /**< Endereço do cliente, não deve ultrapassar o limite de USUARIOS_LIMITE_ENDERECO-1 caracteres */
	usuarios_forma_de_pagamento formaPagamento; /**< Forma de pagamento padrão */
	usuarios_tipo_usuario tipo; /**< Tipo do usuário, se é OFERTANTE, CONSUMIDOR ou ADMINISTRADOR */
	usuarios_estado_de_usuario estado; /**< Estado do usuário, ATIVO ou INATIVO por alguma razão */
	double avaliacao; /**< Avaliação do usuário, número de ponto flutuante de 0 a 5 */
	unsigned int n_avaliacao; /**< Número de avaliações feitas por outros usuários a este usuário */
	unsigned int n_reclamacoes;	/**< Número de reclamações feitas por outros usuários a este usuário, DEPRECATED, FORA DE USO */
} tpUsuario;

/*!
 * @enum usuarios_condRet
 * @brief Condições de retorno das funções deste módulo, cada condição é explicada na documentação da função que a retorna.
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
	USUARIOS_FALHA_SESSAONULA,
	USUARIOS_FALHA_CARACTERESILEGAIS,
	USUARIOS_DB_CORROMPIDO,
	USUARIOS_GRAFO_CORROMPIDO,
	USUARIOS_FALHA_CRIARAMIZADE,
	USUARIOS_AMIZADEINVALIDA,
	USUARIOS_AMIZADEJASOLICITADA,
	USUARIOS_FALHACRIARAMIZADE,
	USUARIOS_FALHAUSUARIONAOEXISTE,
	USUARIOS_FALHA_INATIVO,
  USUARIOS_FALHA_ACESSORESTRITO,
  USUARIOS_FALHA_LISTARAMIGOS,
  USUARIOS_FALHA_REMOVER_AMIZADE,
  USUARIOS_FALHA_ALOCAR
} usuarios_condRet;

/*!
 * @enum usuarios_relacao
 * @brief Estrutura com a relação entre dois usuários
*/
typedef enum {
	AMIGOS, /**< Os usuários A e B são amigos */
	AGUARDANDOCONFIRMACAO, /**< Usuário A pede amizade a B e B não respondeu, usuário A está neste estado */
	ACONFIRMAR, /**< Usuário A pede amizade a B e B não respondeu, usuário B está neste estado */
	NENHUMA, /**< Não há relação direta entre os usuários, mas podem ser amigos de amigos ainda */
	ERRO /**< Ocorreu um erro na função */
} usuarios_relacao;

/*!
 * @typedef usuarios_cadastro_argumentos
 * @brief Estrutura para os argumentos da função usuarios_cadastro, de uso único do módulo. Serve para facilitar na leitura de argumentos
*/

typedef struct usuarios_cadastro_argumentos {
	const char *validos; /**< Um argumento válido */
	int tamanho; /**< Tamanho em bytes que ocupa o dado do argumento */
	char *destino; /**< Onde será armazenado o dado do argumento */
} usuarios_cadastro_argumentos;

/*!
 * @typedef usuarios_uintarray
 * @brief Estrutura de array de inteiros
*/

typedef struct usuarios_uintarray {
  unsigned int length; /**< Número de elementos no array */
  unsigned int *array; /**< Ponteiro para os inteiros não negativos do array */
} usuarios_uintarray;

usuarios_condRet usuarios_cadastro(int, ...);
usuarios_condRet usuarios_carregarArquivo();
usuarios_condRet usuarios_login(char *, char *);
usuarios_condRet usuarios_logout();
usuarios_condRet usuarios_retornaDados(unsigned int, const char *, void *);
usuarios_condRet usuarios_limpar();
usuarios_condRet usuarios_criarAmizade(unsigned int);
usuarios_relacao usuarios_verificarAmizade(unsigned int);
usuarios_condRet usuarios_atualizarDados(unsigned int, const char *, ...);
usuarios_condRet usuarios_listarAmigos(unsigned int, usuarios_uintarray *);
usuarios_condRet usuarios_listarAmigosdeAmigos(unsigned int, usuarios_uintarray *);
usuarios_condRet usuarios_listarAmigosPendentes(unsigned int, usuarios_uintarray *);
usuarios_condRet usuarios_freeUint(usuarios_uintarray *);
usuarios_condRet usuarios_removerAmizade(unsigned int, unsigned int);
int usuarios_sessaoAberta();
int usuarios_max();

#endif


