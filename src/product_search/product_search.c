// Módulo de pesquisa de produtos.

#include "product_search.h"

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

errorLevel copy_product(product *copy, product *original) {

  strcpy(copy->name, original->name);
  copy->type = original->type;
  copy->price = original->price;
  copy->popularity = original->popularity;

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
  free(matches->items);
  matches->items = NULL;

  for (iterator = 0; iterator < (list->size); iterator++) {

    if(!strcmp(query, list->items[iterator].name) && (specifics->type == All
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

int compare_products(product *first, product *second) {

  if(!strcmp(first->name, second->name) && first->type == second->type
  && first->price == second->price &&first->popularity == second->popularity)
    return 0;

  else
    return 1;

}
