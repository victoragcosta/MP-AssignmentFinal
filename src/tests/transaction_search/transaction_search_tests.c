// Módulo de busca de transações - Testes.

/**

  @file transaction_search_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de busca de transações
  do aplicativo.

*/

#include "transaction_search.h"

#include "gtest/gtest.h"

char name[75];
product new_product, new_product2, invalid;
transaction new_transaction, new_transaction2, new_transaction3, result;
transaction new_transaction4;
transactionList list, list2, matches;
userRestriction generic, specific;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  CleanTransactionList(&list);

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &new_product);

  strcpy(name, "Feijão");
  CreateProduct(name, Sale, 7, 92, &new_product2);

  strcpy(invalid.name, "Iate de ouro");
  invalid.price = 400000000;
  invalid.popularity = 60;
  invalid.type = Rental;

  StartTransaction(171, &new_product, &new_transaction);
  StartTransaction(705, &new_product2, &new_transaction2);

  CreateRestriction(Other, 0, 5, &generic);

  usuarios_carregarArquivo();

  EXPECT_EQ(1, true);

}

TEST (AddTransaction, First) {

  ASSERT_EQ(list.size, 0);

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(new_transaction.status, Open);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);

  EXPECT_EQ(AddTransaction(&new_transaction, &list), Success);

  ASSERT_EQ(list.size, 1);
  EXPECT_EQ(list.items[0].user1, 171);
  EXPECT_EQ(list.items[0].user2, 171);
  EXPECT_EQ(list.items[0].status, Open);
  EXPECT_EQ(CompareProducts(&(list.items[0].item), &new_product), 0);

}

/*
  Teste da função AddTransaction para adicionar o segundo produto à uma lista de
  produtos.
 */

TEST (AddTransaction, Second) {

  ASSERT_EQ(list.size, 1);

  EXPECT_EQ(new_transaction2.user1, 705);
  EXPECT_EQ(new_transaction2.user2, 705);
  EXPECT_EQ(new_transaction2.status, Open);
  EXPECT_EQ(CompareProducts(&(new_transaction2.item), &new_product2), 0);

  EXPECT_EQ(AddTransaction(&new_transaction2, &list), Success);

  ASSERT_EQ(list.size, 2);
  EXPECT_EQ(list.items[0].user1, 171);
  EXPECT_EQ(list.items[0].user2, 171);
  EXPECT_EQ(list.items[0].status, Open);
  EXPECT_EQ(CompareProducts(&(list.items[0].item), &new_product), 0);
  EXPECT_EQ(list.items[1].user1, 705);
  EXPECT_EQ(list.items[1].user2, 705);
  EXPECT_EQ(list.items[1].status, Open);
  EXPECT_EQ(CompareProducts(&(list.items[1].item), &new_product2), 0);

}

TEST (AddTransaction, Repeated_Transaction) {

  ASSERT_EQ(list.size, 2);

  EXPECT_EQ(AddTransaction(&new_transaction, &list), Failure);

  EXPECT_EQ(list.size, 2);

}

