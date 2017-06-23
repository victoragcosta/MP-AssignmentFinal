#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "usuarios.h"
#include "avaliacao.h"

TEST(Avaliacao, Avaliar) { 
	/* Carregamos o grafo de usuários */
	EXPECT_EQ(usuarios_carregarArquivo(), USUARIOS_SUCESSO);
	
  /* Fazemos login como jose123 */
  EXPECT_EQ(usuarios_login((char *)"jose123", (char *)"987654"), USUARIOS_SUCESSO);
  
  /* Avaliamos amandalinda */
  EXPECT_EQ(avaliacao_fazerAvaliacao(2, 5, (char *)"Muito bom!"), AVALIACAO_SUCESSO);
  EXPECT_EQ(avaliacao_fazerAvaliacao(2, 1, (char *)"Uma bosta!"), AVALIACAO_SUCESSO);

	EXPECT_EQ(usuarios_limpar(), USUARIOS_SUCESSO);
  
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

