// Módulo de transações - Cabeçalho.

/**
 * @file transaction.h
 * @brief Cabeçalho do módulo de transações.
 */

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "avaliacao.h"
#include "error_level.h"
#include "product.h"

typedef enum {
  Open,
  InProgress,
  Closed,
  Canceled
}transactionStatus;

typedef struct transaction {
  unsigned int user1;
  unsigned int user2;
  product item;
  transactionStatus status;
}transaction;

/*
  avaliacao new1, new2;

  &new1 = avaliacao_iniciar();
  avaliacao_definir(&new1, "o que", dado);
  avaliacao_fazerAvaliacao(&avaliacao);
*/

errorLevel CancelTransaction(transaction*);
errorLevel CopyTransaction(transaction*, transaction*);
errorLevel CreateTransaction(unsigned int, product*, transaction*);
errorLevel UpdateTransaction(unsigned int, transaction*);
int CompareTransactions(transaction*, transaction*);
int ValidTransaction(transaction*);

#endif  // TRANSACTION_H_
