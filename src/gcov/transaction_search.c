// Módulo de busca de transações.

/**
 * @file transaction_search.c
 * @brief Implementação do módulo de busca de transações.
 */

#include "transaction_search.h"

/**
 * @fn errorLevel AddTransaction(transaction *new_transaction,
 * transactionList *list)
 * @brief Função que adiciona uma transação à uma lista de transações.
 * @param new_transaction Endereço da transação a ser adicionada. Argumento
 * passado por referência.
 * @param list Endereço da lista que receberá a transação. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja adicionado à lista com sucesso; Failure caso a transação já
 * exista na lista; Illegal_argument, caso a transação passada como argumento
 * seja inválida ou a função receba um ponteiro nulo como argumento.
 *
 * Adiciona um transação ao vetor do tipo transaction contido no tipo de dados
 * transactionList alocando/realocando o vetor de transações de list para conter
 * uma entrada a mais e copiando os parâmetros de new_transaction para essa nova
 * entrada.
 *
 * Importante: Aloca/Realoca dinamicamente o vetor que contém as transaçãos em
 * list (uma estrutura de dados do tipo transactionList). Tal memória deve ser
 * liberada no término do programa chamando-se a função
 * CleanTransactionList(list) ou por meio da função free(list.items).
 *
 * Assertivas de entrada:
 *  -Ambos new_transaction e list devem ser diferentes de NULL.
 *  -O parâmetro new_transaction deve apontar para uma estrutura de dados do
 * tipo transaction.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -A transação referenciada por new_transaction permanecerá inalterado e
 * estará contida no vetor de transaçãos referenciado por list.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transaçãos possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço new_transaction serão copiadas para uma
 * nova entrada na lista contida no endereço list.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de transações
 * de list.
 *
 */

errorLevel AddTransaction(transaction *given_transaction,
                          transactionList *list) {

  int i, empty_slot;

  if(given_transaction == NULL || list == NULL
     || (ValidTransaction(given_transaction) != 1))
    return Illegal_argument;

  /*
    Percorre-se a lista para verificar-se se a transação já não pertence à lista
    de transações.
   */

  for (i = 0; i < (list->size); ++i)
    if(!CompareTransactions(&(list->items[i]), given_transaction))
      return Failure;

  /*
    Caso a transação passada como argumento contenha campos válidos e ainda não
    pertença à lista, adiciona-se a transação à lista.
   */

  list->size++; /* Aumenta-se o tamanho da lista devido à adição. */

  /*
    Caso a transação adicionada seja a primeira da lista, utiliza-se a função
    malloc para gerar o vetor de transações. Do contrário, utiliza-se a função
    realloc para realocar o vetor de transações.
   */

  if(list->size == 1)
    list->items = (transaction*) malloc(sizeof(transaction));

  else
    list->items = (transaction*) realloc(list->items,
                                         list->size * sizeof(transaction));

  empty_slot = (list->size)-1; /* Posição vaga na lista. */

  CopyTransaction(&(list->items[empty_slot]), given_transaction);

  return Success;

}

/**
 * @fn errorLevel CleanTransactionList (transactionList *list)
 * @brief Função para limpar uma lista de transações.
 * @param list Endereço da lista que será limpa. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * lista seja limpa com sucesso.
 *
 * Limpa uma estrutura de dados do tipo transactionList, desalocando seu vetor
 * de estruturas de dados do tipo transaction e colocando o seu inteiro de
 * tamanho como sendo igual a zero. Recomenda-se chamá-la no início da execução
 * de um programa para preparar a lista para uso e antes do término da execução
 * do programa passando-se como argumento todas as listas de transações usadas.
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -list->size = 0.
 *  -list->items = NULL.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço list serão limpas de forma que list se
 * comporte como uma lista recém inicializada.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CleanTransactionList(transactionList *list) {

  /*
    Para limpar uma lista de transações, atribui-se ao seu tamanho o valor 0 e,
    caso seja necessário, libera-se o vetor de items alocado dinamicamente e
    atribui-se a ele o valor NULL.
   */

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

