// Módulo de pesquisa de produtos - Cabeçalho.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  Rental,
  Sale,
  Service,
  All
}productType;

typedef enum {
  Success,
  Failure,
  Illegal_argument
}errorLevel;

typedef struct product {
  char name[75];
  productType type;
  double price;
  int popularity;
}product;

typedef struct productList {
  product *itens;
  int size;
}productList;

typedef struct productSpecification {
  double minimum_price;
  double maximum_price;
  productType type;
  int minimum_popularity;
  int maximum_popularity;
}productSpecification;

typedef struct results {
  unsigned int *indexes;
  int size;
}results;

errorLevel add_product(product*, productList*);
errorLevel create_product(char[75], productType, double, int, product*);
errorLevel create_specification(productType, double, double, int, int,
productSpecification*);
errorLevel search_product(char[75], productList*, results*,
productSpecification*);
