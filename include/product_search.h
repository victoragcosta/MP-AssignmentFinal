// Módulo de pesquisa de produtos - Cabeçalho.

#ifndef PRODUCT_SEARCH_H_
#define PRODUCT_SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_level.h"
#include "product.h"

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
errorLevel CreateSpecification(productType, double, double, int, int,
                               productSpecification*);
errorLevel DeleteProduct (int, productList*);
errorLevel InitializeProductList (productList*);
errorLevel SearchProduct(char[75], productList*, productSpecification*,
                         productList*);
errorLevel SelectProduct(int, productList*, product*);

#endif  // PRODUCT_SEARCH_H_