/**
 * @fn errorLevel DeleteTransaction (int index, transactionList *list)
 * @brief Função que remove uma transação de uma lista de transações.
 * @param index Índice da transação na lista de transações.
 * @param list Endereço da lista que terá a transação removida. Argumento
 * passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja removida da lista com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido ou o endereço da lista passado seja um
 * ponteiro NULL.
 *
 * Remove a transação contida no índice index da estrutura de dados do tipo
 * transactionList referenciada por list. Caso essa seja a única transação da
 * lista, o vetor de transações da lista é liberado com free(). Do contrário,
 * ele é realocado para ter uma posição a menos. Retornará Illegal_argument caso
 * list->size = 0.
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O índice index deve ser um índice válido, considerando-se list->size.
 *
 * Assertivas de saída:
 *  -list->size -= 1.
 *  -A transação que estava no índice index de list->items não pertence mais a
 * list->items.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -A transação contida na posição index do vetor de transações de list será
 * removida do vetor de transações de list.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para realocar o vetor de transações de list.
 *
 */

errorLevel DeleteTransaction (int index, transactionList *list) {

  int i;

  if(list == NULL || !ValidIndex(index, list->size)) {
    return Illegal_argument;
  }

  /*
    Caso a lista contenha apenas 1 item, libera-se o vetor de items e atribui-se
    a ele o valor NULL.
   */

  else if(list->size == 1) {
    free(list->items);
    list->items = NULL;
  }

  /* Caso contrário, o procedimento de deleção é mais complicado. */

  else {

    /*
      Primeiro, vamos "mover" todos os elementos do vetor de transações que
      estão à direita da transação a ser removida uma "posição" para esquerda.
      Atingimos tal resultado sobrescrevendo a transação a ser removida com a
      transação que está a sua direita (o que pode ser feito com a função de
      copiar transações) e repetindo esse procedimento até a penúltima transação
      do vetor de transações.
     */

    for (i = index; i < list->size - 1; ++i)
      CopyTransaction(&(list->items[i]), &(list->items[i + 1]));

    /*
      Por fim, basta realocar a lista para que ela tenha um espaço a menos.
      Como a transação da última posição terá sido copiado para a penúltima
      posição, a transação que será "perdida" com o realocamento do vetor será
      aquela que deveria ser removida.
     */

    list->items = (transaction*) realloc(list->items, (list->size - 1)
                                     * sizeof(transaction));

  }

  /*
    Após uma deleção bem sucedida, deve-se diminuir o tamanho da lista em uma
    unidade.
   */

  (list->size) -= 1;

  return Success;

}

/**
 * @fn errorLevel LoadTransactionList(transactionList *list)
 * @brief Função que carrega a lista de transações do banco de dados de
 * transações.
 * @param list Endereço da lista que receberá as transações. Argumento passado
 * por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso as
 * transações sejam carregadas com sucesso; Failure caso não seja possível
 * acessar o banco de dados das transações; Illegal_argument, caso a função
 * receba um ponteiro nulo como argumento.
 *
 * Abre o banco de dados que guarda as transações do aplicativo
 * (transactions.txt) e carrega suas transações para a lista de transações cujo
 * endereço foi fornecido como argumento da função. Os elementos anteriores que
 * a lista tinha serão sobrescritos. Elementos que gerem erros de leitura, que
 * possuam membros com valores inválidos ou que sejam repetidos não serão
 * carregados. Mudanças feitas no banco de dados de transações devem ser salvas
 * por meio da função SaveTransactionList.
 *
 * Importante: Aloca dinamicamente o vetor que contém as transações em list (uma
 * estrutura de dados do tipo transactionList). Tal memória deve ser liberada no
 * término do programa chamando-se a função CleanTransactionList(list) ou por
 * meio da função free(list.items).
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -Existe um banco de dados de transações contido no endereço TRANSACTION_DB.
 *  -As transações neste banco de dados terão seus campos separados pelo
 * caractere reservado '|'.
 *  -Produtos diferentes no banco de dados serão separados pelo caractere '\n'.
 *
 * Assertivas de saída:
 *  -As transações válidos contidos no banco de dados de transações estarão em
 * list.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo transactionType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações válidas contidos no banco de dados de transações
 * sobrescreverão as transações contidas em list.
 *
 * Requisitos:
 *  -Um banco de dados de transações (arquivo .txt).
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  -As transações neste banco de dados terão seus campos separados pelo
 * caractere reservado '|'.
 *  -Transações diferentes no banco de dados serão separadas pelo caractere
 * '\n'.
 *
 */

