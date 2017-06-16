// Módulo de pesquisa de produtos - Cabeçalho.

#ifndef PRODUCT_SEARCH_H_
#define PRODUCT_SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_level.h"
#include "product.h"

/**
 * @typedef productList
 * @brief Lista de produtos.
 */

typedef struct productList {
  product *items; /**< Items na lista. Vetor de tipo product. */
  int size; /**< Tamanho da lista. Não pode ser negativo. */
}productList;

/**
 * @typedef productSpecification
 * @brief Especificação de busca de produtos.
 */

typedef struct productSpecification {
  double minimum_price; /**< Preço mínimo do(s) produto(s). */
  double maximum_price; /**< Preço máximo do(s) produto(s). */
  productType type;  /**< Tipo do(s) produto(s). Pode ser "All" caso se deseje
                          pesquisar produtos de qualquer tipo.*/
  int minimum_popularity; /**< Popularidade mínima do(s) produto(s). */
  int maximum_popularity; /**< Popularidade máxima do(s) produto(s). */
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
