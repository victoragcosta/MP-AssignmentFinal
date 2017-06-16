// Módulo de produtos.

/**
 * @file product.c
 * @brief Implementação do módulo de produtos.
 */

#include "product.h"

/**
 * @fn errorLevel CopyProduct(product *copy, product *original)
 * @brief Função que copia um produto.
 * @param copy Endereço do produto que receberá as especificações copiadas.
 * @param original Endereço do produto que será copiado.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja copiado com sucesso; Illegal_argument caso um dos argumentos
 * passados seja um ponteiro nulo.
 */

errorLevel CopyProduct(product *copy, product *original) {

  if(copy == NULL || original == NULL)
    return Illegal_argument;

  strcpy(copy->name, original->name);
  copy->type = original->type;
  copy->price = original->price;
  copy->popularity = original->popularity;

  return Success;

}

/**
 * @fn errorLevel CreateProduct(char name[75], productType type, double price,
 * int popularity, product *new_product)
 * @brief Função que cria um produto.
 * @param name Nome do produto a ser criado.
 * @param type Tipo do produto a ser criado.
 * @param price Preço do produto a ser criado.
 * @param popularity Popularidade do produto a ser criado.
 * @param new_product Endereço da estrutura de dados onde o produto será
 * criado.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja criado com sucesso; Illegal_argument caso os parâmetros
 * passados para a criação do produto sejam inválidos ou caso um dos produtos
 * passados seja um ponteiro nulo.
 */

errorLevel CreateProduct(char name[75], productType type, double price,
int popularity, product *new_product) {

  if(new_product == NULL || !ValidPrice(price) || !ValidPopularity(popularity))
    return Illegal_argument;

  strcpy(new_product->name, name);
  new_product->type = type;
  new_product->price = price;
  new_product->popularity = popularity;

  return Success;

}

/**
 * @fn int CompareProducts(product *first, product *second)
 * @brief Função que compara dois produtos.
 * @param first Endereço do primeiro produto que faz parte da comparação.
 * @param second Endereço do segundo produto que faz parte da comparação.
 * @return A função retorna -1 caso algum dos argumentos seja um ponteiro nulo,
 * 0 caso os produtos sejam iguais e 1 caso sejam diferentes.
 */

int CompareProducts(product *first, product *second) {

  if(first == NULL || second == NULL)
    return -1;

  /*
    Verifica-se individualmente se cada um dos campos dos 2 produtos são iguais.
   */

  else if(!strcmp(first->name, second->name)
     && first->type == second->type
     && first->price == second->price
     && first->popularity == second->popularity)
    return 0;

  else
    return 1;

}

int ValidPrice(double price) {

  /* Um produto não pode ter seu preço negativo ou maior que 1.000.000,00. */

  if(price > 0 && price <= 1000000)
    return 1;

  else
    return 0;

}

int ValidPopularity(int popularity) {

  /* Um produto não pode ter sua popularidade negativa ou maior que 100. */

  if(popularity >= 0 && popularity <= 100)
    return 1;

  else
    return 0;

}

int ValidProduct(product *item) {

  else if(ValidPrice(item->price) && ValidPopularity(item->popularity))
    return 1;

  else
    return 0;

}