errorLevel LoadTransactionList(transactionList *list) {

  FILE *fp;
  transaction new_transaction;
  product item;
  char name[75];
  productType type;
  double price;
  int popularity, auxiliary1, auxiliary2;
  unsigned int user1, user2;
  transactionStatus status;

  if(list == NULL)
    return Illegal_argument;

  /*
    Caso não seja possível abrir o banco de dados para transações, a função
    falha.
   */

  fp = fopen(TRANSACTION_DB, "r");

  if(fp == NULL)
    return Failure;

  /* Limpa-se a lista para eliminar qualquer transação residual. */

  CleanTransactionList(list);

  /*
    Enquanto o arquivo não chegar ao fim, os dados de uma transação são
    carregados em váriaveis intermediárias que serão utilizadas para criar
    primeiramente o transação da transação e depois a transação em si. Note
    que a enumeração productType de cada transação e a enumeração
    transactionStatus de cada transação foram, ambos, gravados como ints, então
    devemos convertê-los para o tipo productType e transactionStatus,
    respectivamente.
   */

  while(fscanf(fp, "%u|%u|%[^|]|%d|%lf|%d|%d\n", &user1, &user2, name,
        &auxiliary1, &price, &popularity, &auxiliary2) != EOF) {

    if(ConvertIntToProductType(auxiliary1, &type) == 0
       && ConvertIntToTransactionStatus(auxiliary2, &status) == 0) {

      if(CreateProduct(name, type, price, popularity, &item) == Success)
        if(CreateTransaction(user1, user2, &item, status, &new_transaction)
           == Success)
          AddTransaction(&new_transaction, list);

    }

  }

  fclose(fp);

  return Success;

}

