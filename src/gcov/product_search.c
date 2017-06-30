// Módulo de pesquisa de produtos.

/**
 * @file product_search.c
 * @brief Implementação do módulo de pesquisa de produtos.
 */

#include "product_search.h"

/**
 * @fn errorLevel AddProduct(product *new_product, productList *list)
 * @brief Função que adiciona um produto à uma lista de produtos.
 * @param new_product Endereço do produto a ser adicionado. Argumento passado
 * por referência.
 * @param list Endereço da lista que receberá o produto. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja adicionado à lista com sucesso; Failure caso o produto já
 * exista na lista; Illegal_argument, caso os parâmetros de produto passados
 * sejam inválidos ou a função receba um ponteiro nulo como parâmetro.
 *
 * Adiciona um produto ao vetor do tipo product contido no tipo de dados
 * productList alocando/realocando o vetor de produtos de list para conter uma
 * entrada a mais e copiando os parâmetros de new_product para essa nova
 * entrada.
 *
 * Importante: Aloca/Realoca dinamicamente o vetor que contém os produtos em
 * list (uma estrutura de dados do tipo productList). Tal memória deve ser
 * liberada no término do programa chamando-se a função CleanProductList(list)
 * ou por meio da função free(list.items).
 *
 * Assertivas de entrada:
 *  -Ambos new_product e list devem ser diferentes de NULL.
 *  -O parâmetro new_product deve apontar para uma estrutura de dados do tipo
 * product.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * productList.
 *
 * Assertivas de saída:
 *  -O produto referenciado por new_product permanecerá inalterado e estará
 * contido no vetor de produtos referenciada por list.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados productList possui um int para representar quantos
 * produtos possui e um vetor de produtos que armazena os produtos em si.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço new_product serão copiadas para uma
 * nova entrada na lista contida no endereço list.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo productList alocada estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de produtos de
 * list.
 *
 */

errorLevel AddProduct(product *new_product, productList *list) {

  int i, empty_slot;

  if(new_product == NULL || list == NULL || (ValidProduct(new_product) != 1))
      return Illegal_argument;

  /*
    Percorre-se a lista para verificar-se se o produto já não pertence à lista
    de produtos.
   */

  for (i = 0; i < (list->size); ++i)
    if(!CompareProducts(&(list->items[i]), new_product))
      return Failure;

  /*
    Caso o produto passado como argumento contenha campos válidos e ainda não
    pertença à lista, adiciona-se o produto à lista.
   */

  list->size++; /* Aumenta-se o tamanho da lista devido à adição. */

  /*
    Caso o produto adicionado seja o primeiro da lista, utiliza-se a função
    malloc para gerar o vetor de produtos. Do contrário, utiliza-se a função
    realloc para realocar o vetor de produtos.
   */

  if(list->size == 1)
    list->items = (product*) malloc(sizeof(product));

  else
    list->items = (product*) realloc(list->items, list->size * sizeof(product));

  empty_slot = (list->size)-1; /* Posição vaga na lista. */

  CopyProduct(&(list->items[empty_slot]), new_product);

  return Success;

}

