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

#include "avaliacao.h"
#include "error_level.h"
#include "product.h"
#include "transaction.h"
#include "usuarios.h"
#include "valid_index.h"

/**
 * @def TRANSACTION_DB
 * @brief Caminho ao banco de dados das transações.
 */

#define TRANSACTION_DB "../db/transactions.txt"

/**
 * @enum relationship
 * @brief Contém os possíveis relacionamentos entre usuários.
 *
 * É utilizado como um dos membros da estrutura de dados que modela as
 * restrições de usuário na busca por transações.
 *
 */

typedef enum {
  Friend,  /**< Os usuários são amigos. */
  FriendOfFriend,  /**< Os usuários são amigos de amigos. */
  Other  /**< Os usuários são estranhos. */
}relationship;

/**
 * @typedef userRestriction
 * @brief Restrição de usuários.
 *
 * Restringe a busca por transações abertas ao especificar a proximidade e a
 * avaliação dos usuários com quem se deseja realizar a transação.
 *
 */

typedef struct userRestriction {
  relationship proximity;  /**< Relacionamento com o usuário da transação. */
  double minimum_rating;  /**< Avaliação mínima do usuário da transação. */
  double maximum_rating;  /**< Avaliação máxima do usuário da transação. */
}userRestriction;

/**
 * @typedef transactionList
 * @brief Lista de transações.
 *
 * Não pode conter transações repetidas ou inválidas.
 *
 * Importante: Aloca dinamicamente o vetor que contém as transações. Tal memória
 * deve ser liberada no término do programa chamando-se a função
 * CleanTransactionList(transactionList*) ou por meio da função
 * free(transactionList.items).
 *
 * Exemplo:
 *
 *  transactionList lista_exemplo;
 *
 *  (Utilização da lista_exemplo)
 *
 *  CleanTransactionList(&lista_exemplo);
 *
 */

typedef struct transactionList {
  transaction *items; /**< Items na lista. Vetor de tipo transaction. */
  int size; /**< Tamanho da lista. Não pode ser negativo. */
}transactionList;

errorLevel AddTransaction(transaction*, transactionList*);
errorLevel CleanTransactionList(transactionList*);
errorLevel CreateRestriction(relationship, double, double, userRestriction*);
errorLevel DeleteTransaction(int, transactionList*);
errorLevel LoadTransactionList(transactionList*);
errorLevel OpenTransactions(unsigned int, product*, userRestriction*,
                            transactionList*, transactionList*);
errorLevel ProductTransactions(product*, transactionList*, transactionList*);
errorLevel SaveTransactionList(transactionList*);
errorLevel SelectTransaction(int, transactionList*, transaction*);
errorLevel StatusTransactions(transactionStatus, transactionList*,
                              transactionList*);
errorLevel UserTransactions(unsigned int, transactionList*, transactionList*);
int MatchesRestriction(unsigned int, unsigned int, userRestriction*);

#endif  // TRANSACTION_SEARCH_H_
