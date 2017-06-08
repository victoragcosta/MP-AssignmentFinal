// Módulo de pesquisa de produtos - Testes.

#include "product_search.h"
#include "gtest/gtest.h"

char name[75];
productList list;
product novoProduto;
results query_results;
productSpecification generic;

TEST (Inicialization, Variables) {

  list.size = 0;
  generic.minimum_price = 0;
  generic.maximum_price = 100000;
  generic.type = All;
  generic.minimum_popularity = 0;
  generic.maximum_popularity = 100;

  EXPECT_EQ (1, true);

}

TEST (AddProduct, First) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Arroz");
  novoProduto.price = 5;
  novoProduto.popularity = 100;
  novoProduto.type = Sale;

  add_product(&novoProduto, &list);

  ASSERT_EQ (list.size, 1);
  EXPECT_EQ (strcmp(list.itens[0].name, "Arroz"), 0);
  EXPECT_EQ (list.itens[0].price, 5);
  EXPECT_EQ (list.itens[0].type, Sale);
  EXPECT_EQ (list.itens[0].popularity, 100);

}

TEST (AddProduct, Second) {

  ASSERT_EQ(list.size, 1);

  strcpy(novoProduto.name, "Aulas de C++");
  novoProduto.price = 400;
  novoProduto.popularity = 95;
  novoProduto.type = Service;

  add_product(&novoProduto, &list);

  ASSERT_EQ (list.size, 2);
  EXPECT_EQ (strcmp(list.itens[0].name, "Arroz"), 0);
  EXPECT_EQ (list.itens[0].price, 5);
  EXPECT_EQ (list.itens[0].type, Sale);
  EXPECT_EQ (list.itens[0].popularity, 100);
  EXPECT_EQ (strcmp(list.itens[1].name, "Aulas de C++"), 0);
  EXPECT_EQ (list.itens[1].price, 400);
  EXPECT_EQ (list.itens[1].type, Service);
  EXPECT_EQ (list.itens[1].popularity, 95);

}

TEST (AddProduct, Illegal_Price_01) {

  list.size = 0;
  free(list.itens);

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Iate de ouro");
  novoProduto.price = 40000000;
  novoProduto.popularity = 60;
  novoProduto.type = Rental;

  EXPECT_EQ(add_product(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ (list.size, 0);

}

TEST (AddProduct, Illegal_Price_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Sick dog");
  novoProduto.price = -5;
  novoProduto.popularity = 0;
  novoProduto.type = Sale;

  EXPECT_EQ(add_product(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ (list.size, 0);

}

TEST (AddProduct, Illegal_Popularity_01) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Vitrola anos 70");
  novoProduto.price = 125;
  novoProduto.popularity = 120;
  novoProduto.type = Rental;

  EXPECT_EQ(add_product(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ (list.size, 0);

}

TEST (AddProduct, Illegal_Popularity_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Brócolis com chucrute");
  novoProduto.price = 125;
  novoProduto.popularity = -5;
  novoProduto.type = Sale;

  EXPECT_EQ(add_product(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ (list.size, 0);

}

TEST (ProductSearch, Product_Not_Found) {

  strcpy(novoProduto.name, "Arroz");
  novoProduto.price = 5;
  novoProduto.popularity = 100;
  novoProduto.type = Sale;

  add_product(&novoProduto, &list);

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Chocolate");

  ASSERT_EQ ((search_product(name, &list, &query_results) == Failure), true);
  EXPECT_EQ (query_results.size, 0);

}

TEST (ProductSearch, Product_Found) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Arroz");

  EXPECT_EQ ((search_product(name, &list, &query_results) == 0), 1);
  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (query_results.indexes[0], 0);

}

TEST (Termination, Variables) {

  free(query_results.indexes);
  free(list.itens);

  EXPECT_EQ(1, true);
  
}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
