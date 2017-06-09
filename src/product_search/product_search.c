// Módulo de pesquisa de produtos.

#include "product_search.h"

errorLevel add_product(product *new_product, productList *list) {

  int iterator, size;

  size = list->size;

  if(new_product->price <= 0 || new_product->price >= 1000000 ||
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

errorLevel create_specification(productType type, double min_price,
double max_price, int mim_popularity, int max_popularity,
productSpecification *new_specification) {

  new_specification->type = type;
  new_specification->minimum_price = min_price;
  new_specification->maximum_price = max_price;
  new_specification->minimum_popularity = mim_popularity;
  new_specification->maximum_popularity = max_popularity;

  return Success;

}

errorLevel search_product(char query[75], productList *list, results *matches,
productSpecification *specifics) {

  int iterator;

  matches->size = 0;
  free(matches->indexes);
  matches->indexes = NULL;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(query, list->itens[iterator].name) && (specifics->type == All
    || specifics->type == list->itens[iterator].type)) {

      matches->size++;

      if (matches->size == 1)
        matches->indexes = (unsigned int*) malloc(sizeof(unsigned int));

      else
        matches->indexes = (unsigned int*) realloc(matches->indexes,
        matches->size * sizeof(unsigned int));

      matches->indexes[(matches->size - 1)] = iterator;

    }

  }

  if (matches->size == 0)
    return Failure;

  else
    return Success;

}
