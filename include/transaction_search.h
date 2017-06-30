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

#define TRANSACTION_DB "../../db/transactions.txt"

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

/*
  Usuario_login

  Retorna avaliacao;
  usuarios_retornaDados(unsigned int, "avaliacao", &unsigned int);

  Relacao de amizade:
  usuarios_verificaramizade(unsigned int) == AMIGOS (Amigos)
  usuarios_listarAmigosdeAmigos(unsigned int, usuarios_uintarray*)
  unsigned int pertence à usuarios_uintarray (AMIGOSDEAMIGOS)

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