/**
 * @fn errorLevel CleanProductList (productList *list)
 * @brief Função para limpar uma lista de produtos.
 * @param list Endereço da lista que será limpa. Argumento passado por
 * referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * lista seja limpa com sucesso.
 *
 * Limpa uma estrutura de dados do tipo productList, desalocando seu vetor de
 * estruturas de dados do tipo products e colocando o seu inteiro de tamanho
 * como sendo igual a zero. Recomenda-se chama-la no início da execução de um
 * programa para preparar a lista para uso e antes do término da execução do
 * programa passando-se como argumento todas as listas de produtos usadas.
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * productList.
 *
 * Assertivas de saída:
 *  -list->size = 0.
 *  -list->items = NULL.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados productList possui um int para representar quantos
 * produtos possui e um vetor de produtos que armazena os produtos em si.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço list serão limpas de forma que list se
 * comporte como uma lista recém inicializada.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo productList alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CleanProductList (productList *list) {

  /*
    Para limpar uma lista de produtos, atribui-se ao seu tamanho o valor 0 e,
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

/**
 * @fn errorLevel CreateSpecification(productType type, double min_price,
 * double max_price, int min_popularity, int max_popularity,
 * productSpecification *new_specification)
 * @brief Função que cria uma especificação de busca.
 * @param type Tipo do produto a ser procurado.
 * @param min_price Preço mínimo do produto a ser procurado.
 * @param max_price Preço máximo do produto a ser procurado.
 * @param min_popularity Popularidade mínima do produto a ser procurado.
 * @param max_popularity Popularidade máxima do produto a ser procurado.
 * @param new_specification Endereço da estrutura de dados onde a especificação
 * será criada. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * especificação seja criada com sucesso; Illegal_argument caso a função receba
 * um ponteiro nulo como parâmetro.
 *
 * Copia os parâmetros fornecidos na função para o endereço da estrutura de
 * dados do tipo productSpecification fornecida como parâmetro.
 *
 * Assertivas de entrada:
 *  -O parâmetro new_specification deve ser diferente de NULL.
 *  -O parâmetro new_specification deve apontar para uma estrutura de dados do
 * tipo productSpecification.
 *
 * Assertivas de saída:
 *  -Os membros da especificação no endereço new_specification serão aqueles
 * passados como parâmetros para a função.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados productSpecification possui uma estrutura de dados
 * do tipo productType para representar os tipos de produto desejados; dois
 * doubles, um para representar o preço mínimo dos produtos desejados e outro
 * para representar o preço máximo dos produtos desejados; e dois inteiros, um
 * para representar a popularidade mínima dos produtos desejado e outro para
 * representar a popularidade máxima dos produtos desejados.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço new_specification serão sobrescritas
 * com aquelas fornecidas como parâmetros da função.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo productSpecification alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CreateSpecification(
    productType type,
    double min_price,
    double max_price,
    int min_popularity,
    int max_popularity,
    productSpecification *new_specification) {

  if(new_specification == NULL)
    return Illegal_argument;

  new_specification->type = type;
  new_specification->minimum_price = min_price;
  new_specification->maximum_price = max_price;
  new_specification->minimum_popularity = min_popularity;
  new_specification->maximum_popularity = max_popularity;

  return Success;

}

/**
 * @fn errorLevel DeleteProduct (int index, productList *list)
 * @brief Função que remove um produto de uma lista de produtos.
 * @param index Índice do produto na lista de produtos.
 * @param list Endereço da lista que terá o produto removido. Argumento passado
 * por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja removido da lista com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido.
 *
 * Remove o produto contido no índice index da estrutura de dados do tipo
 * productList referenciada por list. Caso esse seja o único produto da lista,
 * o vetor de produtos da lista é liberado com free(). Do contrário, ele é
 * realocado para ter uma posição a menos. Retornará Illegal_argument caso
 * list->size = 0.
 *
 * Assertivas de entrada:
 *  -O parâmetro list deve ser diferente de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * productList.
 *  -O índice index deve ser um índice válido, considerando-se list->size.
 *
 * Assertivas de saída:
 *  -list->size -= 1.
 *  -O produto que estava no índice index de list->items não pertence mais a
 * list->items.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados productList possui um int para representar quantos
 * produtos possui e um vetor de produtos que armazena os produtos em si.
 *
 * Assertivas de contrato:
 *  -O produto contido na posição index do vetor de produtos de list será
 * removido do vetor de produtos de list.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo productList alocada estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para realocar o vetor de produtos de list.
 *
 */

errorLevel DeleteProduct (int index, productList *list) {

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
      Primeiro, vamos "mover" todos os elementos do vetor de produtos que estão
      à direita do produto a ser removido uma "posição" para esquerda.
      Atingimos tal resultado sobrescrevendo o produto a ser removido com o
      produto que está a sua direita (o que pode ser feito com a função de
      copiar produtos) e repetindo esse procedimento até o penúltimo produto do
      vetor de produtos.
     */

    for (i = index; i < list->size - 1; ++i)
      CopyProduct(&(list->items[i]), &(list->items[i + 1]));

      /*
        Por fim, basta realocar a lista para que ela tenha um espaço a menos.
        Como o produto da última posição terá sido copiado para a penúltima
        posição, o produto que será "perdido" com o realocamento do vetor será
        aquele que deveria ser removido.
       */

    list->items = (product*) realloc(list->items, (list->size - 1)
                                     * sizeof(product));

  }

  /*
    Após uma deleção bem sucedida, deve-se diminuir o tamanho da lista em uma
    unidade.
   */

  (list->size) -= 1;

  return Success;

}