TEST (AddTransaction, Illegal_Status) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  new_transaction.status = Error;

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(new_transaction.status, Error);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);

  EXPECT_EQ(AddTransaction(&new_transaction, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddTransaction, Illegal_Users) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  new_transaction.status = InProgress;

  EXPECT_EQ(new_transaction.user1, 171);
  EXPECT_EQ(new_transaction.user2, 171);
  EXPECT_EQ(new_transaction.status, InProgress);
  EXPECT_EQ(CompareProducts(&(new_transaction.item), &new_product), 0);

  EXPECT_EQ(AddTransaction(&new_transaction, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddTransaction, Illegal_Product) {

  ASSERT_EQ(list.size, 0);

  new_transaction.user1 = 171;
  new_transaction.user2 = 171;
  new_transaction.status = Open;
  CopyProduct(&(new_transaction.item), &invalid);

  EXPECT_EQ(AddTransaction(&new_transaction, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddTransaction, Illegal_Transaction) {

  ASSERT_EQ(list.size, 0);

  StartTransaction(171, &new_product, &new_transaction);

  EXPECT_EQ(AddTransaction(NULL, &list), Illegal_argument);
  EXPECT_EQ(AddTransaction(&new_transaction, NULL), Illegal_argument);
  EXPECT_EQ(AddTransaction(NULL, NULL), Illegal_argument);

  ASSERT_EQ(list.size, 0);

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

TEST (CleanTransactionList, List_With_Items) {

  EXPECT_EQ(AddTransaction(&new_transaction, &list2), Success);
  EXPECT_EQ(AddTransaction(&new_transaction2, &list2), Success);

  ASSERT_EQ(list2.size, 2);
  ASSERT_EQ((list2.items != NULL), true);

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

TEST (CreateRestriction, Normal_Restriction) {

  EXPECT_EQ(CreateRestriction(Friend, 0, 5, &specific), Success);
  EXPECT_EQ(specific.proximity, Friend);
  EXPECT_EQ(specific.minimum_rating, 0);
  EXPECT_EQ(specific.maximum_rating, 5);

}

TEST (CreateRestriction, Invalid_Restriction) {

  EXPECT_EQ(CreateRestriction(Friend, 0, 5, NULL), Illegal_argument);

}

TEST (OpenTransactions, No_Restrictions) {

  /*
    O usuário 105 será o autor da nossa busca.
    A proximidade entre o usuário 105 e o usuário 130 é Friend.
    A proximidade entre o usuário 105 e o usuário 155 é FriendOfFriend.
    A proximidade entre o usuário 105 e o usuário 3 é Other.
   */

  CleanTransactionList(&list);

  CreateTransaction(130, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 16, &new_product2, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(11, 16, &new_product2, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(130, 130, &new_product, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(155, 155, &new_product, Open, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  CreateTransaction(3, 3, &new_product, Open, &new_transaction3);
  AddTransaction(&new_transaction3, &list);

  ASSERT_EQ(list.size, 6);
  ASSERT_EQ(generic.proximity, Other);
  ASSERT_EQ(generic.minimum_rating, 0);
  ASSERT_EQ(generic.maximum_rating, 5);

  ASSERT_EQ(OpenTransactions(105, &new_product, &generic, &list, &matches),
            Success);

  ASSERT_EQ(matches.size, 3);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[2]), &new_transaction3), 0);

}

TEST (OpenTransactions, Friend_Restriction) {

  /*
    O usuário 105 será o autor da nossa busca.
    A proximidade entre o usuário 105 e o usuário 130 é Friend.
    A proximidade entre o usuário 105 e o usuário 155 é FriendOfFriend.
    A proximidade entre o usuário 105 e o usuário 3 é Other.
   */

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(CreateRestriction(Friend, 0, 5, &specific), Success);

  ASSERT_EQ(OpenTransactions(105, &new_product, &specific, &list, &matches),
            Success);

  ASSERT_EQ(matches.size, 1);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);

}

TEST (OpenTransactions, Friend_Of_Friend_Restriction) {

  /*
    O usuário 105 será o autor da nossa busca.
    A proximidade entre o usuário 105 e o usuário 130 é Friend.
    A proximidade entre o usuário 105 e o usuário 155 é FriendOfFriend.
    A proximidade entre o usuário 105 e o usuário 3 é Other.
   */

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(CreateRestriction(FriendOfFriend, 0, 5, &specific), Success);

  ASSERT_EQ(OpenTransactions(105, &new_product, &specific, &list, &matches),
            Success);

  ASSERT_EQ(matches.size, 2);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);

}

TEST (OpenTransactions, Rating_Restriction_01) {

  /*
    O usuário 11 possui avaliação 4.
    O usuário 13 possui avaliação 3.
    O usuário 15 possui avaliação 3.
    O usuário 16 possui avaliação 0.
   */

  CleanTransactionList(&list);

  CreateTransaction(130, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(11, 16, &new_product2, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(11, 11, &new_product2, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(13, 13, &new_product2, Open, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  CreateTransaction(15, 15, &new_product2, Open, &new_transaction3);
  AddTransaction(&new_transaction3, &list);

  CreateTransaction(16, 16, &new_product2, Open, &new_transaction4);
  AddTransaction(&new_transaction4, &list);

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(CreateRestriction(Other, 3, 5, &specific), Success);

  ASSERT_EQ(OpenTransactions(171, &new_product2, &specific, &list, &matches),
            Success);

  ASSERT_EQ(matches.size, 3);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[2]), &new_transaction3), 0);

}

TEST (OpenTransactions, Rating_Restriction_02) {

  /*
    O usuário 11 possui avaliação 4.
    O usuário 13 possui avaliação 3.
    O usuário 15 possui avaliação 3.
    O usuário 16 possui avaliação 0.
   */

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(CreateRestriction(Other, 0, 3, &specific), Success);

  ASSERT_EQ(OpenTransactions(171, &new_product2, &specific, &list, &matches),
            Success);

  ASSERT_EQ(matches.size, 3);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction2), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction3), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[2]), &new_transaction4), 0);

}

TEST (OpenTransactions, No_Results) {

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(CreateRestriction(Friend, 4.5, 5, &specific), Success);

  ASSERT_EQ(OpenTransactions(171, &new_product, &specific, &list, &matches),
            Failure);

  ASSERT_EQ(matches.size, 0);

}

TEST (OpenTransactions, Invalid_Product) {

  ASSERT_EQ(list.size, 6);

  ASSERT_EQ(OpenTransactions(105, &invalid, &generic, &list, &matches),
            Illegal_argument);

  ASSERT_EQ(matches.size, 0);

}

TEST (OpenTransactions, Invalid_Adresses) {

  ASSERT_EQ(OpenTransactions(105, NULL, &generic, &list, &matches),
            Illegal_argument);
  ASSERT_EQ(OpenTransactions(105, &new_product, NULL, &list, &matches),
            Illegal_argument);
  ASSERT_EQ(OpenTransactions(105, &new_product, &generic, NULL, &matches),
            Illegal_argument);
  ASSERT_EQ(OpenTransactions(105, &new_product, &generic, &list, NULL),
            Illegal_argument);
  ASSERT_EQ(OpenTransactions(105, NULL, NULL, NULL, NULL), Illegal_argument);
}

TEST (ProductTransactions, Valid_Search) {

  CleanTransactionList(&list);

  CreateTransaction(16, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 16, &new_product, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  CreateTransaction(11, 16, &new_product2, InProgress, &new_transaction3);
  AddTransaction(&new_transaction3, &list);

  ASSERT_EQ(list.size, 6);

  EXPECT_EQ(ProductTransactions(&new_product2, &list, &matches), Success);

  EXPECT_EQ(matches.size, 3);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[2]), &new_transaction3), 0);

}

