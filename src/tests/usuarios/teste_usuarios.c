#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "usuarios.h"
#include "aleatorio.h"

TEST(Usuarios, CriarUsuario){
	/* Removemos o arquivo de usuários */
	remove(USUARIOS_DB);
	remove(USUARIOS_DB_AMIGOS);
	
	/* Esperamos que a função falhe pois o grafo de usuário não foi carregado ainda */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_GRAFONULL);
	
	/* Carregamos o grafo de usuários */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados dois novos usuários */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "amandalinda", "nome", "Amanda", "email", "karol@diego.com", "endereco", "Rua Foo 2 Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", PAYPAL, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados o novo usuário novamente */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
	
	/* Tentamos criar um usuário com senha inválida */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "1234536", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_SENHAS_INVALIDAS);
	
	/* Tentamos criar um usuário com email inválido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joaoantonio.com", "senha", "123436", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_EMAIL_INVALIDO);
	
	/* Tentamos criar um usuário com email repetido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose1423", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
	
	/* Tentamos criar um usuário com \t */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "maria", "nome", "Maria\tAntônia", "endereco", "Rua Foo Casa Bar", "email", "maria@antonia.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_CARACTERESILEGAIS);
}

TEST(Usuarios, CriarMuitosUsuarios){
	int i;
	char email[USUARIOS_LIMITE_EMAIL];
	char *senha;
	for(i=0;i<100;i++){
		senha = stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_SENHA-5)+5);
		sprintf(email, "%s@%s.com", stringAleatoria(numeroAleatorio(5)+5), stringAleatoria(numeroAleatorio(5)+5));
		EXPECT_EQ(usuarios_cadastro(8, "usuario", stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_USUARIO-5)+5), "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", email, "senha", senha, "senha_confirmacao", senha, "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
		free(senha);
	}
}

TEST(Usuarios, FazerLogin){
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_FALHA_SESSAOABERTA);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);
}

TEST(Usuarios, DadosRetorno){
	char *teste_nome;
	usuarios_tipo_usuario teste_tipo;
	usuarios_forma_de_pagamento teste_forma;
	
	/* Esperamos que o nome seja o mesmo do primeiro teste */
	EXPECT_EQ(usuarios_retornaDados((char *)"nome", (void *)&teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "José Antônio"), 1);
	EXPECT_EQ(usuarios_retornaDados((char *)"usuario", (void *)&teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "jose123"), 1);
	EXPECT_EQ(usuarios_retornaDados((char *)"email", (void *)&teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "joao@antonio.com"), 1);
	EXPECT_EQ(usuarios_retornaDados((char *)"endereco", (void *)&teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Rua Foo Casa Bar"), 1);
	EXPECT_EQ(usuarios_retornaDados((char *)"formaPagamento", (void *)&teste_forma), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_forma, BOLETO);
	EXPECT_EQ(usuarios_retornaDados((char *)"tipo", (void *)&teste_tipo), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_tipo, CONSUMIDOR);
	
	/* Esperamos que a conta não tenha sido criada */
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"maria", (char *)"123456"), USUARIOS_FALHA_DADOSINCORRETOS);
	
}

TEST(Usuarios, lerArquivo){
	char *teste_nome;
	
	/* Fechamos tudo */
	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
	
	/* Reabrimos o arquivo */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
	/* Esperamos que a conta não tenha sido criada sequer no arquivo */
	EXPECT_EQ(usuarios_login((char *)"maria", (char *)"123456"), USUARIOS_FALHA_DADOSINCORRETOS);
	
}

TEST(Amizade, criarAmizade){
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_criarAmizade(2), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(2), AGUARDANDOCONFIRMACAO);
	EXPECT_EQ(usuarios_criarAmizade(2), USUARIOS_AMIZADEJASOLICITADA);
	EXPECT_EQ(usuarios_verificarAmizade(2), AGUARDANDOCONFIRMACAO);
	
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"amandalinda", (char *)"123456"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), ACONFIRMAR);
	EXPECT_EQ(usuarios_criarAmizade(1), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), AMIGOS);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

