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

TEST (Initialization, Variables) {

  EXPECT_EQ(1, true);

}

TEST (CreateProduct, Normal_Product) {

  strcpy(name, "Arroz");

  EXPECT_EQ(CreateProduct(name, Sale, 5, 100, &novoProduto), Success);
  EXPECT_EQ(strcmp(novoProduto.name, "Arroz"), 0);
  EXPECT_EQ(novoProduto.price, 5);
  EXPECT_EQ(novoProduto.type, Sale);
  EXPECT_EQ(novoProduto.popularity, 100);

}

TEST (CreateProduct, Illegal_Price_01) {

  strcpy(name, "Arroz estragado");

  EXPECT_EQ(CreateProduct(name, Sale, -2, 5, &novoProduto), Illegal_argument);

}

TEST (CreateProduct, Illegal_Price_02) {

  strcpy(name, "Mansão");

  EXPECT_EQ(CreateProduct(name, Sale, 277899000, 55, &novoProduto),
            Illegal_argument);

}

TEST (CreateProduct, Illegal_Popularity_01) {

  strcpy(name, "Bomba atômica");

  EXPECT_EQ(CreateProduct(name, Sale, 500000, -5, &novoProduto),
            Illegal_argument);

}

TEST (CreateProduct, Illegal_Popularity_02) {

  strcpy(name, "Bilhete premiado de loteria");

  EXPECT_EQ(CreateProduct(name, Sale, 5, 120, &novoProduto), Illegal_argument);

}

TEST (CreateProduct, Null_Pointer) {

  EXPECT_EQ(CreateProduct(name, Sale, 5, 120, NULL), Illegal_argument);

}

TEST (CopyProduct, Normal_Copy) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  CopyProduct(&copia, &novoProduto);

  EXPECT_EQ(strcmp(copia.name, "Clone"), 0);
  EXPECT_EQ(copia.price, 25);
  EXPECT_EQ(copia.type, Sale);
  EXPECT_EQ(copia.popularity, 92);

}

TEST (CopyProduct, Null_Pointer) {

  EXPECT_EQ(CopyProduct(&novoProduto, NULL), Illegal_argument);
  EXPECT_EQ(CopyProduct(NULL, &novoProduto), Illegal_argument);

}

TEST (CompareProducts, Equal) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  CopyProduct(&copia, &novoProduto);

  EXPECT_EQ(CompareProducts(&novoProduto, &copia), 0);
  EXPECT_EQ(CompareProducts(&copia, &novoProduto), 0);

}

TEST (CompareProducts, Different_Name) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);

  strcpy(name, "Outro clone");

  CreateProduct(name, Sale, 25, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Type) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Service, 25, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Price) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Sale, 27, 92, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Popularity) {

  strcpy(name, "Clone");

  CreateProduct(name, Sale, 25, 92, &novoProduto);
  CreateProduct(name, Sale, 25, 93, &outro);

  EXPECT_EQ(CompareProducts(&novoProduto, &outro), 1);
  EXPECT_EQ(CompareProducts(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Null_Pointer) {

  EXPECT_EQ(CompareProducts(&novoProduto, NULL), -1);
  EXPECT_EQ(CompareProducts(NULL, &novoProduto), -1);

}

TEST (Termination, Variables) {

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
