// Módulo de pesquisa de produtos - Testes.

#include "product_search.h"
#include "gtest/gtest.h"

char name[75];
productList list;
product arroz;

TEST (ProductSearch, Product_Not_Found) {

  list.size = 0;

  strcpy(name, "Arroz");

  EXPECT_EQ ((search_product(name, &list) == -1), 1);

}

TEST (ProductSearch, Product_Found) {

  strcpy(arroz.name, "Arroz");
  arroz.price = 5;
  arroz.popularity = 100;
  arroz.type = Sale;

  add_product(&arroz, &list);

  strcpy(name, "Arroz");

  EXPECT_EQ ((search_product(name, &list) == 0), 1);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
