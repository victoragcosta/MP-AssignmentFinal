// Módulo de pesquisa de produtos.

#include "product_search.h"

errorLevel add_product(product *new_product, productList *list) {

  int iterator, size;

  size = list->size;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(new_product->name, list->itens[iterator].name)
      && new_product->type == list->itens[iterator].type
      && new_product->price == list->itens[iterator].price
      && new_product->popularity == list->itens[iterator].popularity)
      return Failure;

  }

  list->size++;
  list->itens = (product*) realloc(list->itens, list->size * sizeof(product));

  strcpy(list->itens[size].name, new_product->name);
  list->itens[size].type = new_product->type;
  list->itens[size].price = new_product->price;
  list->itens[size].popularity = new_product->popularity;

  return Success;

}

int search_product(char query[75], productList *list, results *matches) {

  int iterator;

  matches->size = 0;
  free(matches->indexes);
  matches->indexes = NULL;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(query, list->itens[iterator].name)) {

      matches = NULL;


    }

  }

  if (matches->size == 0)
    return Failure;

  else
    return Success;

}
