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
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_GRAFONULL);
	
	/* Carregamos o grafo de usuários */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados dois novos usuários */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "Jose Antonio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "amandalinda", "nome", "Amanda", "email", "karol@diego.com", "endereco", "Rua Foo 2 Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", PAYPAL, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados o novo usuário novamente */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
	
	/* Tentamos criar um usuário com senha inválida */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "1234536", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_SENHAS_INVALIDAS);
	
	/* Tentamos criar um usuário com email inválido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", "joaoantonio.com", "senha", "123436", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_EMAIL_INVALIDO);
	
	/* Tentamos criar um usuário com email repetido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose1423", "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
	
	/* Tentamos criar um usuário com \t */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "maria", "nome", "Maria\tAntonia", "endereco", "Rua Foo Casa Bar", "email", "maria@antonia.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_CARACTERESILEGAIS);
	
	/* Esperamos que a conta não tenha sido criada */
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"maria", (char *)"123456"), USUARIOS_FALHA_DADOSINCORRETOS);
}

TEST(Usuarios, CriarMuitosUsuarios){
	int i;
	char email[USUARIOS_LIMITE_EMAIL];
	char *senha;
	for(i=0;i<100;i++){
		senha = stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_SENHA-5)+5);
		sprintf(email, "%s@%s.com", stringAleatoria(numeroAleatorio(5)+5), stringAleatoria(numeroAleatorio(5)+5));
		EXPECT_EQ(usuarios_cadastro(8, "usuario", stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_USUARIO-5)+5), "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", email, "senha", senha, "senha_confirmacao", senha, "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
		free(senha);
	}
}

TEST(Usuarios, FazerLogin){
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_FALHA_SESSAOABERTA);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
}

TEST(Usuarios, DadosRetornoSessao){
	char teste_nome[40];
	usuarios_tipo_usuario teste_tipo;
	usuarios_forma_de_pagamento teste_forma;
	usuarios_estado_de_usuario teste_estado;
	double teste_avaliacao;
	unsigned int teste_n_avaliacao;
	
	/* Esperamos que o nome seja o mesmo do primeiro teste (sessão) */
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);

	
	EXPECT_EQ(usuarios_retornaDados(0, "nome", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Jose Antonio"), 1);
	EXPECT_EQ(usuarios_retornaDados(0, "usuario", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "jose123"), 1);
	EXPECT_EQ(usuarios_retornaDados(0, "email", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "joao@antonio.com"), 1);
	EXPECT_EQ(usuarios_retornaDados(0, "endereco", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Rua Foo Casa Bar"), 1);
	EXPECT_EQ(usuarios_retornaDados(0, "formaPagamento", (void *)&teste_forma), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_forma, BOLETO);
	EXPECT_EQ(usuarios_retornaDados(0, "tipo", (void *)&teste_tipo), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "estado", (void *)&teste_estado), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_estado, ATIVO);
	EXPECT_EQ(usuarios_retornaDados(0, "avaliacao", (void *)&teste_avaliacao), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_avaliacao, 0);
	EXPECT_EQ(usuarios_retornaDados(0, "n_avaliacao", (void *)&teste_n_avaliacao), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_n_avaliacao, 0);
	
}

TEST(Usuarios, DadosRetorno){
	char teste_nome[40];
	usuarios_tipo_usuario teste_tipo;


	EXPECT_EQ(usuarios_retornaDados(2, "nome", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Amanda"), 1);

	EXPECT_EQ(usuarios_retornaDados(2, "tipo", (void *)&teste_tipo), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_tipo, CONSUMIDOR);
}

TEST(Usuarios, AlterarDadosSessao){
	char teste_nome[40];
	int teste_n_reclamacoes;
	usuarios_estado_de_usuario teste_estado;
	EXPECT_EQ(usuarios_atualizarDados(0, "nome", "Jose Felipe"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "nome", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Jose Felipe"), 1);
	EXPECT_EQ(usuarios_atualizarDados(0, "nome", "Jose Augusto"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "nome", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Jose Augusto"), 1);
	EXPECT_EQ(usuarios_atualizarDados(0, "senha", "987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "senha", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "987654"), 1);
	EXPECT_EQ(usuarios_atualizarDados(0, "estado", INATIVO_EMAIL), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "estado", (void *)&teste_estado), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_estado, INATIVO_EMAIL);
	EXPECT_EQ(usuarios_atualizarDados(0, "estado", ATIVO), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "estado", (void *)&teste_estado), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_estado, ATIVO);
	EXPECT_EQ(usuarios_atualizarDados(0, "n_reclamacoes", 5), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "n_reclamacoes", (void *)&teste_n_reclamacoes), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_n_reclamacoes, 5);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
}

TEST(Usuarios, AlterarDados){
	char teste_nome[40];
	usuarios_estado_de_usuario teste_estado;
  usuarios_tipo_usuario teste_tipo;
	EXPECT_EQ(usuarios_atualizarDados(2, "nome", "Amanda Nunes"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(2, "nome", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "Amanda Nunes"), 1);
	EXPECT_EQ(usuarios_atualizarDados(2, "senha", "987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(2, "senha", (void *)teste_nome), USUARIOS_SUCESSO);
	EXPECT_EQ(!strcmp(teste_nome, "987654"), 1);
	EXPECT_EQ(usuarios_atualizarDados(2, "tipo", OFERTANTE), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(2, "tipo", (void *)&teste_tipo), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_tipo, OFERTANTE);
	
}

TEST(Usuarios, lerArquivo){
	char teste_nome[40];
	
	/* Fechamos tudo */
	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
	
	/* Reabrimos o arquivo */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);	
}

TEST(Amizade, criarAmizade){
  unsigned int i;
  usuarios_uintarray a;
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_criarAmizade(2), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(2), AGUARDANDOCONFIRMACAO);
	EXPECT_EQ(usuarios_criarAmizade(2), USUARIOS_AMIZADEJASOLICITADA);
	EXPECT_EQ(usuarios_verificarAmizade(2), AGUARDANDOCONFIRMACAO);
	
	usuarios_listarAmigos(1, &a);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
	EXPECT_EQ(usuarios_login((char *)"amandalinda", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), ACONFIRMAR);
	EXPECT_EQ(usuarios_criarAmizade(1), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), AMIGOS);
	usuarios_listarAmigos(1, &a);
	
	
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

