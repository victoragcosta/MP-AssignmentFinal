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
  product *items;
  int size;
}productList;

typedef struct productSpecification {
  double minimum_price;
  double maximum_price;
  productType type;
  int minimum_popularity;
  int maximum_popularity;
}productSpecification;

errorLevel add_product(product*, productList*);
errorLevel copy_product(product*, product*);
errorLevel create_product(char[75], productType, double, int, product*);
errorLevel create_specification(productType, double, double, int, int,
productSpecification*);
errorLevel delete_product (int, productList*);
errorLevel search_product(char[75], productList*, productList*,
productSpecification*);
errorLevel select_product(int, productList*, product*);
int compare_products(product*, product*);
