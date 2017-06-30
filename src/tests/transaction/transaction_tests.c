// Módulo de transações - Testes.

/**

  @file transaction_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de transações do
  aplicativo.

*/

#include "transaction.h"

#include "gtest/gtest.h"

char name[75];
char review1[AVALIACAO_LIMITE_COMENTARIO], review2[AVALIACAO_LIMITE_COMENTARIO];
product new_product, different_product, invalid;
transaction new_transaction, new_transaction2, copy, other;
avaliacao *test_review;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &new_product);

  strcpy(name, "Feijão");
  CreateProduct(name, Sale, 7, 92, &different_product);

  strcpy(invalid.name, "Sick dog");
  invalid.price = -5;
  invalid.popularity = 0;
  invalid.type = Sale;

  strcpy(review1, "Ofertante mediano.");
  strcpy(review2, "Sem reclamações.");

  usuarios_carregarArquivo();
  avaliacao_pegarContador();

  EXPECT_EQ(1, true);

}

TEST (CreateTransaction, Valid_Transaction_01) {

  EXPECT_EQ(CreateTransaction(171, 171, &new_product, Open,
            &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Open);

}

TEST (CreateTransaction, Valid_Transaction_02) {

  EXPECT_EQ(CreateTransaction(171, 501, &new_product, InProgress,
            &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

}

TEST (CreateTransaction, Valid_Transaction_03) {

  EXPECT_EQ(CreateTransaction(134, 501, &new_product, Closed,
            &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 134);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Closed);

}

TEST (CreateTransaction, Valid_Transaction_04) {

  EXPECT_EQ(CreateTransaction(134, 501, &new_product, Canceled,
            &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 134);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

}

TEST (CreateTransaction, Valid_Transaction_05) {

  EXPECT_EQ(CreateTransaction(134, 134, &new_product, Canceled,
            &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 134);
  EXPECT_EQ(new_transaction.user2, 134);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

}

TEST (CreateTransaction, Invalid_Open_Transaction) {

  EXPECT_EQ(CreateTransaction(134, 137, &new_product, Open,
            &new_transaction), Illegal_argument);

}

TEST (CreateTransaction, Same_User) {

  EXPECT_EQ(CreateTransaction(134, 134, &new_product, InProgress,
            &new_transaction), Illegal_argument);
  EXPECT_EQ(CreateTransaction(134, 134, &new_product, Closed,
            &new_transaction), Illegal_argument);

}

TEST (CreateTransaction, Invalid_User) {

  EXPECT_EQ(CreateTransaction(0, 0, &new_product, Open,
            &new_transaction), Illegal_argument);
  EXPECT_EQ(CreateTransaction(0, 134, &new_product, InProgress,
            &new_transaction), Illegal_argument);
  EXPECT_EQ(CreateTransaction(0, 134, &new_product, Canceled,
            &new_transaction), Illegal_argument);
  EXPECT_EQ(CreateTransaction(0, 134, &new_product, Closed,
            &new_transaction), Illegal_argument);

}

TEST (CreateTransaction, Invalid_Product) {

  EXPECT_EQ(CreateTransaction(134, 134, &invalid, Open,
            &new_transaction), Illegal_argument);

}

TEST (CreateTransaction, Invalid_Status) {

  EXPECT_EQ(CreateTransaction(134, 139, &new_product, Error,
            &new_transaction), Illegal_argument);

}

TEST (CreateTransaction, Invalid_Adresses) {

  EXPECT_EQ(CreateTransaction(134, 134, NULL, Open, &new_transaction),
            Illegal_argument);
  EXPECT_EQ(CreateTransaction(134, 134, &new_product, Open, NULL),
            Illegal_argument);
  EXPECT_EQ(CreateTransaction(134, 134, NULL, Open, NULL), Illegal_argument);

}

TEST (StartTransaction, Normal_Transaction) {

  EXPECT_EQ(StartTransaction(171, &new_product, &new_transaction), Success);
  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Open);

}

TEST (StartTransaction, Invalid_Product) {

  EXPECT_EQ(StartTransaction(171, &invalid, &new_transaction),
            Illegal_argument);

}

TEST (StartTransaction, Invalid_Transaction) {

  EXPECT_EQ(StartTransaction(171, &new_product, NULL), Illegal_argument);
  EXPECT_EQ(StartTransaction(171, NULL, &new_transaction), Illegal_argument);
  EXPECT_EQ(StartTransaction(171, NULL, NULL), Illegal_argument);

}

TEST (UpdateTransaction, Normal_Transaction) {

  StartTransaction(171, &new_product, &new_transaction);

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

  EXPECT_EQ(StartTransaction(171, &new_product, &new_transaction2), Success);
  EXPECT_EQ(UpdateTransaction(171, &new_transaction2), Illegal_argument);

}

TEST (UpdateTransaction, Invalid_User) {

  EXPECT_EQ(StartTransaction(171, &new_product, &new_transaction2), Success);
  EXPECT_EQ(UpdateTransaction(0, &new_transaction2), Illegal_argument);

}

TEST (UpdateTransaction, Invalid_Status) {

  new_transaction2.status = Closed;
  EXPECT_EQ(UpdateTransaction(501, &new_transaction2), Illegal_argument);

  new_transaction2.status = Canceled;
  EXPECT_EQ(UpdateTransaction(501, &new_transaction2), Illegal_argument);

  new_transaction2.status = Error;
  EXPECT_EQ(UpdateTransaction(501, &new_transaction2), Illegal_argument);

}

TEST (UpdateTransaction, Invalid_Transaction) {

  EXPECT_EQ(UpdateTransaction(171, NULL), Illegal_argument);

}

TEST (CancelTransaction, Open_Transaction) {

  EXPECT_EQ(StartTransaction(171, &new_product, &new_transaction2), Success);
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

TEST (CancelTransaction, Error_Transaction) {

  new_transaction.status = Error;

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Error);

  EXPECT_EQ(CancelTransaction(&new_transaction), Illegal_argument);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Error);

}

TEST (CancelTransaction, Invalid_Transaction) {

  EXPECT_EQ(CancelTransaction(NULL), Illegal_argument);

}

TEST (CopyTransaction, Normal_Copy) {

  new_transaction.status = Canceled;

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  EXPECT_EQ(CopyTransaction(&copy, &new_transaction), Success);

  EXPECT_EQ(copy.user1, 171);
  EXPECT_EQ(copy.user2, 501);
  EXPECT_EQ(CompareProducts(&(copy.item), &new_product), 0);
  EXPECT_EQ(copy.status, Canceled);

}

TEST (CopyTransaction, Invalid_Copy) {

  EXPECT_EQ(CopyTransaction(&new_transaction, NULL), Illegal_argument);
  EXPECT_EQ(CopyTransaction(NULL, &new_transaction), Illegal_argument);
  EXPECT_EQ(CopyTransaction(NULL, NULL), Illegal_argument);

}

TEST (CompareTransactions, Equal) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  EXPECT_EQ(CopyTransaction(&copy, &new_transaction), Success);

  EXPECT_EQ(copy.user1, 171);
  EXPECT_EQ(copy.user2, 501);
  EXPECT_EQ(CompareProducts(&(copy.item), &new_product), 0);
  EXPECT_EQ(copy.status, Canceled);

  EXPECT_EQ(CompareTransactions(&new_transaction, &copy), 0);
  EXPECT_EQ(CompareTransactions(&copy, &new_transaction), 0);

}

/*
  Teste da função CompareTransactions passando um mesmo endereço duas vezes como
  argumento.
 */

TEST (CompareTransactions, Same_Argument) {

  EXPECT_EQ(CompareTransactions(&new_transaction, &new_transaction), 0);

}

TEST (CompareTransactions, Different_User1) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  CopyTransaction(&other, &new_transaction);

  other.user1 = 170;

  EXPECT_EQ(other.user1, 170);
  EXPECT_EQ(other.user2, 501);
  EXPECT_EQ(CompareProducts(&(other.item), &new_product), 0);
  EXPECT_EQ(other.status, Canceled);

  EXPECT_EQ(CompareTransactions(&new_transaction, &other), 1);
  EXPECT_EQ(CompareTransactions(&other, &new_transaction), 1);

}

TEST (CompareTransactions, Different_User2) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  CopyTransaction(&other, &new_transaction);

  other.user2 = 532;

  EXPECT_EQ(other.user1, 171);
  EXPECT_EQ(other.user2, 532);
  EXPECT_EQ(CompareProducts(&(other.item), &new_product), 0);
  EXPECT_EQ(other.status, Canceled);

  EXPECT_EQ(CompareTransactions(&new_transaction, &other), 1);
  EXPECT_EQ(CompareTransactions(&other, &new_transaction), 1);

}

