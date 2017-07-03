// Módulo de transações.

/**
 * @file transaction.c
 * @brief Implementação do módulo de transações.
 */

#include "transaction.h"

/**
 * @fn errorLevel CancelTransaction(transaction *target_transaction)
 * @brief Função que cancela uma transação.
 * @param target_transaction Transação que será cancelada. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja cancelada com sucesso; Illegal_argument caso o argumento
 * passado para a função seja uma transação inválida, uma transação cujo estado
 * é diferente de "Open" ou de "InProgress" ou um ponteiro NULL.
 *
 * Atualiza o estado de uma transação válida de "Open" ou de "InProgress" para
 * "Canceled".
 *
 * Assertivas de entrada:
 *  -O parâmetro target_transaction deve ser diferente de NULL.
 *  -O parâmetro target_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -O estado de target_transaction deve ser "Open" ou "InProgress".
 *  -O parâmetro target_transaction deve ser uma transação válida.
 *
 * Assertivas de saída:
 *  -O estado de target_transaction será "Canceled".
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -Caso target_transaction seja uma transação válida cujo estado é "Open" ou
 * "InProgress", seu estado será atualizado para "Canceled".
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CancelTransaction(transaction *target_transaction) {

  /*
    Uma transação só pode ser cancelada se ela é válida e se o seu status é Open
    ou InProgress, pois não faz sentido cancelar transações já finalizadas
    (status = Closed), transações já canceladas (status = Canceled) ou
    transações que geraram erros (status = Error).
   */

  if(target_transaction == NULL || (target_transaction->status != Open
     && target_transaction->status != InProgress)
     || (ValidTransaction(target_transaction) != 1))
    return Illegal_argument;

  target_transaction->status = Canceled;

  return Success;

}

/**
 * @fn errorLevel CopyTransaction(transaction *copy, transaction *original)
 * @brief Função que copia uma transação.
 * @param copy Endereço da transação que receberá as especificações copiadas.
 * Argumento passado por referência.
 * @param original Endereço da transação que será copiada.
 * Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja copiada com sucesso; Illegal_argument caso um dos argumentos
 * passados seja um ponteiro nulo.
 *
 * Copia os dados de uma transação para outra transação.
 *
 * Assertivas de entrada:
 *  -Ambos copy e original devem ser diferentes de NULL.
 *  -Ambos copy e original devem apontar para estruturas de dados do tipo
 *   transaction.
 *
 * Assertivas de saída:
 *  -Os parâmetros da transação no endereço copy serão os mesmos que os
 * parâmetros da transação no endereço original.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço copy serão sobrescritas pelas
 * informações contidas no endereço original.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo transaction alocadas estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 */

errorLevel CopyTransaction(transaction *copy, transaction *original) {

  if(copy == NULL || original == NULL)
    return Illegal_argument;

  copy->user1 = original->user1;
  copy->user2 = original->user2;
  copy->status = original->status;
  CopyProduct(&(copy->item), &(original->item));

  return Success;

}

