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
