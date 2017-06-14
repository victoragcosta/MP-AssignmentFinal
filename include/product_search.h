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

errorLevel AddProduct(product*, productList*);
errorLevel CleanProductList (productList*);
errorLevel CopyProduct(product*, product*);
errorLevel CreateProduct(char[75], productType, double, int, product*);
errorLevel CreateSpecification(productType, double, double, int, int,
                               productSpecification*);
errorLevel DeleteProduct (int, productList*);
errorLevel InitializeProductList (productList*);
errorLevel SearchProduct(char[75], productList*, productSpecification*,
                         productList*);
errorLevel SelectProduct(int, productList*, product*);
int CompareProducts(product*, product*);
