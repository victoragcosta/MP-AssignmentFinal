// Módulo de pesquisa de produtos.

#include "product_search.h"

errorLevel add_product(product *new_product, productList *list) {

  int iterator, size;

  size = list->size;

  if(new_product->price <= 0 || new_product->price >= 100000 ||
    new_product->popularity < 0 || new_product->popularity > 100)
      return Illegal_argument;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(new_product->name, list->itens[iterator].name)
      && new_product->type == list->itens[iterator].type
      && new_product->price == list->itens[iterator].price
      && new_product->popularity == list->itens[iterator].popularity)
      return Failure;

  }

  list->size++;

  if (list->size == 1)
    list->itens = (product*) malloc(sizeof(product));

  else
    list->itens = (product*) realloc(list->itens, list->size * sizeof(product));

  strcpy(list->itens[size].name, new_product->name);
  list->itens[size].type = new_product->type;
  list->itens[size].price = new_product->price;
  list->itens[size].popularity = new_product->popularity;

  return Success;

}

errorLevel search_product(char query[75], productList *list, results *matches) {

  int iterator;

  matches->size = 0;
  free(matches->indexes);
  matches->indexes = NULL;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(query, list->itens[iterator].name)) {
      matches->size++;
      matches->indexes = (unsigned int*) realloc(matches->indexes, matches->size *
      sizeof(unsigned int));
      matches->indexes[(matches->size - 1)] = iterator;
    }

  }

  if (matches->size == 0)
    return Failure;

  else
    return Success;

}