/**
 * @fn errorLevel OpenTransactions(unsigned int search_author,
 * product *given_product, userRestriction *restriction, transactionList *list,
 * transactionList *matches)
 * @brief Função que realiza a busca por transações de um produto disponíveis.
 * @param given_product Produto procurado. Argumento passado por referência.
 * @param restriction Endereço da restrição de usuários utilizada para busca.
 * Argumento passado por referência.
 * @param list Endereço da lista onde a pesquisa de transações será realizada.
 * Argumento passado por referência.
 * @param matches Endereço da lista de transações onde os resultados serão
 * armazenados. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um produto inválido ou um ponteiro nulo
 * como um dos seus argumentos.
 *
 * Busca em uma lista de transações por transações cujo produto transacionado
 * seja aquele passado como argumento da função e cujos usuários se encaixem na
 * restrição de usuários passada como argumento da função. Copia qualquer
 * transação que se adeque ao cenário anterior à uma segunda lista de
 * transações, passada como argumento da função, para guardar os resultados da
 * busca.
 *
 * Importante: Limpa os dados contidos na estrutura de dados referenciada por
 * matches. Aloca/Realoca dinamicamente o vetor que contém as transações em
 * matches (uma estrutura de dados do tipo transactionList). Tal memória deve
 * ser liberada no término do programa chamando-se a função
 * CleanTransactionList(matches) ou por meio da função free(matches.items).
 *
 * Assertivas de entrada:
 *  -Os parâmetros given_product, restriction, list e matches devem ser
 * diferentes de NULL.
 *  -O parâmetro given_product deve apontar para uma estrutura de dados do tipo
 * product que represente um produto válido.
 *  -O parâmetro restriction deve apontar para uma estrutura de dados do tipo
 * userRestriction.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O parâmetro matches deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -As transações cujo produto transacionado era product, cujos usuários se
 * encaixavam na restrição de usuários referenciada por restriction e que
 * estavam no vetor de transações de list estarão no vetor de transações de
 * matches.
 *  -A estrutura de dados given_product permanecerá inalterada.
 *  -A estrutura de dados restriction permanecerá inalterada.
 *  -A estrutura de dados list permanecerá inalterada.
 *  -Os dados da estrutra de dados matches serão sobrescritos pelos resultados
 * da busca.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados userRestriction possui uma estrutura de dados do
 * tipo relationship para representar a proximidade desejada com o usuário da
 * transação; e dois doubles, um para representar a avaliação mínima desejada do
 * usuário da transação e outro para representar a avaliação máxima desejada do
 * usuário da transação.
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações resultantes da busca feita em list com as restrições
 * fornecidas sobrescreverão as transações contidas no vetor de transações
 * referenciado por matches. O número de items em matches será igual ao número
 * de resultados da busca.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo userRestriction alocada estaticamente.
 *  -Duas estruturas de dados do tipo transactionList alocadas estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de transações
 * de matches.
 *
 */

