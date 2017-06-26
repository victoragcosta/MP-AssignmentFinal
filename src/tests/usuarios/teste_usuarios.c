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

	/* Gravamos usuários com overflow nos campos */
	EXPECT_EQ(usuarios_cadastro(8, "usuario", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "nome", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "email", "aaaaaa@a.comaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa@aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.com", "endereco", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "senha", "123", "senha_confirmacao", "123", "formaPagamento", PAYPAL, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
	
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
  char *tmp[3];
	char *senha;
	for(i=0;i<100;i++){
		senha = stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_SENHA-5)+5);
    tmp[0] = stringAleatoria(numeroAleatorio(5)+5);
    tmp[1] = stringAleatoria(numeroAleatorio(5)+5);
    tmp[2] = stringAleatoria(numeroAleatorio(USUARIOS_LIMITE_USUARIO-5)+5);
		sprintf(email, "%s@%s.com", tmp[0], tmp[1]);
		EXPECT_EQ(usuarios_cadastro(8, "usuario", tmp[2], "nome", "Jose Antonio", "endereco", "Rua Foo Casa Bar", "email", email, "senha", senha, "senha_confirmacao", senha, "formaPagamento", BOLETO, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
		free(senha);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
	}
	EXPECT_EQ(usuarios_max(), 100+3);
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
	
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
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
	unsigned int teste_n_reclamacoes;
  unsigned int teste_n_avaliacao;
	usuarios_estado_de_usuario teste_estado;
  usuarios_forma_de_pagamento teste_forma;
  double teste_avaliacao;
	
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"123456"), USUARIOS_SUCESSO);
	
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
	
	EXPECT_EQ(usuarios_atualizarDados(0, "avaliacao", 2.854), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "avaliacao", (void *)&teste_avaliacao), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_avaliacao, 2.854);
	
	EXPECT_EQ(usuarios_atualizarDados(0, "n_avaliacao", 80), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(0, "n_avaliacao", (void *)&teste_n_avaliacao), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_n_avaliacao, 80);
	
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
	EXPECT_EQ(usuarios_atualizarDados(2, "estado", INATIVO_EMAIL), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(2, "estado", (void *)&teste_estado), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_estado, INATIVO_EMAIL);
	
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
	EXPECT_EQ(usuarios_login((char *)"amandalinda", (char *)"987654"), USUARIOS_FALHA_INATIVO);
	
	EXPECT_EQ(usuarios_atualizarDados(2, "estado", ATIVO), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_retornaDados(2, "estado", (void *)&teste_estado), USUARIOS_SUCESSO);
	EXPECT_EQ(teste_estado, ATIVO);
	
	EXPECT_EQ(usuarios_login((char *)"amandalinda", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
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
	
	
	EXPECT_EQ(usuarios_criarAmizade(105), USUARIOS_FALHAUSUARIONAOEXISTE);
	
	usuarios_listarAmigos(1, &a);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	
	EXPECT_EQ(usuarios_login((char *)"amandalinda", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), ACONFIRMAR);
	EXPECT_EQ(usuarios_criarAmizade(1), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(1), AMIGOS);
	usuarios_listarAmigos(1, &a);
	usuarios_freeUint(&a);
	
	
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);

	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);	
	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(2), AMIGOS);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
}


TEST(Amizade, amigodeamigo){
  unsigned int i=0,j,k,max=usuarios_max()+1, id;
  char usuario[USUARIOS_LIMITE_USUARIO];
  char email[USUARIOS_LIMITE_EMAIL];
  usuarios_uintarray amigospendentes, amigosdeamigos;

  /* Criamos 100 usuários */
  for(;i<100;i++){
    sprintf(usuario, "u%u", i);
    sprintf(email, "e%u@t.com", i);
    EXPECT_EQ(usuarios_cadastro(8, "usuario", usuario, "nome", "u1", "email", email, "endereco", "", "senha", "0", "senha_confirmacao", "0", "formaPagamento", PAYPAL, "tipo", CONSUMIDOR), USUARIOS_SUCESSO);
  }
  for(k=0;k<3;k++){ /* Grupos de 25 usuários */
  for(i=0;i<25;i++){
    sprintf(usuario,"u%u",i+25*k);
    EXPECT_EQ(usuarios_login(usuario,(char *)"0"), USUARIOS_SUCESSO);
    EXPECT_EQ(usuarios_retornaDados(0,"identificador", (void *)&id), USUARIOS_SUCESSO);
    for(j=0;j<25;j++){
      EXPECT_EQ(usuarios_criarAmizade(max+j+25*(k+1)), USUARIOS_SUCESSO);
      EXPECT_EQ(usuarios_verificarAmizade(max+j+25*(k+1)), AGUARDANDOCONFIRMACAO);
    }
    EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
  }
  }
  /* Aceitamos as solicitações de amizade */
  for(i=25;i<100;i++) {
    sprintf(usuario,"u%u",i);
    EXPECT_EQ(usuarios_login(usuario,(char *)"0"), USUARIOS_SUCESSO);
    EXPECT_EQ(usuarios_listarAmigosPendentes(i+max, &amigospendentes), USUARIOS_SUCESSO);
    EXPECT_EQ(amigospendentes.length, 25);
    for(j=0;j<amigospendentes.length;j++){
      //printf("%u com %u\n", i, amigospendentes.array[j]-max);
      EXPECT_EQ(usuarios_criarAmizade(amigospendentes.array[j]), USUARIOS_SUCESSO);
    }
    EXPECT_EQ(usuarios_freeUint(&amigospendentes), USUARIOS_SUCESSO);
    EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
  }
  /* Verificamos são amigos */
  for(k=0;k<3;k++){
    for(i=0;i<25;i++){
      sprintf(usuario,"u%u",i+25*k);
      EXPECT_EQ(usuarios_login(usuario,(char *)"0"), USUARIOS_SUCESSO);
      for(j=1;j<25;j++){
        EXPECT_EQ(usuarios_verificarAmizade(max+j+25*(k+1)), AMIGOS);
      }
      EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
    }
  }
  /* Verificamos se o grupo 50~75 são amigos de amigos do grupo 0~25 */
  
  for(i=0;i<25;i++){
    usuarios_listarAmigosdeAmigos(max+i, &amigosdeamigos);
    
    for(j=0;j<amigosdeamigos.length/2;j++){
      EXPECT_EQ(amigosdeamigos.array[j], j+max+2*25);
    }
    EXPECT_EQ(usuarios_freeUint(&amigosdeamigos), USUARIOS_SUCESSO);
  }
}

TEST(Amizade, removerAmizade){

	EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_verificarAmizade(2), AMIGOS);
	EXPECT_EQ(usuarios_removerAmizade(0, 2), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

