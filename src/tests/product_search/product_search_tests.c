// Módulo de pesquisa de produtos - Testes.

/**

  \file
  \brief Arquivo que testa as funções relativas ao módulo de busca de produtos
  do aplicativo

*/

#include "product_search.h"
#include "gtest/gtest.h"

char name[75];
productList list, query_results;
product novoProduto, copia, outro;
productSpecification generic, specific;

TEST (Initialization, Variables) {

  //list.size = 0;
  create_specification(All, 0, 1000000, 0, 100, &generic);

  EXPECT_EQ (1, true);

}

TEST (CreateProduct, Normal_Product) {

  strcpy(name, "Arroz");

  EXPECT_EQ(create_product(name, Sale, 5, 100, &novoProduto), Success);
  EXPECT_EQ (strcmp(novoProduto.name, "Arroz"), 0);
  EXPECT_EQ (novoProduto.price, 5);
  EXPECT_EQ (novoProduto.type, Sale);
  EXPECT_EQ (novoProduto.popularity, 100);

}

TEST (CreateProduct, Illegal_Price_01) {

  strcpy(name, "Arroz estragado");

  EXPECT_EQ(create_product(name, Sale, -2, 5, &novoProduto), Illegal_argument);

}

TEST (CreateProduct, Illegal_Price_02) {

  strcpy(name, "Mansão");

  EXPECT_EQ(create_product(name, Sale, 277899000, 55, &novoProduto),
   Illegal_argument);

}

TEST (CreateProduct, Illegal_Popularity_01) {

  strcpy(name, "Bomba atômica");

  EXPECT_EQ(create_product(name, Sale, 500000, -5, &novoProduto),
    Illegal_argument);

}

TEST (CreateProduct, Illegal_Popularity_02) {

  strcpy(name, "Bilhete premiado de loteria");

  EXPECT_EQ(create_product(name, Sale, 5, 120, &novoProduto), Illegal_argument);

}

TEST (CopyProduct, Normal_Copy) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);

  copy_product(&copia, &novoProduto);

  EXPECT_EQ (strcmp(copia.name, "Clone"), 0);
  EXPECT_EQ (copia.price, 25);
  EXPECT_EQ (copia.type, Sale);
  EXPECT_EQ (copia.popularity, 92);

}

TEST (CompareProducts, Equal) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);

  copy_product(&copia, &novoProduto);

  EXPECT_EQ (compare_products(&novoProduto, &copia), 0);
  EXPECT_EQ (compare_products(&copia, &novoProduto), 0);

}

TEST (CompareProducts, Different_Name) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);

  strcpy(name, "Outro clone");

  create_product(name, Sale, 25, 92, &outro);

  EXPECT_EQ (compare_products(&novoProduto, &outro), 1);
  EXPECT_EQ (compare_products(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Type) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);
  create_product(name, Service, 25, 92, &outro);

  EXPECT_EQ (compare_products(&novoProduto, &outro), 1);
  EXPECT_EQ (compare_products(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Price) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);
  create_product(name, Sale, 27, 92, &outro);

  EXPECT_EQ (compare_products(&novoProduto, &outro), 1);
  EXPECT_EQ (compare_products(&outro, &novoProduto), 1);

}

TEST (CompareProducts, Different_Popularity) {

  strcpy(name, "Clone");

  create_product(name, Sale, 25, 92, &novoProduto);
  create_product(name, Sale, 25, 93, &outro);

  EXPECT_EQ (compare_products(&novoProduto, &outro), 1);
  EXPECT_EQ (compare_products(&outro, &novoProduto), 1);

}

TEST (AddProduct, First) {

  ASSERT_EQ(list.size, 0);

  strcpy(name, "Arroz");
  create_product(name, Sale, 5, 100, &novoProduto);

  add_product(&novoProduto, &list);

  ASSERT_EQ (list.size, 1);
  EXPECT_EQ (strcmp(list.items[0].name, "Arroz"), 0);
  EXPECT_EQ (list.items[0].price, 5);
  EXPECT_EQ (list.items[0].type, Sale);
  EXPECT_EQ (list.items[0].popularity, 100);

}

TEST (AddProduct, Second) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Aulas de C++");
  create_product(name, Service, 400, 95, &novoProduto);
  copy_product(&copia, &novoProduto);

  add_product(&novoProduto, &list);

  ASSERT_EQ (list.size, 2);
  EXPECT_EQ (strcmp(list.items[0].name, "Arroz"), 0);
  EXPECT_EQ (list.items[0].price, 5);
  EXPECT_EQ (list.items[0].type, Sale);
  EXPECT_EQ (list.items[0].popularity, 100);
  EXPECT_EQ (strcmp(list.items[1].name, "Aulas de C++"), 0);
  EXPECT_EQ (list.items[1].price, 400);
  EXPECT_EQ (list.items[1].type, Service);
  EXPECT_EQ (list.items[1].popularity, 95);

}

