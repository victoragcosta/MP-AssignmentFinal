// Módulo de pesquisa de produtos - Testes.

/**

  @file
  @brief Arquivo que testa as funções relativas ao módulo de busca de produtos
  do aplicativo

*/

#include "product_search.h"

#include "gtest/gtest.h"

char name[75];
productList list, list2, query_results;
product novoProduto, copia, outro;
productSpecification generic, specific;

TEST (Initialization, Variables) {

  CleanProductList(&list);
  CleanProductList(&list2);
  CleanProductList(&query_results);
  CreateSpecification(All, 0, 1000000, 0, 100, &generic);

  EXPECT_EQ(1, true);

}

TEST (AddProduct, First) {

  ASSERT_EQ(list.size, 0);

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &novoProduto);

  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 1);
  EXPECT_EQ(strcmp(list.items[0].name, "Arroz"), 0);
  EXPECT_EQ(list.items[0].price, 5);
  EXPECT_EQ(list.items[0].type, Sale);
  EXPECT_EQ(list.items[0].popularity, 100);

}

TEST (AddProduct, Second) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Aulas de C++");
  CreateProduct(name, Service, 400, 95, &novoProduto);
  CopyProduct(&copia, &novoProduto);

  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 2);
  EXPECT_EQ(strcmp(list.items[0].name, "Arroz"), 0);
  EXPECT_EQ(list.items[0].price, 5);
  EXPECT_EQ(list.items[0].type, Sale);
  EXPECT_EQ(list.items[0].popularity, 100);
  EXPECT_EQ(strcmp(list.items[1].name, "Aulas de C++"), 0);
  EXPECT_EQ(list.items[1].price, 400);
  EXPECT_EQ(list.items[1].type, Service);
  EXPECT_EQ(list.items[1].popularity, 95);

}

TEST (AddProduct, Repeated_Product) {

  ASSERT_EQ(list.size, 2);

  EXPECT_EQ(AddProduct(&copia, &list), Failure);

  EXPECT_EQ(list.size, 2);

}

TEST (AddProduct, Illegal_Price_01) {

  list.size = 0;
  free(list.items);

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Iate de ouro");
  novoProduto.price = 400000000;
  novoProduto.popularity = 60;
  novoProduto.type = Rental;

  EXPECT_EQ(AddProduct(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddProduct, Illegal_Price_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Sick dog");
  novoProduto.price = -5;
  novoProduto.popularity = 0;
  novoProduto.type = Sale;

  EXPECT_EQ(AddProduct(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddProduct, Illegal_Popularity_01) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Vitrola anos 70");
  novoProduto.price = 125;
  novoProduto.popularity = 120;
  novoProduto.type = Rental;

  EXPECT_EQ(AddProduct(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (AddProduct, Illegal_Popularity_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novoProduto.name, "Brócolis com chucrute");
  novoProduto.price = 125;
  novoProduto.popularity = -5;
  novoProduto.type = Sale;

  EXPECT_EQ(AddProduct(&novoProduto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

TEST (CleanProductList, Invalid_List) {

  EXPECT_EQ(CleanProductList(NULL), Illegal_argument);

}

TEST (CleanProductList, New_List) {

  ASSERT_EQ((list2.items == NULL), true);

  EXPECT_EQ(CleanProductList(&list2), Success);

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

}

TEST (CleanProductList, Used_List) {

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

  strcpy(name, "Arroz integral");
  CreateProduct(name, Sale, 7, 70, &novoProduto);
  AddProduct(&novoProduto, &list2);

  strcpy(name, "Arroz branco");
  CreateProduct(name, Sale, 5, 85, &novoProduto);
  AddProduct(&novoProduto, &list2);

  ASSERT_EQ(list2.size, 2);
  ASSERT_EQ((list2.items == NULL), false);

  EXPECT_EQ(CleanProductList(&list2), Success);

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

}

TEST (CreateSpecification, Normal_Specification) {

  EXPECT_EQ(CreateSpecification(Rental, 0, 100000, 0, 100, &specific), Success);
  EXPECT_EQ(specific.type, Rental);
  EXPECT_EQ(specific.minimum_price, 0);
  EXPECT_EQ(specific.maximum_price, 100000);
  EXPECT_EQ(specific.minimum_popularity, 0);
  EXPECT_EQ(specific.maximum_popularity, 100);

}

TEST (ProductSearch, Product_Not_Found) {

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &novoProduto);
  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Chocolate");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Failure);
  EXPECT_EQ(query_results.size, 0);

}

TEST (ProductSearch, Product_Found) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Arroz");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[0])), 0);

}

TEST (ProductSearch, Multiple_results) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Carro");
  CreateProduct(name, Sale, 120000, 80, &novoProduto);
  AddProduct(&novoProduto, &list);

  strcpy(name, "Carro");
  CreateProduct(name, Rental, 2000, 85, &novoProduto);
  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

}

TEST (ProductSearch, Type_Restriction) {

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  CreateSpecification(Rental, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

}

TEST (ProductSearch, Price_Restriction_01) {

  strcpy(name, "Arroz");

  CreateProduct(name, Sale, 10, 90, &novoProduto);
  AddProduct(&novoProduto, &list);

  CreateProduct(name, Sale, 20, 95, &novoProduto);
  AddProduct(&novoProduto, &list);

  CreateProduct(name, Sale, 100, 82, &novoProduto);
  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  CreateSpecification(All, 0, 15, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[0])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[3])), 0);

}

TEST (ProductSearch, Price_Restriction_02) {

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  CreateSpecification(All, 10, 20, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[3])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[4])), 0);

}

TEST (ProductSearch, Popularity_Restriction) {

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  CreateSpecification(All, 0, 1000000, 90, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 3);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[0])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[3])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[2]), &(list.items[4])), 0);

}

TEST (ProductSearch, Partial_Name) {

  strcpy(name, "Camisa azul");

  CreateProduct(name, Sale, 35, 97, &novoProduto);
  AddProduct(&novoProduto, &list);

  ASSERT_EQ(list.size, 7);

  strcpy(name, "Camisa");

  CreateSpecification(All, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[6])), 0);

}

TEST (SelectProduct, Valid_Select) {

  strcpy(name, "Carro");

  ASSERT_EQ((SearchProduct(name, &list, &generic, &query_results) == Success),
            true);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(SelectProduct(1, &query_results, &novoProduto), Success);
  EXPECT_EQ(CompareProducts(&novoProduto, &(query_results.items[1])), 0);

}

TEST (SelectProduct, Invalid_Select) {

  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(SelectProduct(2, &query_results, &novoProduto), Illegal_argument);

}

TEST (DeleteProduct, Valid_Delete) {

  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(DeleteProduct(0, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

}

TEST (DeleteProduct, Invalid_Delete) {

  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

  ASSERT_EQ(DeleteProduct(1, &query_results), Illegal_argument);

}

TEST (DeleteProduct, Empty_List) {

  ASSERT_EQ(query_results.size, 1);
  ASSERT_EQ(DeleteProduct(0, &query_results), Success);
  ASSERT_EQ(query_results.size, 0);

  ASSERT_EQ(DeleteProduct(0, &query_results), Illegal_argument);

}

TEST (Termination, Variables) {

  CleanProductList(&list);
  CleanProductList(&list2);
  CleanProductList(&query_results);

  EXPECT_EQ(1, true);

}

int main(int argc, char **argv) {

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}
