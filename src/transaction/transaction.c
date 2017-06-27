// Módulo de transações.

/**
 * @file transaction.c
 * @brief Implementação do módulo de transações.
 */

#include "transaction.h"

errorLevel CancelTransaction(transaction *target_transaction) {

  if(target_transaction == NULL || target_transaction->status == Closed
     || target_transaction->status == Canceled)
    return Illegal_argument;

  target_transaction->status = Canceled;

  return Success;

}

errorLevel CreateTransaction(unsigned int user_id, product *item,
                             transaction *new_transaction) {

  if(item == NULL || new_transaction == NULL)
    return Illegal_argument;

  new_transaction->user1 = user_id;
  new_transaction->user2 = user_id;
  new_transaction->status = Open;
  CopyProduct(&(new_transaction->item), item);

  return Success;

}

errorLevel UpdateTransaction(unsigned int user_id,
                             transaction *started_transaction) {

  if(started_transaction == NULL || started_transaction->status != Open
     || user_id == started_transaction->user1)
    return Illegal_argument;

  started_transaction->user2 = user_id;
  started_transaction->status = InProgress;

  return Success;

}
