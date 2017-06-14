// Módulo de produtos.

/**

  \file
  \brief Arquivo que contém as funções relativas ao módulo de produtos do
  aplicativo.

*/

#include "product.h"

/** Função que copia um produto.

    \param copy Endereço do produto que receberá as especificações copiadas.
    \param original Endereço do produto que será copiado.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja copiado com sucesso.

    */

errorLevel CopyProduct(product *copy, product *original) {

  strcpy(copy->name, original->name);
  copy->type = original->type;
  copy->price = original->price;
  copy->popularity = original->popularity;

  return Success;

}

/** Função que cria um produto.

    \param name Nome do produto a ser criado.
    \param type Tipo do produto a ser criado.
    \param price Preço do produto a ser criado.
    \param popularity Popularidade do produto a ser criado.
    \param new_product Endereço da estrutura de dados onde o produto será
    criado.
    \return A função retorna uma instância do tipo errorLevel: Success caso o
    produto seja criado com sucesso; Illegal_argument caso os parâmetros
    passados para a criação do produto sejam inválidos.

    */

errorLevel CreateProduct(char name[75], productType type, double price,
int popularity, product *new_product) {

  if(price <= 0 || price >= 1000000 || popularity < 0 || popularity > 100)
    return Illegal_argument;

  strcpy(new_product->name, name);
  new_product->type = type;
  new_product->price = price;
  new_product->popularity = popularity;

  return Success;

}

/** Função que compara dois produtos.

    \param first Endereço do primeiro produto que faz parte da comparação.
    \param second Endereço do segundo produto que faz parte da comparação.
    \return A função retorna 0 caso os produtos sejam iguais e 1 caso sejam
    diferentes.

    */

int CompareProducts(product *first, product *second) {

  if(!strcmp(first->name, second->name) && first->type == second->type
     && first->price == second->price
     && first->popularity == second->popularity)
    return 0;

  else
    return 1;

}