errorLevel OpenTransactions(
    unsigned int search_author,
    product *given_product,
    userRestriction *restriction,
    transactionList *list,
    transactionList *matches) {

  int i;

  if(restriction == NULL || list == NULL || matches == NULL ||
     given_product == NULL || (ValidProduct(given_product) != 1))
    return Illegal_argument;

  /*
    Deve-se limpar a lista de resultados da busca para evitar qualquer transação
    residual.
   */

  CleanTransactionList(matches);

  for (i = 0; i < (list->size); ++i) {

    if(list->items[i].status == Open
       && !CompareProducts(&(list->items[i].item), given_product)
       && (MatchesRestriction(search_author, list->items[i].user1, restriction)
       == 1)) {

      AddTransaction(&(list->items[i]), matches);

    }

  }

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn errorLevel ProductTransactions(product *given_product,
 * transactionList *list, transactionList *matches)
 * @brief Função que realiza a busca por transações que envolvam um produto.
 * @param given_product Produto procurado. Argumento passado por referência.
 * @param list Endereço da lista onde a pesquisa de transações será realizada.
 * Argumento passado por referência.
 * @param matches Endereço da lista de transações onde os resultados serão
 * armazenados. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um produto inválido ou um ponteiro nulo
 * como um dos seus argumentos.
 *
 * Busca em uma lista de transações por todas as transações cujo produto
 * transacionado seja aquele passado como argumento da função. Copia qualquer
 * transação que se adeque ao cenário anterior à uma segunda lista de
 * transações, passada como argumento da função, para guardar os resultados da
 * busca.
 *
 * Importante: Limpa os dados contidos na estrutura de dados referenciada por
 * matches. Aloca/Realoca dinamicamente o vetor que contém as transações em
 * matches (uma estrutura de dados do tipo transactionList). Tal memória deve
 * ser liberada no término do programa chamando-se a função
 * CleanTransactionList(matches) ou por meio da função free(matches.items).
 *
 * Assertivas de entrada:
 *  -Os parâmetros given_product, list e matches devem ser diferentes de NULL.
 *  -O parâmetro given_product deve apontar para uma estrutura de dados do tipo
 * product que represente um produto válido.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O parâmetro matches deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -As transações cujo produto transacionado era product e que estavam no vetor
 * de transações de list estarão no vetor de transações de matches.
 *  -A estrutura de dados given_product permanecerá inalterada.
 *  -A estrutura de dados list permanecerá inalterada.
 *  -Os dados da estrutra de dados matches serão sobrescritos pelos resultados
 * da busca.
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
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações resultantes da busca feita em list com o produto fornecido
 * sobrescreverão as transações contidas no vetor de transações referenciado por
 * matches. O número de items em matches será igual ao número de resultados da
 * busca.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Duas estruturas de dados do tipo transactionList alocadas estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de transações
 * de matches.
 *
 */

errorLevel ProductTransactions(product *given_product, transactionList *list,
                               transactionList *matches) {

  int i;

  if(given_product == NULL || list == NULL || matches == NULL ||
     (ValidProduct(given_product) != 1))
    return Illegal_argument;

  /*
    Deve-se limpar a lista de resultados da busca para evitar qualquer transação
    residual.
   */

  CleanTransactionList(matches);

  for (i = 0; i < (list->size); ++i)
    if(!CompareProducts(&(list->items[i].item), given_product))
      AddTransaction(&(list->items[i]), matches);

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn errorLevel SaveTransactionList(transactionList *list)
 * @brief Função que salva uma lista de transações no banco de dados de
 * transações.
 * @param list Endereço da lista cujas transações serão salvas. Argumento
 * passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso os
 * transações sejam salvas com sucesso; Failure caso não seja possível acessar
 * o banco de dados das transações; Illegal_argument, caso a função receba um
 * ponteiro nulo como argumento.
 *
 * Abre o banco de dados que guarda as transações do aplicativo
 * (transactions.txt) e salva nele as transações de uma lista de transações cujo
 * endereço foi fornecido como argumento da função, sobrescrevendo as transações
 * contidas nele  anteriormente. Caso o banco de dados de transações não exista
 * no endereço TRANSACTION_DB, ele será criado.
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -As transações de list estarão gravadas no banco de dados de transações.
 *  -As transações gravadas no banco de dados terão seus campos separados pelo
 * caractere reservado '|'.
 *  -As diferentes transações gravadas no banco de dados serão separadas pelo
 * caractere '\n'.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações contidas em list serão gravados no banco de dados de
 * transações sobrescrevendo as transações anteriores, caso existam.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel SaveTransactionList(transactionList *list) {

  FILE *fp;
  int i;

  if(list == NULL)
    return Illegal_argument;

  /*
    Caso não seja possível abrir o banco de dados para transações, a função
    falha.
   */

  fp = fopen(TRANSACTION_DB, "w");

  if(fp == NULL)
    return Failure;

  /*
    Grava-se os dados das transações separando-se os campos de uma mesma
    transação pelo caractere reservado '|' e separando-se transações diferentes
    pelo caractere '\n'. Para gravar-se os dados do transação contido na
    transação, grava-se cada um de seus campos, separando-os, novamente, pelo
    caractere '|'. Note que as enumerações productType e transactionStatus são
    gravadas como ints.
   */

  for (i = 0; i < list->size; i++)
    fprintf(fp, "%u|%u|%s|%d|%lf|%d|%d\n", list->items[i].user1,
            list->items[i].user2, list->items[i].item.name,
            list->items[i].item.type, list->items[i].item.price,
            list->items[i].item.popularity, list->items[i].status);

  fclose(fp);

  return Success;

}

/**
 * @fn errorLevel SelectTransaction(int index, transactionList *list,
 * transaction *selection)
 * @brief Função que seleciona uma transação de uma lista de transações.
 * @param index Índice da transação na lista de transações.
 * @param list Endereço da lista que contém a transação desejada. Argumento
 * passado por referência.
 * @param selection Endereço da estrutura de dados que reberá os parâmetros da
 * transação desejada. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * transação seja selecionado com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido ou seja fornecido um ponteiro NULL como
 * endereço da lista.
 *
 * Seleciona a transação de índice index no vetor de transações de list para
 * copiar suas informações para a transação referenciada por selection.
 *
 * Assertivas de entrada:
 *  -Ambos selection e list devem ser diferentes de NULL.
 *  -O parâmetro selection deve apontar para uma estrutura de dados do tipo
 * transaction.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O índice index deve ser um índice válido, considerando-se list->size.
 *
 * Assertivas de saída:
 *  -A transação referenciada por selection terá suas informações sobrescritas
 * por aquelas da transação contida no índice index do vetor de transações
 * referenciado por list.
 *  -A estrutura de dados list permanecerá inalterada.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -Os membros da transação na posição index do vetor de transações de list
 * serão copiados para a transação referenciado por selection, sobrescrevendo
 * seus membros antigos.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo transaction alocada estaticamente.
 *  -Uma estrutura de dados do tipo transactionList alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel SelectTransaction(int index, transactionList *list,
                             transaction *selection) {

  if(list == NULL || selection == NULL || !ValidIndex(index, list->size))
    return Illegal_argument;

  CopyTransaction(selection, &(list->items[index]));

  return Success;

}

/**
 * @fn errorLevel StatusTransactions(transactionStatus status,
 * transactionList *list, transactionList *matches)
 * @brief Função que realiza a busca por transações que estejam em um certo
 * estado.
 * @param status Estado procurado.
 * @param list Endereço da lista onde a pesquisa de transações será realizada.
 * Argumento passado por referência.
 * @param matches Endereço da lista de transações onde os resultados serão
 * armazenados. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um ponteiro nulo como um dos seus
 * argumentos.
 *
 * Busca em uma lista de transações por todas as transações cujo estado seja
 * aquele passado como argumento da função. Copia qualquer transação que se
 * adeque ao cenário anterior à uma segunda lista de transações, passada como
 * argumento da função, para guardar os resultados da busca.
 *
 * Importante: Limpa os dados contidos na estrutura de dados referenciada por
 * matches. Aloca/Realoca dinamicamente o vetor que contém as transações em
 * matches (uma estrutura de dados do tipo transactionList). Tal memória deve
 * ser liberada no término do programa chamando-se a função
 * CleanTransactionList(matches) ou por meio da função free(matches.items).
 *
 * Assertivas de entrada:
 *  -Os parâmetros list e matches devem ser diferentes de NULL.
 *  -O parâmetro status deve ser diferente de Error.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O parâmetro matches deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -As transações cujo estado era status e que estavam no vetor de transações
 * de list estarão no vetor de transações de matches.
 *  -A estrutura de dados list permanecerá inalterada.
 *  -Os dados da estrutra de dados matches serão sobrescritos pelos resultados
 * da busca.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações resultantes da busca feita em list com o estado fornecido
 * sobrescreverão as transações contidas no vetor de transações referenciado por
 * matches. O número de items em matches será igual ao número de resultados da
 * busca.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo transactionList alocadas estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de transações
 * de matches.
 *
 */

errorLevel StatusTransactions(transactionStatus status, transactionList *list,
                              transactionList *matches) {

  int i;

  if(list == NULL || matches == NULL || status == Error)
    return Illegal_argument;

  /*
    Deve-se limpar a lista de resultados da busca para evitar qualquer transação
    residual.
   */

  CleanTransactionList(matches);

  for (i = 0; i < (list->size); ++i)
    if(status == list->items[i].status)
      AddTransaction(&(list->items[i]), matches);

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn errorLevel UserTransactions(unsigned int user, transactionList *list,
 * transactionList *matches)
 * @brief Função que realiza a busca por transações que envolvam um certo
 * usuário.
 * @param user Usuário procurado.
 * @param list Endereço da lista onde a pesquisa de transações será realizada.
 * Argumento passado por referência.
 * @param matches Endereço da lista de transações onde os resultados serão
 * armazenados. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um ponteiro nulo como um dos seus
 * argumentos.
 *
 * Busca em uma lista de transações por todas as transações que envolvam o id de
 * usuário passado como argumento da função. Copia qualquer transação que se
 * adeque ao cenário anterior à uma segunda lista de transações, passada como
 * argumento da função, para guardar os resultados da busca.
 *
 * Importante: Limpa os dados contidos na estrutura de dados referenciada por
 * matches. Aloca/Realoca dinamicamente o vetor que contém as transações em
 * matches (uma estrutura de dados do tipo transactionList). Tal memória deve
 * ser liberada no término do programa chamando-se a função
 * CleanTransactionList(matches) ou por meio da função free(matches.items).
 *
 * Assertivas de entrada:
 *  -Os parâmetros list e matches devem ser diferentes de NULL.
 *  -O parâmetro user deve ser diferente de 0.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *  -O parâmetro matches deve apontar para uma estrutura de dados do tipo
 * transactionList.
 *
 * Assertivas de saída:
 *  -As transações que envolviam o id de usuário user e que estavam no vetor de
 * transações de list estarão no vetor de transações de matches.
 *  -A estrutura de dados list permanecerá inalterada.
 *  -Os dados da estrutra de dados matches serão sobrescritos pelos resultados
 * da busca.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados transaction possui como membros um unsigned int para
 * o primeiro usuário envolvido na transação, um unsigned int para o segundo
 * usuário envolvido na transação, uma estrutura de dados do tipo product para o
 * produto que está sendo transacionado e uma estrutura de dados do tipo
 * transactionStatus para seu estado.
 *  -Uma estrutura de dados transactionList possui um int para representar
 * quantas transações possui e um vetor de transações que armazena as transações
 * em si.
 *
 * Assertivas de contrato:
 *  -As transações resultantes da busca feita em list com o id de usuário
 * fornecido sobrescreverão as transações contidas no vetor de transações
 * referenciado por matches. O número de items em matches será igual ao número
 * de resultados da busca.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo transactionList alocadas estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de transações
 * de matches.
 *
 */

errorLevel UserTransactions(unsigned int user, transactionList *list,
                            transactionList *matches) {

  int i;

  if(list == NULL || matches == NULL || user == 0)
    return Illegal_argument;

  /*
    Deve-se limpar a lista de resultados da busca para evitar qualquer transação
    residual.
   */

  CleanTransactionList(matches);

  for (i = 0; i < (list->size); ++i)
    if(user == list->items[i].user1 || user == list->items[i].user2)
      AddTransaction(&(list->items[i]), matches);

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn int MatchesRestriction(unsigned int original_user, unsigned int
 * given_user, userRestriction *restriction)
 * @brief Função que verifica se um usuário se adequa a uma restrição de
 * usuário.
 * @param original_user Usuário que criou a restrição.
 * @param given_user Usuário que será analizado.
 * @param restriction Endereço da restrição contra qual o usuário given_user é
 * analizado. Argumento passado por referência.
 * @return A função retorna um inteiro: 1 se o usuário given_user se adequa à
 * restrição; 0 se o usuário given_user não se adequa à restrição.
 *
 * Verifica se a avaliação do usuário given_user e a sua proximidade com o
 * usuário original_user se adequam à restrição de usuários fornecida como
 * argumento da função.
 *
 * Assertivas de entrada:
 *  -O parâmetro restriction deve ser diferente de NULL.
 *  -Ambos os parâmetros original_user e given_user devem ser diferentes de 0.
 *  -O parâmetro restriction deve apontar para uma estrutura de dados do tipo
 * userRestriction.
 *
 * Assertivas de saída:
 *  -A estrutura de dados restriction permanecerá inalterada.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados userRestriction possui uma estrutura de dados do
 * tipo relationship para representar a proximidade desejada com o usuário da
 * transação; e dois doubles, um para representar a avaliação mínima desejada do
 * usuário da transação e outro para representar a avaliação máxima desejada do
 * usuário da transação.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se os argumentos utilizados são
 * válidos e se o usuário given_user, passado como argumento, se adequa à
 * restrição de usuário feita pelo usuário original_user e passada como
 * argumento da função.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo userRestriction alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int MatchesRestriction(unsigned int original_user, unsigned int given_user,
                       userRestriction *restriction) {

  double rating;
  int result = 0;
  unsigned int i;
  usuarios_uintarray friends, friends_of_friends;
  relationship proximity;

  /*
    Caso argumentos passados para a função sejam inválidos ou não seja possível
    carregar as avaliações de cada usuário, a função retorna -1. Note que o id
    de usuário 0 está reservado para o usuário da sessão, sendo, assim, um
    argumento ilegal.
   */

  if(restriction == NULL || original_user == 0 || given_user == 0
     || (usuarios_retornaDados(given_user, "avaliacao", &rating)
     != USUARIOS_SUCESSO)) {
    return -1;
  }

  /*
    Caso a avaliação do usuário não se adeque às restrições, a função retorna 0.
    Do contrário, devemos avaliar se a proximidade dos usuários é compatível com
    a restrição imposta.
   */

  else if(rating > restriction->maximum_rating
          || rating < restriction->minimum_rating) {
    return 0;
  }

  else {

    /*
      A restrição de proximidade "Other" aceita qualquer usuário. Como já
      checamos a avaliação do usuário inspecionado, então podemos concluir que
      ele se encaixa na restrição.
     */

    if(restriction->proximity == Other){
      return 1;
    }

    /*
        Caso a restrição de proximidade seja diferente de "Other", devemos
      analisar as lista de amigos e de amigos de amigos do usuário inspecionado.
      Caso não seja possível carregar as listas de amigos e de amigos de amigos
      do usuário inspecionado, a função retornará -1.
        Note que as listas poderiam ter sido carregadas no início da função,
      mas, tendo-se em vista que carregar as referidas listas é um processo
      custoso em relação aos outros processos da função, a função foi
      estruturada de forma a evitar esse processo sempre que possível.
        Note também que, a partir deste ponto, deveremos liberar as listas de
      amigos e de amigos de amigos do usuário inspecionado independentemente do
      resultado da função. Portanto, optou-se por armazenar o resultado da
      função em uma variável intermediária "result" e, ao final da função,
      liberar as referidas listas e retornar "result" para evitar a repetição
      do código de liberação das listas.
     */

    else if((usuarios_listarAmigos(given_user, &friends) != USUARIOS_SUCESSO)
            || (usuarios_listarAmigosdeAmigos(given_user, &friends_of_friends)
            != USUARIOS_SUCESSO)) {
      result = -1;
    }


    else {

      /* Inicialmente, considera-se o usuário inspecionado um estranho. */

      proximity = Other;

      for(i = 0; i < friends.length; i++)
        if(friends.array[i] == original_user)
          proximity = Friend;

      /*
        Caso o usuário inspecionado seja amigo do usuário original, ele
        adequa-se tanto à restrição de proximidade "Friend" quanto à restrição
        de proximidade "FriendOfFriend".
       */

      if((restriction->proximity == Friend
         || restriction->proximity == FriendOfFriend) && proximity == Friend) {
        result = 1;
      }

      for(i = 0; i < friends_of_friends.length; i++)
        if(friends_of_friends.array[i] == original_user)
          proximity = FriendOfFriend;

      /*
        Caso o usuário inspecionado seja amigo de um amigo do usuário original,
        ele adequa-se apenas à restrição de proximidade "FriendOfFriend".
       */

      if(restriction->proximity == FriendOfFriend
         && proximity == FriendOfFriend) {
        result = 1;
      }

    }

    usuarios_freeUint(&friends);
    usuarios_freeUint(&friends_of_friends);
    return result;

  }

}
