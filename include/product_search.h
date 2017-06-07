// Módulo de pesquisa de produtos - Cabeçalho.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  Rental,
  Sale,
  Service
}productType;

typedef enum {
  Success,
  Failure
}errorLevel;

typedef struct product {
  char name[75];
  productType type;
  float price;
  int popularity;
}product;

typedef struct productList {
  product *itens;
  int size;
}productList;

typedef struct results {
  unsigned int *indexes;
  int size;
}results;

errorLevel add_product(product*, productList*);
errorLevel search_product(char[75], productList*, results*);
