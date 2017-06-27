// Módulo de busca de transações - Testes.

/**

  @file transaction_search_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de busca de transações
  do aplicativo.

*/

#include "transaction_search.h"

#include "gtest/gtest.h"

char name[75];
transactionList list, list2;
userRestriction restriction;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  EXPECT_EQ(1, true);

}

TEST (CreateRestriction, Normal_Restriction) {

  EXPECT_EQ(CreateRestriction(Friend, 0, 5, &restriction), Success);
  EXPECT_EQ(restriction.proximity, Friend);
  EXPECT_EQ(restriction.minimum_rating, 0);
  EXPECT_EQ(restriction.maximum_rating, 5);

}

TEST (CreateRestriction, Invalid_Restriction) {

  EXPECT_EQ(CreateRestriction(Friend, 0, 5, NULL), Illegal_argument);

}

/*
  Teste da função CleanTransactionList passando-se como argumento uma lista
  vazia.
 */

TEST (CleanTransactionList, New_List) {

  ASSERT_EQ((list2.items == NULL), true);

  EXPECT_EQ(CleanTransactionList(&list2), Success);

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

}

/*
  Teste da função CleanTransactionList passando-se como argumento um ponteiro
  nulo.
 */

TEST (CleanTransactionList, Invalid_List) {

  EXPECT_EQ(CleanTransactionList(NULL), Illegal_argument);

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
