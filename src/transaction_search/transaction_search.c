// Módulo de busca de transações.

/**
 * @file transaction_search.c
 * @brief Implementação do módulo de busca de transações.
 */

#include "transaction_search.h"

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
