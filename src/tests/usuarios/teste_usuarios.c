#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "usuarios.h"
#include "aleatorio.h"

TEST(Usuarios, CriarUsuario){
	/* Removemos o arquivo de usuários */
	remove(USUARIOS_DB);
	
	/* Esperamos que a função falhe pois o grafo de usuário não foi carregado ainda */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_GRAFONULL);
	
	/* Carregamos o grafo de usuários */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados o novo usuário */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	
	/* Tentamos gravar no arquivo de dados o novo usuário novamente */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
	
	/* Tentamos criar um usuário com senha inválida */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "1234536", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_SENHAS_INVALIDAS);
	
	/* Tentamos criar um usuário com email inválido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jos0e123", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joaoantonio.com", "senha", "123436", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_FALHA_EMAIL_INVALIDO);
	
	/* Tentamos criar um usuário com email repetido */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "jose1423", "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", "joao@antonio.com", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_USUARIOEXISTE);
}

TEST(Usuarios, CriarMuitosUsuarios){
	int i;
	char email[USUARIOS_LIMITE_EMAIL];
	for(i=0;i<100;i++){
		sprintf(email, "%s@%s.com", stringAleatoria(numeroAleatorio(5)+5), stringAleatoria(numeroAleatorio(5)+5));
		EXPECT_EQ(usuarios_cadastro(8, "usuario", stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_USUARIO-5)+5), "nome", "José Antônio", "endereco", "Rua Foo Casa Bar", "email", email, "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	}
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