/**
 * @fn errorLevel CreateTransaction(unsigned int user_id1,
 * unsigned int user_id2, product *item, transactionStatus status, transaction
 * *new_transaction)
 * @brief Função que cria uma transação.
 * @param user_id1 Primeiro usuário da transação a ser criada.
 * @param user_id2 Segundo usuário da transação a ser criada.
 * @param item Endereço para o produto transacionado na transação a ser criada.
 * Argumento passado por referência.
 * @param status Estado da transação a ser criada.
 * @param new_transaction Endereço da estrutura de dados onde a transação será
 * criada. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja criada com sucesso; Illegal_argument caso os argumentos
 * passados para a criação da transação sejam inválidos ou caso um dos
 * argumentos passados seja um ponteiro nulo.
 *
 * Atualiza os dados de uma estrutura de dados do tipo transaction a partir de
 * dois unsigned ints, uma estrutura de dados do tipo product e uma estrutura de
 * dados do tipo transactionStatus. Os dados em new_transaction são sobrescritos
 * com os dados fornecidos como argumentos da função.
 *
 * Assertivas de entrada:
 *  -Ambos item e new_transaction devem ser diferentes de NULL.
 *  -O parâmetro item deve apontar para uma estrutura de dados do tipo
 * product.
 *  -O parâmetro new_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -Os parâmetros user_id1, user_id2, item e status devem gerar uma transação
 * válida.
 *
 * Assertivas de saída:
 *  -Os membros da transação no endereço new_transaction serão aqueles passados
 * como argumentos para a função.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço new_transaction serão sobrescritas
 * pelas informações passadas como argumentos da função.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CreateTransaction(unsigned int user_id1, unsigned int user_id2,
                             product *item, transactionStatus status,
                             transaction *new_transaction) {

  if(item == NULL || new_transaction == NULL
     || (ValidTransactionArguments(user_id1, user_id2, item, status) != 1))
    return Illegal_argument;

  new_transaction->user1 = user_id1;
  new_transaction->user2 = user_id2;
  new_transaction->status = status;
  CopyProduct(&(new_transaction->item), item);

  return Success;

}

/**
 * @fn errorLevel FinishTransaction(transaction *given_transaction, unsigned
 * int grade1, unsigned int grade2, char comment1[AVALIACAO_LIMITE_COMENTARIO],
 * char comment2[AVALIACAO_LIMITE_COMENTARIO])
 * @brief Função que finaliza uma transação.
 * @param given_transaction Transação que será finalizada. Argumento passado por
 * referência.
 * @param grade1 Nota dada pelo primeiro usuário ao segundo usuário.
 * @param grade2 Nota dada pelo segundo usuário ao primeiro usuário.
 * @param comment1 Comentário feito pelo primeiro usuário acerca do segundo
 * usuário.
 * @param comment2 Comentário feito pelo segundo usuário acerca do primeiro
 * usuário.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja finalizada com sucesso; Failure caso as avaliações feitas
 * pelos usuários não sejam lançadas com sucesso; Illegal_argument caso os
 * argumentos passados para a finalização da transação sejam inválidos, caso a
 * transação em si seja inválida ou caso um dos argumentos passados seja um
 * ponteiro nulo.
 *
 * Altera o estado de uma transação de "InProgress" para "Closed". Lança as
 * avaliações feitas pelos usuários no término da transação.
 *
 * Assertivas de entrada:
 *  -Os parâmetros given_transaction, comment1 e comment2 devem ser diferentes
 * de NULL.
 *  -O parâmetro given_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -Os parâmetros comment1 e comment2 devem apontar para um vetor de
 * caracteres.
 *  -A transação given_transaction deve ser uma transação válida.
 *  -A transação given_transaction deve ter estado igual a "InProgress".
 *  -Os parâmetros grade1 e grade2 devem ser números entre 0 e 5.
 *
 * Assertivas de saída:
 *  -O estado de given_transaction será "Closed".
 *  -As avaliações feitas pelo primeiro usuário e pelo segundo usuário terão
 * sido lançadas.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -Caso os argumentos da função sejam argumentos válidos, o estado de
 * given_transaction será alterado de "InProgress" para "Closed" e as avalições
 * feitas pelo primeiro e pelo segundo usuário serão lançadas.
 *
 * Requisitos:
 *  -O grafo de usuários deve ter sido gerado.
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  -O banco de dados de avaliações está configurado corretamente.
 *
 */

errorLevel FinishTransaction(
    transaction *given_transaction,
    unsigned int grade1,
    unsigned int grade2,
    char comment1[AVALIACAO_LIMITE_COMENTARIO],
    char comment2[AVALIACAO_LIMITE_COMENTARIO]) {

  /*
    Uma transação só pode ser finalizada caso seu status seja InProgress e caso
    os argumentos fornecidos para a função sejam válidos.
  .*/

  if(given_transaction == NULL || comment1 == NULL || comment2 == NULL
     || (ValidTransaction(given_transaction) != 1)
     || given_transaction->status != InProgress || !ValidGrade(grade1)
     || !ValidGrade(grade2))
    return Illegal_argument;

  /*
    Para que uma transação seja finalizada, os usuários que participaram da
    transação devem se avaliar. Caso não seja possível realizar as avaliações
    entre os usuários, diz-se que a finalização de transação falhou.
   */

  if(avaliacao_avaliar(given_transaction->user1, given_transaction->user2,
                       grade1, comment1) != AVALIACAO_SUCESSO
     || avaliacao_avaliar(given_transaction->user2, given_transaction->user1,
                          grade2, comment2) != AVALIACAO_SUCESSO)
    return Failure;

  /*
    Somente caso as avaliações sejam feitas com sucesso é que se atribui o
    status "Closed" para a transação.
   */

  given_transaction->status = Closed;

  return Success;

}