errorLevel LoadProductList(productList *list) {

  FILE *fp;
  product item;
  char name[75];
  productType type;
  double price;
  int popularity, auxiliary;

  if(list == NULL)
    return Illegal_argument;

  fp = fopen(PRODUCT_DB, "r");

  if(fp == NULL)
    return Failure;

  CleanProductList(list);

  while(fscanf(fp, "%[^|]|%d|%lf|%d\n", name, &auxiliary, &price, &popularity)
        != EOF) {

    if (ConvertIntToProductType(auxiliary, &type) == 0) {

      CreateProduct(name, type, price, popularity, &item);
      AddProduct(&item, list);

    }

  }

  fclose(fp);

  return Success;

}

errorLevel SaveProductList(productList *list) {

  FILE *fp;
  int i;

  if(list == NULL)
    return Illegal_argument;

  fp = fopen(PRODUCT_DB, "w");

  if(fp == NULL)
    return Failure;

  for (i = 0; i < list->size; i++)
    fprintf(fp, "%s|%d|%lf|%d\n", list->items[i].name, list->items[i].type,
            list->items[i].price, list->items[i].popularity);

  fclose(fp);

  return Success;

}

/**
 * @fn errorLevel SearchProduct(char query[75], productList *list,
 * productSpecification *specifics, productList *matches)
 * @brief Função que realiza a busca por um produto.
 * @param query Nome ou parte de nome dos produtos procurados.
 * @param list Endereço da lista onde a pesquisa de produtos será realizada.
 * Argumento passado por referência.
 * @param specifics Endereço da especificação de busca utilizada para busca.
 * Argumento passado por referência.
 * @param matches Endereço da lista de produtos onde os resultados serão
 * armazenados. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um ponteiro nulo como parâmetro.
 *
 * Busca por produtos no vetor de produtos de uma lista de produtos cujo nome
 * contenha o trecho buscado passado como parâmetro da função e cujas
 * especificações se adequem à especificação de produtos passada como parâmetro
 * da função. Copia qualquer produto que se adeque ao cenário anterior à uma
 * segunda lista de produtos passada como parâmetro da função para guardar os
 * resultados da busca.
 *
 * Importante: Limpa os dados contidos na estrutura de dados referenciada por
 * matches. Aloca/Realoca dinamicamente o vetor que contém os produtos em
 * matches (uma estrutura de dados do tipo productList). Tal memória deve ser
 * liberada no término do programa chamando-se a função
 * CleanProductList(matches) ou por meio da função free(matches.items).
 *
 * Assertivas de entrada:
 *  -Os parâmetros list, specifics e matches devem ser diferentes de NULL.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * productList.
 *  -O parâmetro specifics deve apontar para uma estrutura de dados do tipo
 * productSpecification.
 *  -O parâmetro matches deve apontar para uma estrutura de dados do tipo
 * productList.
 *
 * Assertivas de saída:
 *  -Os produtos cujo nome continha ou se igualava à query, que se adequavam à
 * especificação referenciada por specifics e que estavam no vetor de produtos
 * de list estarão no vetor de produtos de matches.
 *  -A estrutura de dados list permanecerá inalterada.
 *  -Os dados da estrutra de dados matches serão sobrescritos pelos resultados
 * da busca.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados productSpecification possui uma estrutura de dados
 * do tipo productType para representar os tipos de produto desejados; dois
 * doubles, um para representar o preço mínimo dos produtos desejados e outro
 * para representar o preço máximo dos produtos desejados; e dois inteiros, um
 * para representar a popularidade mínima dos produtos desejado e outro para
 * representar a popularidade máxima dos produtos desejados.
 *  -Uma estrutura de dados productList possui um int para representar quantos
 * produtos possui e um vetor de produtos que armazena os produtos em si.
 *
 * Assertivas de contrato:
 *  -Os produtos resultantes da busca feita em list com as especificações
 * fornecidas sobrescreverão os produtos contidos no vetor de produtos
 * referenciado por matches. O número de items em matches será igual ao número
 * de resultados da busca.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo productSpecification alocada estaticamente.
 *  -Duas estruturas de dados do tipo productList alocadas estaticamente.
 *
 * Hipóteses:
 *  -Sempre haverá espaço na heap para alocar ou realocar o vetor de produtos de
 * matches.
 *
 */

