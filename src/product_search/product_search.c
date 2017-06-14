// Módulo de pesquisa de produtos.

/**

  \file
  \brief Arquivo que contém as funções relativas ao módulo de busca de produtos
  do aplicativo.

*/

#include "product_search.h"

/** Função que adiciona um produto à uma lista de produtos.

    \param new_product Endereço do produto a ser adicionado.
    \param list Endereço da lista que receberá o produto.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja adicionado à lista com sucesso; Failure caso o produto já
    exista na lista; Illegal_argument, caso os parâmetros de produto passados
    sejam inválidos.

    */

errorLevel AddProduct(product *new_product, productList *list) {

  int i, size;

  size = list->size;

  if(new_product->price <= 0 || new_product->price >= 1000000
     || new_product->popularity < 0 || new_product->popularity > 100)
      return Illegal_argument;

  for (i = 0; i < (list->size); ++i) {

    if(!strcmp(new_product->name, list->items[i].name)
       && new_product->type == list->items[i].type
       && new_product->price == list->items[i].price
       && new_product->popularity == list->items[i].popularity)
      return Failure;

  }

  list->size++;

  if(list->size == 1)
    list->items = (product*) malloc(sizeof(product));

  else
    list->items = (product*) realloc(list->items, list->size * sizeof(product));

  strcpy(list->items[size].name, new_product->name);
  list->items[size].type = new_product->type;
  list->items[size].price = new_product->price;
  list->items[size].popularity = new_product->popularity;

  return Success;

}

/** Função para limpar uma lista de produtos.

    \param list Endereço da lista que será limpa.
    \return A função retorna uma instância do tipo errorLevel: Success caso a
    lista seja limpa com sucesso.

    */

errorLevel CleanProductList (productList *list) {

  list->size = 0;

  if(list->items != NULL) {
    free(list->items);
    list->items = NULL;
  }

  return Success;

}

/** Função que cria uma especificação de busca.

    \param type Tipo do produto a ser procurado.
    \param min_price Preço mínimo do produto a ser procurado.
    \param max_price Preço máximo do produto a ser procurado.
    \param min_popularity Popularidade mínima do produto a ser procurado.
    \param max_popularity Popularidade máxima do produto a ser procurado.
    \param new_specification Endereço da estrutura de dados onde a especificação
    será criada.
    \return A função retorna uma instância do tipo errorLevel: Success caso a
    especificação seja criada com sucesso.

    */

errorLevel CreateSpecification(
    productType type,
    double min_price,
    double max_price,
    int min_popularity,
    int max_popularity,
    productSpecification *new_specification) {

  new_specification->type = type;
  new_specification->minimum_price = min_price;
  new_specification->maximum_price = max_price;
  new_specification->minimum_popularity = min_popularity;
  new_specification->maximum_popularity = max_popularity;

  return Success;

}

/** Função que remove um produto de uma lista de produtos.

    \param index Índice do produto na lista de produtos.
    \param list Endereço da lista que terá o produto removido.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja removido da lista com sucesso; Illegal_argument, caso o índice
    passado como argumento seja inválido.

    */

errorLevel DeleteProduct (int index, productList *list) {

  int i;

  if(index < 0 || index >= list->size) {
    return Illegal_argument;
  }

  else if(list->size == 1) {
    free(list->items);
    list->items = NULL;
  }

  else {

    for (i = index; i < list->size - 1; ++i)
      CopyProduct(&(list->items[i]), &(list->items[i + 1]));

    list->items = (product*) realloc(list->items, (list->size - 1)
                                     * sizeof(product));

  }

  list->size = list->size - 1;

  return Success;

}

/** Função para iniciar uma lista de produtos.

    \param list Endereço da lista que será incializada.
    \return A função retorna uma instância do tipo errorLevel: Success caso a
    lista seja inicializada com sucesso.

    */

errorLevel InitializeProductList (productList *list) {

  list->size = 0;
  list->items = NULL;

  return Success;

}

/** Função que realiza a busca por um produto.

    \param query Nome ou parte de nome dos produtos procurados.
    \param list Endereço da lista onde a pesquisa de produtos será realizada.
    \param matches Endereço da lista de produtos onde os resultados serão
    armazenados.
    \param specifics Endereço da especificação de busca utilizada para busca.
    \return A função retorna uma instância do tipo errorLevel: Success caso a
    busca retorne algum resultado; Failure caso a busca não retorne resultados.

    */

errorLevel SearchProduct(char query[75], productList *list,
                          productSpecification *specifics,
                          productList *matches) {

  int i;

  CleanProductList(matches);

  for (i = 0; i < (list->size); ++i) {

    if((strstr(list->items[i].name, query) != NULL)
      && (specifics->type == All
      || specifics->type == list->items[i].type)
      && (list->items[i].price >= specifics->minimum_price
      && list->items[i].price <= specifics->maximum_price)
      && (list->items[i].popularity >= specifics->minimum_popularity
      && list->items[i].popularity <= specifics->maximum_popularity)) {

      matches->size++;

      if(matches->size == 1)
        matches->items = (product*) malloc(sizeof(product));

      else
        matches->items = (product*) realloc(matches->items,
        matches->size * sizeof(product));

      CopyProduct(&(matches->items[(matches->size - 1)]),
                  &(list->items[i]));

    }

  }

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/** Função que seleciona um produto de uma lista de produtos.

    \param index Índice do produto na lista de produtos.
    \param list Endereço da lista que contém o produto desejado.
    \param selection Endereço da estrutura de dados que reberá os parâmetros do
    produto desejado.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja selecionado com sucesso; Illegal_argument, caso o índice
    passado como argumento seja inválido.

    */

errorLevel SelectProduct(int index, productList *list, product *selection) {

  if(index >= list->size || index < 0)
    return Illegal_argument;

  CopyProduct(selection, &(list->items[index]));

  return Success;

}