/**
 * @fn errorLevel StartTransaction(unsigned int user_id, product *item,
 * transaction *new_transaction)
 * @brief Função que abre uma transação.
 * @param user_id Identificador do usuário que iniciou a transação.
 * @param item Item transacionado. Argumento passado por referência.
 * @param new_transaction Transação que será iniciada. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja aberta com sucesso; Illegal_argument caso os argumentos
 * passados para a função sejam inválidos ou ponteiros NULL.
 *
 * Cria uma transação cujos identificadores de usuário user1 e user2 sejam
 * user_id, cujo estado é "Open" e cujo produto transacionado é item.
 *
 * Assertivas de entrada:
 *  -Os parâmetros item e new_transaction devem ser diferentes de NULL.
 *  -O parâmetro item deve apontar para uma estrutura de dados do tipo
 * product.
 *  -O parâmetro new_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -O parâmetro user_id deve ser diferente de 0.
 *  -O parâmetro item deve ser um produto válido.
 *
 * Assertivas de saída:
 *  -A transação new_transaction terá como user1 e user2 o identificador
 * user_id, como produto transacionado o produto item e terá o estado "Open".
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -Caso user_id e item sejam argumentos válidos, sobrescreve-se os membros de
 * new_transaction para que esta seja uma transação que cujos usuários
 * envolvidos ambos sejam user_id, cujo produto transacionado seja item e cujo
 * estado seja aberto.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel StartTransaction(unsigned int user_id, product *item,
                             transaction *new_transaction) {

  if(item == NULL || new_transaction == NULL || (ValidProduct(item) != 1)
     || user_id == 0)
    return Illegal_argument;

  /*
    Em uma transação aberta, há apenas um usuário presente, esperando outro
    usuário envolver-se na transação. Entretanto, a função possui dois campos
    para id de usuário. Para resolver esse problema, copia-se o id do único
    usuário presente na transação nos dois campos. Por esse motivo, uma
    transação de status "Open" sempre deve ter os campos user1 e user2 iguais.
    Do contrário, a transação não será válida.
   */

  new_transaction->user1 = user_id;
  new_transaction->user2 = user_id;
  new_transaction->status = Open;
  CopyProduct(&(new_transaction->item), item);

  return Success;

}

/**
 * @fn errorLevel UpdateTransaction(unsigned int user_id, transaction
 * *started_transaction)
 * @brief Função que atualiza uma transação.
 * @param user_id Identificador do usuário que entrará na transação.
 * @param started_transaction Transação iniciada que receberá um segundo
 * usuário. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja atualizada com sucesso; Illegal_argument caso os argumentos
 * passados para a função sejam inválidos ou ponteiros NULL.
 *
 * Modifica o campo user2 de uma transação cujo estado seja "Open" para incluir
 * um segundo usuário na transação. Muda o estado da transação para
 * "InProgress".
 *
 * Assertivas de entrada:
 *  -O parâmetro started_transaction deve ser diferente de NULL.
 *  -O parâmetro started_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -O parâmetro user_id deve ser diferente de 0.
 *  -O parâmetro started_transaction deve ser uma transação válida.
 *
 * Assertivas de saída:
 *  -A transação started_transaction terá como user2 o identificador user_id e
 * terá o estado "InProgress".
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -Caso user_id e started_transaction sejam argumentos válidos, sobrescreve-se
 * os membros user2 e estado de started_transaction para esta tenha o campo
 * user2 igual a user_id e estado igual a "InProgress".
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel UpdateTransaction(unsigned int user_id,
                             transaction *started_transaction) {

  /*
    Só se pode atualizar transações válidas e de status "Open" e nunca pode-se
    fazê-lo com o mesmo usuário que já estava na transação ou com o id 0, por
    ser um id de usuário inválido nesse contexto.
   */

  if(started_transaction == NULL || started_transaction->status != Open
     || user_id == started_transaction->user1 || user_id == 0
     || (ValidTransaction(started_transaction) != 1))
    return Illegal_argument;

  /*
    Para atualizar uma transação, modifica-se o segundo usuário da transação e
    atribui-se a ela o status "InProgress".
   */

  started_transaction->user2 = user_id;
  started_transaction->status = InProgress;

  return Success;

}