errorLevel SearchProduct(char query[75], productList *list,
                          productSpecification *specifics,
                          productList *matches) {

  int i;

  if(specifics == NULL || list == NULL || matches == NULL)
    return Illegal_argument;

  /*
    Deve-se limpar a lista de resultados da busca para evitar qualquer falso
    positivo.
   */

  CleanProductList(matches);

  /*
    Varre-se a lista de produtos procurando-se produtos cujo nome contenha a
    chave de busca e cujas características sejam permitidas pela especificação
    de busca. Caso encontre-se um produto que se encaixe nessa situação, ele
    é adicionado à lista de resultados.
   */

  for (i = 0; i < (list->size); ++i) {

    if((strstr(list->items[i].name, query) != NULL)
      && (MatchesSpecification(&(list->items[i]), specifics) == 1)) {

      AddProduct(&(list->items[i]), matches);

    }

  }

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn errorLevel SelectProduct(int index, productList *list,
 * product *selection)
 * @brief Função que seleciona um produto de uma lista de produtos.
 * @param index Índice do produto na lista de produtos.
 * @param list Endereço da lista que contém o produto desejado. Argumento
 * passado por referência.
 * @param selection Endereço da estrutura de dados que reberá os parâmetros do
 * produto desejado. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja selecionado com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido ou seja fornecido um ponteiro nulo como
 * parâmetro.
 *
 * Seleciona o produto de índice index no vetor de produtos de list para copiar
 * suas informações para o produto referenciado por selection.
 *
 * Assertivas de entrada:
 *  -Ambos selection e list devem ser diferentes de NULL.
 *  -O parâmetro selection deve apontar para uma estrutura de dados do tipo
 * product.
 *  -O parâmetro list deve apontar para uma estrutura de dados do tipo
 * productList.
 *  -O índice index deve ser um índice válido, considerando-se list->size.
 *
 * Assertivas de saída:
 *  -O produto referenciado por selection terá suas informações sobrescritas por
 * aquelas do produto contido no índice index do vetor de produtos referenciada
 * por list.
 *  -A estrutura de dados list permanecerá inalterada.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados productList possui um int para representar quantos
 * produtos possui e um vetor de produtos que armazena os produtos em si.
 *
 * Assertivas de contrato:
 *  -Os membros do produto na posição index do vetor de produtos de list serão
 * copiados para o produto referenciado por selection, sobrescrevendo seus
 * membros antigos.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo productList alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel SelectProduct(int index, productList *list, product *selection) {

  if(list == NULL || selection == NULL || !ValidIndex(index, list->size))
    return Illegal_argument;

  CopyProduct(selection, &(list->items[index]));

  return Success;

}

/**
 * @fn MatchesSpecification(product *item, productSpecification *specification)
 * @brief Função que verifica se um produto se adequa a uma especificação.
 * @param item Endereço do produto a ser testado. Argumento passado por
 * referência.
 * @param specification Endereço da especificação na qual o produto é testado.
 * Argumento passado por referência.
 * @return A função retorna um inteiro: 1 se o produto se adequa à
 * especificação; 0 se o produto não se adequa à especificação.
 *
 * Verifica se os membros type, price e popularity de um produto fornecido como
 * parâmetro da função se adequam à especificação fornecida como parâmetro da
 * função.
 *
 * Assertivas de entrada:
 *  -Ambos item e specification devem ser diferentes de NULL.
 *  -O parâmetro item deve apontar para uma estrutura de dados do tipo product.
 *  -O parâmetro specification deve apontar para uma estrutura de dados do tipo
 * productSpecification.
 *
 * Assertivas de saída:
 *  -A estrutura de dados item permanecerá inalterada.
 *  -A estrutura de dados specification permanecerá inalterada.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *  -Uma estrutura de dados productSpecification possui uma estrutura de dados
 * do tipo productType para representar os tipos de produto desejados; dois
 * doubles, um para representar o preço mínimo dos produtos desejados e outro
 * para representar o preço máximo dos produtos desejados; e dois inteiros, um
 * para representar a popularidade mínima dos produtos desejado e outro para
 * representar a popularidade máxima dos produtos desejados.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se os parâmetros utilizados são
 * válidos e se o produto passado como parâmetro se adequa à especificação
 * passada como parâmetro.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *  -Uma estrutura de dados do tipo productSpecification alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int MatchesSpecification(product *item, productSpecification *specification) {

  if(item == NULL || specification == NULL)
    return -1;

  else if((specification->type == All || specification->type == item->type)
          && (item->price >= specification->minimum_price
          && item->price <= specification->maximum_price)
          && (item->popularity >= specification->minimum_popularity
          && item->popularity <= specification->maximum_popularity))
    return 1;

  else
    return 0;

}
