// Módulo de busca de transações.

/**
 * @file transaction_search.c
 * @brief Implementação do módulo de busca de transações.
 */

#include "transaction_search.h"

errorLevel AddTransaction(transaction *given_transaction,
                          transactionList *list) {

  int i, empty_slot;

  if(given_transaction == NULL || list == NULL
     || !ValidTransaction(given_transaction))
    return Illegal_argument;

  for (i = 0; i < (list->size); ++i)
    if(!CompareTransactions(&(list->items[i]), given_transaction))
      return Failure;

  /*
    Caso o produto passado como argumento contenha campos válidos e ainda não
    pertença à lista, adiciona-se o produto à lista.
   */

  list->size++; /* Aumenta-se o tamanho da lista devido à adição. */

  /*
    Caso o produto adicionado seja o primeiro da lista, utiliza-se a função
    malloc para gerar o vetor de produtos. Do contrário, utiliza-se a função
    realloc para realocar o vetor de produtos.
   */

  if(list->size == 1)
    list->items = (transaction*) malloc(sizeof(transaction));

  else
    list->items = (transaction*) realloc(list->items,
                                         list->size * sizeof(transaction));

  empty_slot = (list->size)-1; /* Posição vaga na lista. */

  CopyTransaction(&(list->items[empty_slot]), given_transaction);

  return Success;

}

errorLevel CleanTransactionList(transactionList *list) {

  if(list == NULL)
    return Illegal_argument;

  list->size = 0;

  if(list->items != NULL) {
    free(list->items);
    list->items = NULL;
  }

  return Success;

}

errorLevel CreateRestriction(relationship proximity, double min_rating,
                             double max_rating, userRestriction *restriction) {

  if(restriction == NULL)
    return Illegal_argument;

  restriction->proximity = proximity;
  restriction->minimum_rating = min_rating;
  restriction->maximum_rating = max_rating;

  return Success;

}

errorLevel DeleteTransaction (int index, transactionList *list) {

  int i;

  if(list == NULL || !ValidIndex(index, list->size)) {
    return Illegal_argument;
  }

  /*
    Caso a lista contenha apenas 1 item, libera-se o vetor de items e atribui-se
    a ele o valor NULL.
   */

  else if(list->size == 1) {
    free(list->items);
    list->items = NULL;
  }

  /* Caso contrário, o procedimento de deleção é mais complicado. */

  else {

    /*
      Primeiro, vamos "mover" todos os elementos do vetor de produtos que estão
      à direita do produto a ser removido uma "posição" para esquerda.
      Atingimos tal resultado sobrescrevendo o produto a ser removido com o
      produto que está a sua direita (o que pode ser feito com a função de
      copiar produtos) e repetindo esse procedimento até o penúltimo produto do
      vetor de produtos.
     */

    for (i = index; i < list->size - 1; ++i)
      CopyTransaction(&(list->items[i]), &(list->items[i + 1]));

      /*
        Por fim, basta realocar a lista para que ela tenha um espaço a menos.
        Como o produto da última posição terá sido copiado para a penúltima
        posição, o produto que será "perdido" com o realocamento do vetor será
        aquele que deveria ser removido.
       */

    list->items = (transaction*) realloc(list->items, (list->size - 1)
                                     * sizeof(transaction));

  }

  /*
    Após uma deleção bem sucedida, deve-se diminuir o tamanho da lista em uma
    unidade.
   */

  (list->size) -= 1;

  return Success;

}

errorLevel LoadTransactionList(transactionList *list) {

  FILE *fp;
  transaction new_transaction;
  product item;
  char name[75];
  productType type;
  double price;
  int popularity, auxiliary1, auxiliary2;
  unsigned int user1, user2;
  transactionStatus status;

  if(list == NULL)
    return Illegal_argument;

  fp = fopen(TRANSACTION_DB, "r");

  if(fp == NULL)
    return Failure;

  CleanTransactionList(list);

  while(fscanf(fp, "%u|%u|%[^|]|%d|%lf|%d|%d\n", &user1, &user2, name,
               &auxiliary1, &price, &popularity, &auxiliary2) != EOF) {

    if (ConvertIntToProductType(auxiliary1, &type) == 0
        && ConvertIntToTransactionStatus(auxiliary2, &status) == 0) {

      CreateProduct(name, type, price, popularity, &item);
      CreateTransaction(user1, user2, &item, status, &new_transaction);
      AddTransaction(&new_transaction, list);

    }

  }

  fclose(fp);

  return Success;

}

errorLevel SaveTransactionList(transactionList *list) {

  FILE *fp;
  int i;

  if(list == NULL)
    return Illegal_argument;

  fp = fopen(TRANSACTION_DB, "w");

  if(fp == NULL)
    return Failure;

  for (i = 0; i < list->size; i++)
    fprintf(fp, "%u|%u|%s|%d|%lf|%d|%d\n", list->items[i].user1,
            list->items[i].user2, list->items[i].item.name,
            list->items[i].item.type, list->items[i].item.price,
            list->items[i].item.popularity, list->items[i].status);

  fclose(fp);

  return Success;

}

errorLevel SelectTransaction(int index, transactionList *list,
                             transaction *selection) {

  if(list == NULL || selection == NULL || !ValidIndex(index, list->size))
    return Illegal_argument;

  CopyTransaction(selection, &(list->items[index]));

  return Success;

}

errorLevel UserTransactions(unsigned int user, transactionList *list,
                            transactionList *matches) {

  int i;

  if(list == NULL || matches == NULL)
    return Illegal_argument;

  CleanTransactionList(matches);

  for (i = 0; i < (list->size); ++i)
    if(user == list->items[i].user1 || user == list->items[i].user2)
      AddTransaction(&(list->items[i]), matches);

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

int MatchesRestriction(unsigned int original_user, unsigned int given_user,
                       userRestriction *restriction) {

  double rating;
  unsigned int i;
  usuarios_uintarray friends, friends_of_friends;
  relationship proximity;

  if(restriction == NULL
     || usuarios_retornaDados(given_user, "avaliacao", &rating)
     != USUARIOS_SUCESSO
     || usuarios_listarAmigos(given_user, &friends)
     != USUARIOS_SUCESSO
     || usuarios_listarAmigosdeAmigos(given_user, &friends_of_friends)
     != USUARIOS_SUCESSO) {
    return -1;
  }

  else if(rating > restriction->maximum_rating
     || rating < restriction->minimum_rating) {
    return 0;
  }

  else {

    if(restriction->proximity == Other){
      return 1;
    }

    else {

      proximity = Other;

      for(i = 0; i < friends.length; i++)
        if(friends.array[i] == original_user)
          proximity = Friend;

      if((restriction->proximity == Friend
         || restriction->proximity == FriendOfFriend) && proximity == Friend)
        return 1;

      for(i = 0; i < friends_of_friends.length; i++)
        if(friends_of_friends.array[i] == original_user)
          proximity = FriendOfFriend;

      if(restriction->proximity == FriendOfFriend
         && proximity == FriendOfFriend)
        return 1;

      return 0;

    }

  }

}