/**
 * @fn int CompareTransactions(transaction *first, transaction *second)
 * @brief Função que compara duas transações.
 * @param first Endereço da primeira transação que faz parte da comparação.
 * Argumento passado por referência.
 * @param second Endereço da segunda transação que faz parte da comparação.
 * Argumento passado por referência.
 * @return A função retorna -1 caso algum dos argumentos seja um ponteiro nulo,
 * 0 caso as transações sejam iguais e 1 caso sejam diferentes.
 *
 * Verifica se todos os campos de duas estruturas de dados do tipo transaction
 * são iguais. Compara-se manualmente cada campo das duas transações.
 *
 * Assertivas de entrada:
 *  -Ambas first e second devem ser diferentes de NULL.
 *  -Ambas first e second devem apontar para estruturas de dados do tipo
 *   transaction.
 *
 * Assertivas de saída:
 *  -Os parâmetros da transação no endereço first e second estarão inalterados.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se as transações são iguais ou
 * não ou se os argumentos passados são ilegais, sem alterar as transações em
 * si.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo transaction alocadas estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

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

/**
 * @fn int ConvertIntToTransactionStatus(int number, transactionStatus *status)
 * @brief Função que converte um inteiro para um estado de transação.
 * @param number Número convertido.
 * @param status Endereço de variável do tipo transactionStatus que recebe o
 * resultado da conversão.
 * @return A função retorna um inteiro: 0 se a conversão foi bem sucedida; -1 se
 * a função recebeu um ponteiro NULL como argumento.
 *
 * Realiza a conversão de um número inteiro para seu respectivo estado de
 * transação contido na enumeração transactionStatus e atribui esse resultado
 * para a estrutura de dados transactionStatus no endereço status. Caso o número
 * não represente um transactionStatus válido, será atribuído o
 * transactionStatus "Error".
 *
 * Assertivas de entrada:
 *  -status != NULL.
 *  -status aponta para uma estrutura de dados do tipo transactionStatus.
 *
 * Assertivas de saída:
 *  -O estado de transação contido em status será equivalente ao estado de
 * transação representado por number.
 *
 * Assertivas estruturais:
 *  -Um estrutura de dados do tipo transactionStatus equivale a "Open,
 * "InProgress", "Closed", "Canceled" ou "Error".
 *
 * Assertivas de contrato:
 *  -A função sobrescreverá o estado de transação contido no endereço status com
 * o estado de transação obtido na conversão do inteiro number para um estado de
 * transação.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transactionStatus alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ConvertIntToTransactionStatus(int number, transactionStatus *status) {

  if(status == NULL)
    return -1;

  switch (number) {

    case 0:
      *status = Open;
      break;

    case 1:
      *status = InProgress;
      break;

    case 2:
      *status = Closed;
      break;

    case 3:
      *status = Canceled;
      break;

    default:
      *status = Error;

  }

  return 0;

}

/**
 * @fn int ValidGrade (unsigned int grade)
 * @brief Função que verifica se uma nota é válida.
 * @param grade Nota testada.
 * @return A função retorna um inteiro: 1 se a nota é válida; 0 se a nota é
 * inválida.
 *
 * Verifica se uma está contida no intervalo de notas válidas definido
 * previamente.
 *
 * Assertivas de entrada:
 *  Nenhuma.
 *
 * Assertivas de saída:
 *  Nenhuma.
 *
 * Assertivas estruturais:
 *  Nenhuma.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se a nota passada como
 * argumento pode ser usado como nota em uma avaliação ou não.
 *
 * Requisitos:
 *  Nenhum.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidGrade (unsigned int grade) {

  /* As notas de avaliação válida variam de 0 a 5. */

  if(grade <= 5)
    return 1;

  else
    return 0;

}

