// Módulo de produtos - Cabeçalho.

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_level.h"

typedef enum {
  Rental,
  Sale,
  Service,
  All
}productType;

typedef struct product {
  char name[75];
  productType type;
  double price;
  int popularity;
}product;

errorLevel CopyProduct(product*, product*);
errorLevel CreateProduct(char[75], productType, double, int, product*);
int CompareProducts(product*, product*);

#endif  // PRODUCT_H_
