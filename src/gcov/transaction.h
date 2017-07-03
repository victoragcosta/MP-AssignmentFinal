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

/**
 * @enum transactionStatus
 * @brief Contém os possíveis estados de uma transação
 *
 * É utilizado como um dos membros da estrutura de dados que modela uma
 * transação e atulizada a cada estágio da transação. Pode ser utilizada como
 * parâmetro de busca de uma transação na função StatusTransactions.
 *
 */

typedef enum {
  Open,  /**< A transação está aberta para a entrada de um usuário. */
  InProgress,  /**< A transação está sendo realizada. */
  Closed,  /**< A transação foi realizada com sucesso. */
  Canceled,  /**< A transação foi cancelada. */
  Error  /**< Ocorreu um erro na leitura do estado ou no processamento da
             transação. Não é um estado válido de transação. */
}transactionStatus;

/**
 * @typedef transaction
 * @brief Transação.
 *
 * Representa uma transação entre 2 usuários envolvendo um produto.
 *
 */

typedef struct transaction {
  unsigned int user1;  /**< Primeiro usuário envolvido na transação. */
  unsigned int user2;  /**< Segundo usuário envolvido na transação. */
  product item;  /**< Produto transacionado. */
  transactionStatus status;  /**< Estado da transação. */
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