/**
 * @fn int ValidTransaction (transaction *given_transaction)
 * @brief Função que verifica se uma transação é válida.
 * @param given_transaction Endereço da transação que será testada. Argumento
 * passado por referência.
 * @return A função retorna um inteiro: 1 se a transação é válida; 0 se a
 * transação é inválida.
 *
 * Verifica se uma transação contém os parâmetros usuário 01, usuário 02,
 * produto e estado válidos conforme métricas definidas previamente. Faz-se isso
 * passando-se os parâmetros da transação para a função
 * ValidTransactionArguments.
 *
 * Assertivas de entrada:
 *  -O parâmetro given_transaction deve ser diferente de NULL.
 *  -O parâmetro given_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *
 * Assertivas de saída:
 *  -Os parâmetros da transação no endereço given_transaction permanecerão
 * inalterados.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se a transação cujo endereço
 * foi passado como argumento contém seus membros válidos ou não ou se o
 * argumento fornecido para a função ValidTransaction é inválido.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidTransaction (transaction *given_transaction) {

  if(given_transaction == NULL)
    return -1;

  else if(ValidTransactionArguments(given_transaction->user1,
          given_transaction->user2, &(given_transaction->item),
          given_transaction->status) != 1)
    return 0;

  else
    return 1;

}

/**
 * @fn int ValidTransactionArguments(unsigned int user1, unsigned int user2,
 * product *item, transactionStatus status)
 * @brief Função que verifica se os membros de uma transação são válidos.
 * @param user1 Primeiro usuário de uma transação.
 * @param user2 Segundo usuário de uma transação.
 * @param item Endereço para o produto transacionado em uma transação. Argumento
 * passado por referência.
 * @param status Estado de uma transação.
 * @return A função retorna um inteiro: 1 se os argumentos da função constituem
 * uma transação válida; 0 se os argumentos da função constituem uma transação
 * inválida.
 *
 * Verifica se os argumentos fornecidos para a função constituiriam uma
 * transação válida. Uma transação válida deve: Ter um produto válido, ter ids
 * de usuários diferentes de 0, ter um estado diferente de "Error", não ter ids
 * de usuários iguais para estados diferentes de "Open" e "Canceled", e ter ids
 * de usuários iguais para o estado "Open".
 *
 * Assertivas de entrada:
 *  -O parâmetro item deve ser diferente de NULL.
 *  -O parâmetro item deve apontar para uma estrutura de dados do
 * tipo product.
 *
 * Assertivas de saída:
 *  -Os parâmetros do produto no endereço item permanecerão inalterados.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se os argumentos fornecidos à
 * função constituirião uma transação válida ou não ou se a função recebeu um
 * ponteiro NULL como argumento.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidTransactionArguments(unsigned int user1, unsigned int user2,
                              product *item, transactionStatus status) {

  if(item == NULL)
    return -1;

  /*
    Algums comentários para melhor compreensão do condicional abaixo:
      -Os únicos estados de transação que permitem que os 2 ids de usuários da
      transação sejam iguais são "Open" e "Canceled", pois uma transação cujo
      estado é "Open" aguarda a chegada de um segundo usuário e uma transação
      cujo estado é "Canceled" pode ter sido gerada a partir de uma transação
      cujo estado era "Open".
      -Pela definição de uma transação de estado "Open" feita acima, os 2 ids de
      usuários de uma transação cujo estado é "Open" devem ser necessáriamente
      iguais.
      -O id de usuário 0 está reservado para conter os dados do usuário logado
      no momento, não podendo, portanto, ser o argumento de uma transação.
   */

  else if((ValidProduct(item) != 1) || status == Error
          || (user1 == user2 && (status != Open && status != Canceled))
          || (user1 != user2 && status == Open) || user1 == 0 || user2 == 0)
    return 0;

  else
    return 1;

}
