// Módulo de produtos - Testes.

/**

  @file
  @brief Arquivo que testa as funções relativas ao módulo de produtos do
  aplicativo

*/

#include "product.h"

#include "gtest/gtest.h"

char name[75];
product novoProduto, copia, outro;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  EXPECT_EQ(1, true);

}

/*
  Teste da função CreateProduct utilizando-se parâmetros válidos para o produto.
 */

TEST (CreateProduct, Normal_Product) {

  strcpy(name, "Arroz");

  EXPECT_EQ(CreateProduct(name, Sale, 5, 100, &novoProduto), Success);
  EXPECT_EQ(strcmp(novoProduto.name, "Arroz"), 0);
  EXPECT_EQ(novoProduto.price, 5);
  EXPECT_EQ(novoProduto.type, Sale);
  EXPECT_EQ(novoProduto.popularity, 100);

}

/*
  Teste da função CreateProduct utilizando-se um parâmetro preço negativo (algo
  inválido) para o produto.
 */

TEST (CreateProduct, Illegal_Price_01) {

  strcpy(name, "Arroz estragado");

  EXPECT_EQ(CreateProduct(name, Sale, -2, 5, &novoProduto), Illegal_argument);

}

/*
  Teste da função CreateProduct utilizando-se um parâmetro preço muito grande
  (algo inválido) para o produto.
 */

TEST (CreateProduct, Illegal_Price_02) {

  strcpy(name, "Mansão");

  EXPECT_EQ(CreateProduct(name, Sale, 277899000, 55, &novoProduto),
            Illegal_argument);

}

/*
  Teste da função CreateProduct utilizando-se um parâmetro popularidade negativo
  (algo inválido) para o produto.
 */

TEST (CreateProduct, Illegal_Popularity_01) {

  strcpy(name, "Bomba atômica");

  EXPECT_EQ(CreateProduct(name, Sale, 500000, -5, &novoProduto),
            Illegal_argument);

}

/*
  Teste da função CreateProduct utilizando-se um parâmetro popularidade muito
  grande (algo inválido) para o produto.
 */

TEST (CreateProduct, Illegal_Popularity_02) {

  strcpy(name, "Bilhete premiado de loteria");

  EXPECT_EQ(CreateProduct(name, Sale, 5, 120, &novoProduto), Illegal_argument);

}

/*
  Teste da função CreateProduct passando um ponteiro NULL como endereço do
  produto (algo inválido).
 */

TEST (CreateProduct, Null_Pointer) {

  EXPECT_EQ(CreateProduct(name, Sale, 5, 120, NULL), Illegal_argument);

}

/* Teste da função ValidProduct para um produto válido. */

TEST (ValidProduct, Valid_Product) {

  EXPECT_EQ(CreateProduct(name, Sale, 5, 100, &novoProduto), Success);
  EXPECT_EQ(ValidProduct(&novoProduto), 1);

}

/* Teste da função ValidProduct para um produto com preço inválido. */

TEST (ValidProduct, Invalid_Price) {

  strcpy(novoProduto.name, "Iate de ouro");
  novoProduto.price = 400000000;
  novoProduto.popularity = 60;
  novoProduto.type = Rental;
  EXPECT_EQ(ValidProduct(&novoProduto), 0);

}

/* Teste da função ValidProduct para um produto com popularide inválida. */

TEST (ValidProduct, Invalid_Popularity) {

  strcpy(novoProduto.name, "Vitrola anos 70");
  novoProduto.price = 125;
  novoProduto.popularity = 120;
  novoProduto.type = Rental;
  EXPECT_EQ(ValidProduct(&novoProduto), 0);

}

/*
  Teste da função ValidProduct passando um ponteiro NULL como endereço do
  produto (algo inválido).
 */

TEST (ValidProduct, Null_Pointer) {

  EXPECT_EQ(ValidProduct(NULL), -1);

}

/*
  Teste da função CopyProduct utilizando-se endereços válidos de produtos.
 */

TEST (CopyProduct, Normal_Copy) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  CopyProduct(&copia, &novoProduto);

  EXPECT_EQ(strcmp(copia.name, "Clone"), 0);
  EXPECT_EQ(copia.price, 25);
  EXPECT_EQ(copia.type, Sale);
  EXPECT_EQ(copia.popularity, 92);

}

/*
  Teste da função CopyProduct passando um ponteiro NULL como endereço de um dos
  produtos (algo inválido).
 */

TEST (CopyProduct, Null_Pointer) {

  EXPECT_EQ(CopyProduct(&novoProduto, NULL), Illegal_argument);
  EXPECT_EQ(CopyProduct(NULL, &novoProduto), Illegal_argument);

}

/*
  Teste da função CompareProducts passando os endereços de dois produtos iguais
  como argumentos.
 */

TEST (CompareProducts, Equal) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  CopyProduct(&copia, &novoProduto);

  EXPECT_EQ(CompareProducts(&novoProduto, &copia), 0);
  EXPECT_EQ(CompareProducts(&copia, &novoProduto), 0);

}

/*
  Teste da função CompareProducts passando um mesmo endereço duas vezes como
  argumento.
 */

TEST (CompareProducts, Same_Argument) {

  EXPECT_EQ(CompareProducts(&copia, &copia), 0);

}

/*
  Teste da função CompareProducts passando os endereços de produtos com o nome
  diferente como argumentos.
 */


TEST (CompareProducts, Different_Name) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  strcpy(name, "Outro clone");

  CreateProduct(name, Sale, 25, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

/*
  Teste da função CompareProducts passando os endereços de produtos com o tipo
  diferente como argumentos.
 */

TEST (CompareProducts, Different_Type) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Service, 25, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

/*
  Teste da função CompareProducts passando os endereços de produtos com o preço
  diferente como argumentos.
 */

TEST (CompareProducts, Different_Price) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Sale, 27, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

/*
  Teste da função CompareProducts passando os endereços de produtos com a
  popularidade diferente como argumentos.
 */

TEST (CompareProducts, Different_Popularity) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Sale, 25, 93, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

/* Teste da função CompareProducts passando ponteiros NULL como argumentos. */

TEST (CompareProducts, Null_Pointer) {

  EXPECT_EQ(CompareProducts(&novoProduto, NULL), -1);
  EXPECT_EQ(CompareProducts(NULL, &novoProduto), -1);
  EXPECT_EQ(CompareProducts(NULL, NULL), -1);

}

/*
  Finalização (desalocação de memória alocada dinamicamente) das variáveis
  utilizadas nos testes.
 */

TEST (Termination, Variables) {

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
