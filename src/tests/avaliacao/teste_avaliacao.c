#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>
#include "usuarios.h"
#include "aleatorio.h"
#include "avaliacao.h"

TEST(Avaliacao, AvaliarLogin) { 
	/* Carregamos o grafo de usuários */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
	/* Carregamos as avaliações */
	remove(AVALIACAO_DB);
	avaliacao_pegarContador();
	
  /* Fazemos login como jose123 */
  EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
  
  /* José avalia o usuário 4 com nota 5 */
  EXPECT_EQ(avaliacao_avaliar(0, 4, 5, (char *)"Ótimo"), AVALIACAO_SUCESSO);
  
  EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);

}

TEST(Avaliacao, MostrarSessao){
  avaliacao *a = avaliacao_iniciar();
  EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
  EXPECT_EQ(avaliacao_obterAvaliacao(0, 1, AVALIADOR, a), AVALIACAO_SUCESSO);
  EXPECT_EQ(a->avaliador, 1);
  EXPECT_EQ(a->avaliado, 4);
  EXPECT_EQ(a->nota, 5);
  EXPECT_EQ(!strcmp(a->comentario, "Ótimo"), 1);
  avaliacao_limpar(&a);
  EXPECT_EQ(usuarios_logout(), USUARIOS_SUCESSO);
}

TEST(Avaliacao, Avaliar){
  unsigned int i,j;
  for(i=1;i<50;i++){
    for(j=50;j<100;j++){
      EXPECT_EQ(avaliacao_avaliar(i, j, numeroAleatorio(5), (char *)"Ótimo"), AVALIACAO_SUCESSO);
    }
  }
	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