TEST (AddProduct, Repeated_Product) {

  ASSERT_EQ(list.size, 2);

  EXPECT_EQ(add_product(&copia, &list), Failure);

  EXPECT_EQ (list.size, 2);

}

TEST (AddProduct, Illegal_Price_01) {

  list.size = 0;
  free(list.items);

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Iate de ouro");
  novoProduto.price = 400000000;
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

TEST (CreateSpecification, Normal_Specification) {

  EXPECT_EQ(create_specification(Rental, 0, 100000, 0, 100, &specific), Success);
  EXPECT_EQ (specific.type, Rental);
  EXPECT_EQ (specific.minimum_price, 0);
  EXPECT_EQ (specific.maximum_price, 100000);
  EXPECT_EQ (specific.minimum_popularity, 0);
  EXPECT_EQ (specific.maximum_popularity, 100);

}

TEST (ProductSearch, Product_Not_Found) {

  strcpy(name, "Arroz");
  create_product(name, Sale, 5, 100, &novoProduto);
  add_product(&novoProduto, &list);

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Chocolate");

  ASSERT_EQ (search_product(name, &list, &query_results, &generic), Failure);
  EXPECT_EQ (query_results.size, 0);

}

TEST (ProductSearch, Product_Found) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Arroz");

  ASSERT_EQ (search_product(name, &list, &query_results, &generic), Success);
  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[0])), 0);

}

TEST (ProductSearch, Multiple_results) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Carro");
  create_product(name, Sale, 120000, 80, &novoProduto);
  add_product(&novoProduto, &list);

  strcpy(name, "Carro");
  create_product(name, Rental, 2000, 85, &novoProduto);
  add_product(&novoProduto, &list);

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  ASSERT_EQ (search_product(name, &list, &query_results, &generic), Success);
  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[2])), 0);

}

TEST (ProductSearch, Type_Restriction) {

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  create_specification(Rental, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ (search_product(name, &list, &query_results, &specific), Success);
  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[2])), 0);

}

TEST (ProductSearch, Price_Restriction_01) {

  strcpy(name, "Arroz");

  create_product(name, Sale, 10, 90, &novoProduto);
  add_product(&novoProduto, &list);

  create_product(name, Sale, 20, 95, &novoProduto);
  add_product(&novoProduto, &list);

  create_product(name, Sale, 100, 82, &novoProduto);
  add_product(&novoProduto, &list);

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  create_specification(All, 0, 15, 0, 100, &specific);

  ASSERT_EQ (search_product(name, &list, &query_results, &specific), Success);
  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[0])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[3])), 0);

}

TEST (ProductSearch, Price_Restriction_02) {

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  create_specification(All, 10, 20, 0, 100, &specific);

  ASSERT_EQ (search_product(name, &list, &query_results, &specific), Success);
  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[3])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[4])), 0);

}

TEST (ProductSearch, Popularity_Restriction) {

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  create_specification(All, 0, 1000000, 90, 100, &specific);

  ASSERT_EQ (search_product(name, &list, &query_results, &specific), Success);
  ASSERT_EQ (query_results.size, 3);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[0])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[3])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[2]), &(list.items[4])), 0);

}

TEST (ProductSearch, Partial_Name) {

  strcpy(name, "Camisa azul");

  create_product(name, Sale, 35, 97, &novoProduto);
  add_product(&novoProduto, &list);

  ASSERT_EQ(list.size, 7);

  strcpy(name, "Camisa");

  create_specification(All, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ (search_product(name, &list, &query_results, &specific), Success);
  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[6])), 0);

}

TEST (SelectProduct, Valid_Select) {

  strcpy(name, "Carro");

  ASSERT_EQ ((search_product(name, &list, &query_results, &generic) == Success),
  true);
  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ (select_product(1, &query_results, &novoProduto), Success);
  EXPECT_EQ (compare_products(&novoProduto, &(query_results.items[1])), 0);

}

TEST (SelectProduct, Invalid_Select) {

  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ (select_product(2, &query_results, &novoProduto), Illegal_argument);

}

TEST (DeleteProduct, Valid_Delete) {

  ASSERT_EQ (query_results.size, 2);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ (compare_products(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ (delete_product(0, &query_results), Success);
  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[2])), 0);

}

TEST (DeleteProduct, Invalid_Delete) {

  ASSERT_EQ (query_results.size, 1);
  EXPECT_EQ (compare_products(&(query_results.items[0]), &(list.items[2])), 0);

  ASSERT_EQ (delete_product(1, &query_results), Illegal_argument);

}

TEST (DeleteProduct, Empty_List) {

  ASSERT_EQ (query_results.size, 1);
  ASSERT_EQ (delete_product(0, &query_results), Success);
  ASSERT_EQ (query_results.size, 0);

  ASSERT_EQ (delete_product(0, &query_results), Illegal_argument);

}

TEST (Termination, Variables) {

  if(query_results.size != 0)
    free(query_results.items);

  if(list.items != 0)
    free(list.items);

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
