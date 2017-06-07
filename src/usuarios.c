#include <stdio.h>
#include <stdlib.h>
#include "../include/usuarios.h"
#include "../include/grafo.h"

/*!
 * @brief Grafo de usuários
*/
static grafo *usuarios_grafo = NULL;

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
		fopen(USUARIOS_DB, "w");
		fclose(db_usuarios);
		return SUCESSO;
	}
	
	/* Verificador do fscanf */
	int fscanf_retorno;

	/* Dados do usuário corrente */
	tpUsuario *corrente;
	while(!feof(db_usuarios)){
		corrente = (tpUsuario *)malloc(sizeof(tpUsuario));
		/* Lemos do arquivo */
		fscanf_retorno = fscanf(db_usuarios, "%d\t%*c\t%*c\t%*c\t%*c\t%d\t%d\n", 
			&(corrente->identificador),  \
			USUARIOS_LIMITE_NOME, corrente->nome, \
			USUARIOS_LIMITE_EMAIL, corrente->email, \
			USUARIOS_LIMITE_SENHA, corrente->senha, \
			USUARIOS_LIMITE_ENDERECO, corrente->endereco, \
			(int *)&(corrente->formaPagamento), \
			(int *)&(corrente->tipo)
		);
		
		/* Verificamos se o retorno foi adequado */
		if(fscanf_retorno != 7) {
			fclose(db_usuarios);
			return FALHA_LERDB;
		}
		
		/* Adicionamos ao grafo */
		if(adiciona_vertice(usuarios_grafo, corrente->identificador) != SUCESSO) {
			fclose(db_usuarios);
			return FALHA_ADICIONAR_GRAFO;
		}
		
		/* Definimos o valores correntes no vértice */
		if(muda_valor_vertice(usuarios_grafo, corrente->identificador, (void *)corrente) != SUCESSO) {
			fclose(db_usuarios);
			return FALHA_INSERIR_DADOS;
		}
		
	}
	
	fclose(db_usuarios);
	return SUCESSO;
}

/*!
 * @brief Função de cadastro de usuários
 * 
 * Recebe como parâmetros nome, endereço, email, senha repetida duas vezes, forma de 
 * pagamento, tipo de usuário
 * 
 * @code 
 * usuarios_cadastro("José Antônio", "Rua Foo Casa Bar", "joao@antonio.com", "123456", "123456", BOLETO, CONSUMIDOR);
 * @endcode
*/

usuarios_condRet usuarios_cadastro(char *nome, char *endereco, char *email, char *senha, char *senha_confirmacao, usuarios_forma_de_pagamento formaPagamento, usuarios_tipo_usuario tipo){
	FILE *db_usuarios;
	
	/* Verificamos se o email é válido */
	if(strstr(email, "@") == NULL || strstr(email, ".") == NULL) return FALHA_EMAIL_INVALIDO;
	
	/* Verificamos se as senhas coincidem */
	if(!strcmp(senha, senha_confirmacao)) return FALHA_SENHAS_INVALIDAS;
	
	/* Devemos percorrer o grafo usuarios_grafo e salvar no arquivo */
	db_usuarios = fopen(USUARIOS_DB, "a+");
	
	/* CONTINUAR DAQUI */
	
	return SUCESSO;
}

