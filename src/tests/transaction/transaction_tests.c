// Módulo de transações - Testes.

/**

  @file transaction_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de transações do
  aplicativo

*/

#include "transaction.h"

#include "gtest/gtest.h"

char name[75];
product new_product;
transaction new_transaction, new_transaction2;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &new_product);

  EXPECT_EQ(1, true);

}

TEST (CreateTransaction, Normal_Transaction) {

  EXPECT_EQ(CreateTransaction(171, &new_product, &new_transaction), Success);
  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Open);

}

TEST (CreateTransaction, Invalid_Transaction) {

  EXPECT_EQ(CreateTransaction(171, &new_product, NULL), Illegal_argument);
  EXPECT_EQ(CreateTransaction(171, NULL, &new_transaction), Illegal_argument);
  EXPECT_EQ(CreateTransaction(171, NULL, NULL), Illegal_argument);

}

TEST (UpdateTransaction, Normal_Transaction) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Open);

  EXPECT_EQ(UpdateTransaction(501, &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

}

TEST (UpdateTransaction, Same_User) {

  EXPECT_EQ(CreateTransaction(171, &new_product, &new_transaction2), Success);
  EXPECT_EQ(UpdateTransaction(171, &new_transaction2), Illegal_argument);

}

TEST (UpdateTransaction, Invalid_Status) {

  new_transaction2.status = Closed;
  EXPECT_EQ(UpdateTransaction(501, &new_transaction2), Illegal_argument);

}

TEST (UpdateTransaction, Invalid_Transaction) {

  EXPECT_EQ(UpdateTransaction(171, NULL), Illegal_argument);

}

TEST (CancelTransaction, Open_Transaction) {

  EXPECT_EQ(CreateTransaction(171, &new_product, &new_transaction2), Success);
  EXPECT_EQ(new_transaction2.user1, 171);
  EXPECT_EQ(new_transaction2.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction2.item), &new_product), 0);
  EXPECT_EQ(new_transaction2.status, Open);

  EXPECT_EQ(CancelTransaction(&new_transaction2), Success);

  EXPECT_EQ(new_transaction2.user1, 171);
  EXPECT_EQ(new_transaction2.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction2.item), &new_product), 0);
  EXPECT_EQ(new_transaction2.status, Canceled);

}

TEST (CancelTransaction, Transaction_In_Progress) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

  EXPECT_EQ(CancelTransaction(&new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

}

TEST (CancelTransaction, Closed_Transaction) {

  new_transaction2.status = Closed;
  EXPECT_EQ(new_transaction2.user1, 171);
  EXPECT_EQ(new_transaction2.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction2.item), &new_product), 0);
  EXPECT_EQ(new_transaction2.status, Closed);

  EXPECT_EQ(CancelTransaction(&new_transaction2), Illegal_argument);

  EXPECT_EQ(new_transaction2.user1, 171);
  EXPECT_EQ(new_transaction2.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction2.item), &new_product), 0);
  EXPECT_EQ(new_transaction2.status, Closed);

}

TEST (CancelTransaction, Canceled_Transaction) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  EXPECT_EQ(CancelTransaction(&new_transaction), Illegal_argument);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

}

TEST (CancelTransaction, Invalid_Transaction) {

  EXPECT_EQ(CancelTransaction(NULL), Illegal_argument);

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
