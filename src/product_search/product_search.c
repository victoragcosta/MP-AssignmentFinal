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

errorLevel add_product(product *new_product, productList *list) {

  int iterator, size;

  size = list->size;

  if(new_product->price <= 0 || new_product->price >= 1000000 ||
    new_product->popularity < 0 || new_product->popularity > 100)
      return Illegal_argument;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(new_product->name, list->items[iterator].name)
      && new_product->type == list->items[iterator].type
      && new_product->price == list->items[iterator].price
      && new_product->popularity == list->items[iterator].popularity)
      return Failure;

  }

  list->size++;

  if (list->size == 1)
    list->items = (product*) malloc(sizeof(product));

  else
    list->items = (product*) realloc(list->items, list->size * sizeof(product));

  strcpy(list->items[size].name, new_product->name);
  list->items[size].type = new_product->type;
  list->items[size].price = new_product->price;
  list->items[size].popularity = new_product->popularity;

  return Success;

}

/** Função que copia um produto.

    \param copy Endereço do produto que receberá as especificações copiadas.
    \param original Endereço do produto que será copiado.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja copiado com sucesso.

    */

errorLevel copy_product(product *copy, product *original) {

  strcpy(copy->name, original->name);
  copy->type = original->type;
  copy->price = original->price;
  copy->popularity = original->popularity;

  return Success;

}

/** Função que cria um produto.

    \param name Nome do produto a ser criado.
    \param type Tipo do produto a ser criado.
    \param price Preço do produto a ser criado.
    \param popularity Popularidade do produto a ser criado.
    \param new_product Endereço da estrutura de dados onde o produto será
    criado.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja criado com sucesso; Illegal_argument caso os parâmetros
    passados para a criação do produto sejam inválidos.

    */

errorLevel create_product(char name[75], productType type, double price,
int popularity, product *new_product) {

  if(price <= 0 || price >= 1000000 || popularity < 0 || popularity > 100)
      return Illegal_argument;

  strcpy(new_product->name, name);
  new_product->type = type;
  new_product->price = price;
  new_product->popularity = popularity;

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

errorLevel create_specification(productType type, double min_price,
double max_price, int min_popularity, int max_popularity,
productSpecification *new_specification) {

  new_specification->type = type;
  new_specification->minimum_price = min_price;
  new_specification->maximum_price = max_price;
  new_specification->minimum_popularity = min_popularity;
  new_specification->maximum_popularity = max_popularity;

  return Success;

}

errorLevel delete_product (int index, productList *list) {

  int iterator;

  if (index < 0 || index >= list->size)
    return Illegal_argument;

  else if (list->size == 1)
    free(list->items);

  else {

    for (iterator = index; iterator < list->size - 1; iterator++)
      copy_product(&(list->items[iterator]), &(list->items[iterator + 1]));

    list->items = (product*) realloc(list->items, (list->size - 1)
    * sizeof(product));

  }

  list->size = list->size - 1;

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

errorLevel search_product(char query[75], productList *list, productList *matches,
productSpecification *specifics) {

  int iterator;

  matches->size = 0;

  if (matches->items != NULL) {
    free(matches->items);
    matches->items = NULL;
  }

  for (iterator = 0; iterator < (list->size); iterator++) {

    if((strstr(list->items[iterator].name, query) != NULL)
      && (specifics->type == All
      || specifics->type == list->items[iterator].type)
      && (list->items[iterator].price >= specifics->minimum_price
      && list->items[iterator].price <= specifics->maximum_price)
      && (list->items[iterator].popularity >= specifics->minimum_popularity
      && list->items[iterator].popularity <= specifics->maximum_popularity)) {

      matches->size++;

      if (matches->size == 1)
        matches->items = (product*) malloc(sizeof(product));

      else
        matches->items = (product*) realloc(matches->items,
        matches->size * sizeof(product));

      copy_product(&(matches->items[(matches->size - 1)]),
      &(list->items[iterator]));

    }

  }

  if (matches->size == 0)
    return Failure;

  else
    return Success;

}

errorLevel select_product(int index, productList *list, product *selection) {

  if (index >= list->size || index < 0)
    return Illegal_argument;

  copy_product(selection, &(list->items[index]));

  return Success;

}

/** Função que compara dois produtos.

    \param first Endereço do primeiro produto que faz parte da comparação.
    \param second Endereço do segundo produto que faz parte da comparação.
    \return A função retorna 0 caso os produtos sejam iguais e 1 caso sejam
    diferentes.

    */

int compare_products(product *first, product *second) {

  if(!strcmp(first->name, second->name) && first->type == second->type
  && first->price == second->price &&first->popularity == second->popularity)
    return 0;

  else
    return 1;

}
