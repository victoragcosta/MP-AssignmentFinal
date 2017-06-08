#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aleatorio.h"
#include "usuarios.h"
#include "grafo.h"

/*!
 * @brief Grafo de usuários
*/
static grafo *usuarios_grafo = NULL;
static unsigned int usuarios_contador = 0;
static int usuarios_identificador_max = 0;

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
usuarios_condRet usuarios_verificaRepeticao(const char *argumento, char *dado){
	unsigned int i = 0; /* Contador dos nós */
	tpUsuario *informacao;
	/* Buscamos por um usuario igual */
	if(!strcmp(argumento, "usuario")) {
		for(i=0;i<usuarios_contador;i++){
			informacao = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
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
			/* São iguais */ 
			//printf("'%s' == '%s'\n", informacao->email, dado);
			if(!strcmp(informacao->email, dado)) return USUARIOS_DADOS_REPETICAO;
		}
		return USUARIOS_DADOS_OK;
	}
	
	return USUARIOS_ARGUMENTOINVALIDO;
}

/*!
 * @brief Função leitora de string em um arquivo de dados
*/
void usuarios_lerString(FILE *arquivo, char *dstStr, unsigned int limite){
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
 * @ brief Função carregadora do arquivo 
 * de usuários e suas relações
*/

usuarios_condRet usuarios_carregarArquivo(){
	FILE *db_usuarios = fopen(USUARIOS_DB, "r");
		
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

	/* Dados do usuário corrente */
	tpUsuario *corrente;
	while(!feof(db_usuarios)){
		corrente = (tpUsuario *)malloc(sizeof(tpUsuario));
		
		/* Lemos do arquivo */
		fscanf(db_usuarios, "%d\t", &(corrente->identificador));
		usuarios_lerString(db_usuarios, corrente->usuario, USUARIOS_LIMITE_USUARIO);
		usuarios_lerString(db_usuarios, corrente->nome, USUARIOS_LIMITE_NOME);
		usuarios_lerString(db_usuarios, corrente->email, USUARIOS_LIMITE_EMAIL);
		usuarios_lerString(db_usuarios, corrente->senha, USUARIOS_LIMITE_SENHA);
		usuarios_lerString(db_usuarios, corrente->endereco, USUARIOS_LIMITE_ENDERECO);
				
		fscanf(db_usuarios, "%d\t%d", 
			(int *)&(corrente->formaPagamento), \
			(int *)&(corrente->tipo)
		);
		
		/*printf("'%d'\n'%s'\n'%s'\n'%s'\n'%s'\n'%s'\n'%d'\n'%d'\n-------------\n", 
			corrente->identificador,  \
			corrente->usuario, \
			corrente->nome, \
			corrente->email, \
			corrente->senha, \
			corrente->endereco, \
			(int)corrente->formaPagamento, \
			(int)corrente->tipo
		);*/
		
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
	
	usuarios_contador = i; /* Número de usuários carregados */
	fclose(db_usuarios);
	return USUARIOS_SUCESSO;
}

/*!
 * @brief Função de cadastro de usuários
 * 
 * Recebe como parâmetros nome, endereço, email, senha repetida duas vezes, forma de 
 * pagamento, tipo de usuário
 * 
 * @code 
 * usuarios_cadastro("jose123", "José Antônio", "Rua Foo Casa Bar", "joao@antonio.com", "123456", "123456", BOLETO, CONSUMIDOR);
 * @endcode
 *
 * Assertiva de entrada: o arquivo USUARIOS_DB já existe,
 * isto é a função usuarios_carregarArquivo já foi executada.
*/

usuarios_condRet usuarios_cadastro(char *usuario, char *nome, char *endereco, char *email, char *senha, char *senha_confirmacao, usuarios_forma_de_pagamento formaPagamento, usuarios_tipo_usuario tipo){
	FILE *db_usuarios;
	tpUsuario *novo;
	
	/* Verificamos se o grafo de usuários foi iniciado */
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	/* Verificamos se o email é válido */
	if(strstr(email, "@") == NULL || strstr(email, ".") == NULL) return USUARIOS_FALHA_EMAIL_INVALIDO;
	
	/* Verificamos se as senhas coincidem */
	if(strcmp(senha, senha_confirmacao)) return USUARIOS_FALHA_SENHAS_INVALIDAS;
	
	/* Verificamos se já há um usuário desse */
	if(usuarios_verificaRepeticao("usuario", usuario) != USUARIOS_DADOS_OK)
		return USUARIOS_USUARIOEXISTE;
		
	/* Verificamos se já há um email desse */
	if(usuarios_verificaRepeticao("email", email) != USUARIOS_DADOS_OK)
		return USUARIOS_USUARIOEXISTE;
	
	/* Devemos percorrer o grafo usuarios_grafo e salvar no arquivo */
	db_usuarios = fopen(USUARIOS_DB, "a+");
	
	/* Gravamos no arquivo */
	int fprintf_retorno = fprintf(db_usuarios, "%d\t%*s\t%*s\t%*s\t%*s\t%*s\t%d\t%d\n", 
		++usuarios_identificador_max,  \
		-USUARIOS_LIMITE_USUARIO, usuario, \
		-USUARIOS_LIMITE_NOME, nome, \
		-USUARIOS_LIMITE_EMAIL, email, \
		-USUARIOS_LIMITE_SENHA, senha, \
		-USUARIOS_LIMITE_ENDERECO, endereco, \
		(int)formaPagamento, \
		(int)tipo
	);
	
	/* Definimos os valores */
	novo = (tpUsuario *)malloc(sizeof(tpUsuario));
	
	novo->identificador = usuarios_identificador_max;
	strncpy(novo->usuario, usuario, USUARIOS_LIMITE_USUARIO);
	strncpy(novo->nome, nome, USUARIOS_LIMITE_NOME);
	strncpy(novo->email, email, USUARIOS_LIMITE_EMAIL);
	strncpy(novo->senha, senha, USUARIOS_LIMITE_SENHA);
	strncpy(novo->endereco, endereco, USUARIOS_LIMITE_ENDERECO);
	novo->formaPagamento = formaPagamento;
	novo->tipo = tipo;
	
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

