// Módulo de pesquisa de produtos - Cabeçalho.

/**
 * @file product_search.h
 * @brief Cabeçalho do módulo de busca de produtos.
 */

#ifndef PRODUCT_SEARCH_H_
#define PRODUCT_SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_level.h"
#include "product.h"

#define PRODUCT_DB "../../db/products.txt"

/**
 * @typedef productList
 * @brief Lista de produtos.
 *
 * Não pode conter produtos repetidos.
 *
 * Importante: Aloca dinamicamente o vetor que contém os produtos. Tal memória
 * deve ser liberada no término do programa chamando-se a função
 * CleanProductList(productList*) ou por meio da função free(productList.items).
 *
 * Exemplo:
 *
 *  productList lista_exemplo;
 *
 *  (Utilização da lista_exemplo)
 *
 *  CleanProductList(&lista_exemplo);
 *
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
errorLevel CleanProductList(productList*);
errorLevel CreateSpecification(productType, double, double, int, int,
                               productSpecification*);
errorLevel DeleteProduct(int, productList*);
errorLevel LoadProductList(productList*);
errorLevel SaveProductList(productList*);
errorLevel SearchProduct(char[75], productList*, productSpecification*,
                         productList*);
errorLevel SelectProduct(int, productList*, product*);
int MatchesSpecification(product*, productSpecification*);
int ValidIndex (int, int);

#endif  // PRODUCT_SEARCH_H_
