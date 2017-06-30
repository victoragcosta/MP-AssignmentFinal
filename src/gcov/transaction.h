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

#include "avaliacao.h"
#include "error_level.h"
#include "product.h"
#include "usuarios.h"

typedef enum {
  Open,
  InProgress,
  Closed,
  Canceled,
  Error
}transactionStatus;

typedef struct transaction {
  unsigned int user1;
  unsigned int user2;
  product item;
  transactionStatus status;
}transaction;

errorLevel CancelTransaction(transaction*);
errorLevel CopyTransaction(transaction*, transaction*);
errorLevel CreateTransaction(unsigned int, unsigned int, product*,
                             transactionStatus, transaction*);
errorLevel FinishTransaction(transaction*, unsigned int, unsigned int,
                             char[AVALIACAO_LIMITE_COMENTARIO],
                             char[AVALIACAO_LIMITE_COMENTARIO]);
errorLevel StartTransaction(unsigned int, product*, transaction*);
errorLevel UpdateTransaction(unsigned int, transaction*);
int CompareTransactions(transaction*, transaction*);
int ConvertIntToTransactionStatus(int, transactionStatus*);
int ValidGrade(unsigned int);
int ValidTransaction(transaction*);
int ValidTransactionArguments(unsigned int, unsigned int, product*,
                              transactionStatus);

#endif  // TRANSACTION_H_