TEST (CompareTransactions, Different_Status) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  CopyTransaction(&other, &new_transaction);

  other.status = Open;

  EXPECT_EQ(other.user1, 171);
  EXPECT_EQ(other.user2, 501);
  EXPECT_EQ(CompareProducts(&(other.item), &new_product), 0);
  EXPECT_EQ(other.status, Open);

  EXPECT_EQ(CompareTransactions(&new_transaction, &other), 1);
  EXPECT_EQ(CompareTransactions(&other, &new_transaction), 1);

}

TEST (CompareTransactions, Different_Products) {

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 501);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  CopyTransaction(&other, &new_transaction);

  CopyProduct(&(other.item), &different_product);

  EXPECT_EQ(other.user1, 171);
  EXPECT_EQ(other.user2, 501);
  EXPECT_EQ(CompareProducts(&(other.item), &different_product), 0);
  EXPECT_EQ(other.status, Canceled);

  EXPECT_EQ(CompareTransactions(&new_transaction, &other), 1);
  EXPECT_EQ(CompareTransactions(&other, &new_transaction), 1);

}

/* Teste da função CompareTransactions passando ponteiros NULL como argumentos. */

TEST (CompareTransactions, Null_Pointer) {

  EXPECT_EQ(CompareTransactions(&new_transaction, NULL), -1);
  EXPECT_EQ(CompareTransactions(NULL, &new_transaction), -1);
  EXPECT_EQ(CompareTransactions(NULL, NULL), -1);

}

 TEST (FinishTransaction, Normal_Transaction) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(UpdateTransaction(15, &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 15);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 15);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Closed);

}

