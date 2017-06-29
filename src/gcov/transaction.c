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

errorLevel CopyTransaction(transaction *copy, transaction *original) {

  if(copy == NULL || original == NULL)
    return Illegal_argument;

  copy->user1 = original->user1;
  copy->user2 = original->user2;
  copy->status = original->status;
  CopyProduct(&(copy->item), &(original->item));

  return Success;

}

errorLevel CreateTransaction(unsigned int user_id, product *item,
                             transaction *new_transaction) {

  if(item == NULL || new_transaction == NULL || !ValidProduct(item))
    return Illegal_argument;

  new_transaction->user1 = user_id;
  new_transaction->user2 = user_id;
  new_transaction->status = Open;
  CopyProduct(&(new_transaction->item), item);

  return Success;

}

errorLevel FinishTransaction(
    transaction *given_transaction,
    unsigned int grade1,
    unsigned int grade2,
    char comment1[AVALIACAO_LIMITE_COMENTARIO],
    char comment2[AVALIACAO_LIMITE_COMENTARIO]) {

  if(given_transaction == NULL || !ValidTransaction(given_transaction)
     || given_transaction->status != InProgress || !ValidGrade(grade1)
     || !ValidGrade(grade2))
    return Illegal_argument;

  given_transaction->status = Closed;

  if(avaliacao_avaliar(given_transaction->user1, given_transaction->user2,
                       grade1, comment1) != AVALIACAO_SUCESSO
     || avaliacao_avaliar(given_transaction->user2, given_transaction->user1,
                          grade2, comment2) != AVALIACAO_SUCESSO)
    return Failure;

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

int CompareTransactions(transaction *first, transaction *second) {

  if(first == NULL || second == NULL)
    return -1;

  /*
    Verifica-se individualmente se cada um dos campos das 2 transações são
    iguais.
   */

  else if(first->user1 == second->user1 && first->user2 == second->user2
     && first->status == second->status
     && !CompareProducts(&(first->item), &(second->item)))
    return 0;

  else
    return 1;

}

int ValidGrade (unsigned int grade) {

  if(grade <= 5)
    return 1;

  else
    return 0;

}

int ValidTransaction (transaction *given_transaction) {

  if(given_transaction == NULL)
    return -1;

  else if(!ValidProduct(&(given_transaction->item))
          || (given_transaction->user1 == given_transaction->user2
          && given_transaction->status != Open))
    return 0;

  else
    return 1;

}