TEST (ProductTransactions, No_Results) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 3);

  EXPECT_EQ(ProductTransactions(&new_product, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (ProductTransactions, Empty_List) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  EXPECT_EQ(ProductTransactions(&new_product, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (ProductTransactions, Illegal_Product) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 1);

  EXPECT_EQ(ProductTransactions(&invalid, &list, &matches), Illegal_argument);

}

TEST (ProductTransactions, Illegal_Addresses) {

  EXPECT_EQ(ProductTransactions(NULL, &list, &matches), Illegal_argument);
  EXPECT_EQ(ProductTransactions(&new_product, NULL, &matches), Illegal_argument);
  EXPECT_EQ(ProductTransactions(&new_product, &list, NULL), Illegal_argument);
  EXPECT_EQ(ProductTransactions(NULL, NULL, NULL), Illegal_argument);

}

TEST (StatusTransactions, Valid_Search) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(43, 43, &new_product, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(11, 29, &new_product2, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  ASSERT_EQ(list.size, 6);

  EXPECT_EQ(StatusTransactions(Closed, &list, &matches), Success);

  ASSERT_EQ(matches.size, 2);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);

}

TEST (StatusTransactions, No_Results) {

  CleanTransactionList(&list);

  CreateTransaction(79, 79, &new_product2, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 3);

  EXPECT_EQ(StatusTransactions(Canceled, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (StatusTransactions, Empty_List) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  EXPECT_EQ(StatusTransactions(Open, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (StatusTransactions, Illegal_Status) {

  CleanTransactionList(&list);

  CreateTransaction(79, 79, &new_product2, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 3);

  EXPECT_EQ(StatusTransactions(Error, &list, &matches), Illegal_argument);

  EXPECT_EQ(matches.size, 0);

}

TEST (StatusTransactions, Illegal_Addresses) {

  EXPECT_EQ(StatusTransactions(Open, NULL, &matches), Illegal_argument);
  EXPECT_EQ(StatusTransactions(Open, &list, NULL), Illegal_argument);
  EXPECT_EQ(StatusTransactions(Open, NULL, NULL), Illegal_argument);

}

TEST (UserTransactions, Valid_Search) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 16, &new_product, Open, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  CreateTransaction(11, 16, &new_product2, InProgress, &new_transaction3);
  AddTransaction(&new_transaction3, &list);

  ASSERT_EQ(list.size, 6);

  EXPECT_EQ(UserTransactions(16, &list, &matches), Success);

  EXPECT_EQ(matches.size, 3);
  EXPECT_EQ(CompareTransactions(&(matches.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[1]), &new_transaction2), 0);
  EXPECT_EQ(CompareTransactions(&(matches.items[2]), &new_transaction3), 0);

}

TEST (UserTransactions, No_Results) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 3);

  EXPECT_EQ(UserTransactions(16, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (UserTransactions, Empty_List) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  EXPECT_EQ(UserTransactions(16, &list, &matches), Failure);

  EXPECT_EQ(matches.size, 0);

}

TEST (UserTransactions, Illegal_User) {

  CleanTransactionList(&list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 1);

  EXPECT_EQ(UserTransactions(0, &list, &matches), Illegal_argument);

}

TEST (UserTransactions, Illegal_Addresses) {

  EXPECT_EQ(UserTransactions(16, NULL, &matches), Illegal_argument);
  EXPECT_EQ(UserTransactions(16, &list, NULL), Illegal_argument);
  EXPECT_EQ(UserTransactions(16, NULL, NULL), Illegal_argument);

}

/* Teste da função SelectTransaction para uma seleção válida. */

TEST (SelectTransaction, Valid_Select) {

  CleanTransactionList(&list);

  CreateTransaction(171, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  ASSERT_EQ(list.size, 2);

  ASSERT_EQ(SelectTransaction(1, &list, &result), Success);
  EXPECT_EQ(CompareTransactions(&result, &(list.items[1])), 0);

}

/* Teste da função SelectTransaction para uma seleção com indíce inválido. */

TEST (SelectTransaction, Invalid_Select) {

  ASSERT_EQ(list.size, 2);

  ASSERT_EQ(SelectTransaction(2, &list, &result), Illegal_argument);

}

/*
  Teste da função SelectTransaction para ponteiros nulos passados como argumentos.
 */

TEST (SelectTransaction, Invalid_Adresses) {

  ASSERT_EQ(list.size, 2);

  ASSERT_EQ(SelectTransaction(0, NULL, &result), Illegal_argument);
  ASSERT_EQ(SelectTransaction(0, &list, NULL), Illegal_argument);
  ASSERT_EQ(SelectTransaction(0, NULL, NULL), Illegal_argument);

}

TEST (DeleteTransaction, Valid_Delete) {

  CleanTransactionList(&list);

  CreateTransaction(171, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction2);
  AddTransaction(&new_transaction2, &list);

  ASSERT_EQ(list.size, 2);
  EXPECT_EQ(CompareTransactions(&(list.items[0]), &new_transaction), 0);
  EXPECT_EQ(CompareTransactions(&(list.items[1]), &new_transaction2), 0);

  ASSERT_EQ(DeleteTransaction(0, &list), Success);
  ASSERT_EQ(list.size, 1);
  EXPECT_EQ(CompareTransactions(&(list.items[0]), &new_transaction2), 0);

}

/* Teste da função DeleteTransaction para uma deleção inválida. */

TEST (DeleteTransaction, Invalid_Delete) {

  ASSERT_EQ(list.size, 1);
  EXPECT_EQ(CompareTransactions(&(list.items[0]), &new_transaction2), 0);

  ASSERT_EQ(DeleteTransaction(1, &list), Illegal_argument);

}

/* Teste da função DeleteTransaction para uma lista vazia. */

TEST (DeleteTransaction, Empty_List) {

  CleanTransactionList(&list);

  ASSERT_EQ(list.size, 0);

  ASSERT_EQ(DeleteTransaction(0, &list), Illegal_argument);

}

TEST (SaveTransactionList, Valid_List) {

  CleanTransactionList(&list);

  CreateTransaction(171, 501, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(23, 12, &new_product2, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(16, 16, &new_product, Open, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(70, 79, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(230, 33, &new_product, Closed, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(11, 50, &new_product2, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list);

  CreateTransaction(45, 45, &new_product, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list);

  ASSERT_EQ(list.size, 7);

  EXPECT_EQ(SaveTransactionList(&list), Success);

}

TEST (SaveTransactionList, Invalid_List) {

  EXPECT_EQ(SaveTransactionList(NULL), Illegal_argument);

}

TEST (LoadTransactionList, Clean_List) {

  CleanTransactionList(&list2);

  ASSERT_EQ(list2.size, 0);

  EXPECT_EQ(LoadTransactionList(&list2), Success);

  EXPECT_EQ(list2.size, 7);

}

TEST (LoadTransactionList, List_With_Items) {

  CleanTransactionList(&list2);

  ASSERT_EQ(list2.size, 0);

  CreateTransaction(230, 230, &new_product, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list2);

  CreateTransaction(112, 80, &new_product, InProgress, &new_transaction);
  AddTransaction(&new_transaction, &list2);

  CreateTransaction(45, 77, &new_product2, Canceled, &new_transaction);
  AddTransaction(&new_transaction, &list2);

  ASSERT_EQ(list2.size, 3);

  EXPECT_EQ(LoadTransactionList(&list2), Success);

  EXPECT_EQ(list2.size, 7);

}

TEST (LoadTransactionList, Invalid_List) {

  EXPECT_EQ(LoadTransactionList(NULL), Illegal_argument);

}

/*
  Finalização (desalocação de memória alocada dinamicamente) das variáveis
  utilizadas nos testes.
 */

TEST (Termination, Variables) {

  CleanTransactionList(&list);
  CleanTransactionList(&list2);
  CleanTransactionList(&matches);

  usuarios_limpar();

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
