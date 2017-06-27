// Módulo de transações - Testes.

/**

  @file transaction_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de transações do
  aplicativo

*/

#include "transaction.h"

#include "gtest/gtest.h"

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  EXPECT_EQ(1, true);

}

/*
  Finalização (desalocação de memória alocada dinamicamente) das variáveis
  utilizadas nos testes.
 */

TEST (Termination, Variables) {

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
