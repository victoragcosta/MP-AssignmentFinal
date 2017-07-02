// Módulo de produtos - Cabeçalho.

/**
 * @file product.h
 * @brief Cabeçalho do módulo de produtos.
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_level.h"

/**
 * @enum productType
 * @brief Contém os possíveis tipos de produto.
 *
 * É utilizado como um dos membros da estrutura de dados que modela um produto e
 * como um dos membros da estrutura de dados que modela as especificações de uma
 * busca por produtos.
 */

typedef enum {
  Rental, /**< O produto é um bem que está sendo oferecido para aluguel. */
  Sale, /**< O produto é um bem que está sendo oferecido para venda. */
  Service,  /**< O produto é um serviço que será prestado. */
  All /**< O produto pode ser qualquer um dos outros membros. Utilizado
           exclusivamente para uma especificação de busca de produtos. */
}productType;

/**
 * @typedef product
 * @brief Produto.
 *
 * Representa um bem/serviço.
 */

typedef struct product {
  char name[75];  /**< Nome do produto. */
  productType type; /**< Tipo do produto. */
  double price; /**< Preço do produto. Não deve ser negativo ou maior que
                     1.000.000,00.*/
  int popularity; /**< Popularidade do produto. Não deve ser negativa ou maior
                       100.*/
}product;

errorLevel CopyProduct(product*, product*);
errorLevel CreateProduct(char[75], productType, double, int, product*);
int CompareProducts(product*, product*);
int ConvertIntToProductType(int, productType*);
int ValidName(char[75]);
int ValidPopularity(int);
int ValidPrice(double);
int ValidProduct(product*);

#endif  // PRODUCT_H_
