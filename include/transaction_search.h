// Módulo de busca de transações - Cabeçalho.

/**
 * @file transaction.h
 * @brief Cabeçalho do módulo de transações.
 */

#ifndef TRANSACTION_SEARCH_H_
#define TRANSACTION_SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "avaliacao.h"
#include "error_level.h"
#include "product.h"
#include "transaction.h"

typedef enum {
  Friend,
  FriendOfFriend,
  Other
}relationship;

typedef struct userRestriction {
  relationship proximity;
  double minimum_rating;
  double maximum_rating;
}userRestriction;

typedef struct transactionList {
  transaction *items; /**< Items na lista. Vetor de tipo transaction. */
  int size; /**< Tamanho da lista. Não pode ser negativo. */
}transactionList;

errorLevel CleanTransactionList(transactionList*);
errorLevel CreateRestriction(relationship, double, double, userRestriction*);

#endif  // TRANSACTION_SEARCH_H_