TEST (FinishTransaction, Invalid_Grades) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(UpdateTransaction(15, &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 15);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

  EXPECT_EQ(FinishTransaction(&new_transaction, 13, 4, review1, review2),
            Illegal_argument);
  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 65, review1, review2),
            Illegal_argument);
  EXPECT_EQ(FinishTransaction(&new_transaction, 43, 42, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Status_Open) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 11);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Open);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Status_Cancelled) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(CancelTransaction(&new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 11);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, Canceled);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Status_Closed) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(UpdateTransaction(15, &new_transaction), Success);
  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Success);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Invalid_Users) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(UpdateTransaction(15, &new_transaction), Success);

  new_transaction.user2 = 11;

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 11);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);
  EXPECT_EQ(new_transaction.status, InProgress);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Invalid_Product) {

  EXPECT_EQ(StartTransaction(11, &new_product, &new_transaction), Success);
  EXPECT_EQ(UpdateTransaction(15, &new_transaction), Success);

  EXPECT_EQ(new_transaction.user1, 11);
  EXPECT_EQ(new_transaction.user2, 15);
  EXPECT_EQ(new_transaction.status, InProgress);

  CopyProduct(&(new_transaction.item), &invalid);

  ASSERT_EQ(CompareProducts(&(new_transaction.item), &invalid), 0);

  EXPECT_EQ(FinishTransaction(&new_transaction, 3, 4, review1, review2),
            Illegal_argument);

}

TEST (FinishTransaction, Invalid_Transaction) {

  EXPECT_EQ(FinishTransaction(NULL, 1, 4, review1, review2), Illegal_argument);
  EXPECT_EQ(FinishTransaction(&new_transaction, 1, 4, NULL, review2),
                              Illegal_argument);
  EXPECT_EQ(FinishTransaction(&new_transaction, 1, 4, review1, NULL),
                              Illegal_argument);
  EXPECT_EQ(FinishTransaction(NULL, 1, 4, NULL, NULL), Illegal_argument);

}

/*
  Finalização (desalocação de memória alocada dinamicamente) das variáveis
  utilizadas nos testes.
 */

TEST (Termination, Variables) {

  usuarios_limpar();

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
