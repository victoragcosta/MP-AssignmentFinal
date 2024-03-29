// Módulo de pesquisa de produtos - Testes.

/**

  @file product_search_tests.c
  @brief Arquivo que testa as funções relativas ao módulo de busca de produtos
  do aplicativo

*/

#include "product_search.h"

#include "gtest/gtest.h"

char name[75];
productList list, list2, query_results;
product novo_produto, copia, outro;
productSpecification generic, specific;

/* Inicialização das variáveis utilizadas nos testes.*/

TEST (Initialization, Variables) {

  CleanProductList(&list);
  CleanProductList(&list2);
  CleanProductList(&query_results);
  CreateSpecification(All, 0, 1000000, 0, 100, &generic);

  EXPECT_EQ(1, true);

}

/*
  Teste da função AddProduct para adicionar o primeiro produto à uma lista de
  produtos.
 */

TEST (AddProduct, First) {

  ASSERT_EQ(list.size, 0);

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &novo_produto);

  AddProduct(&novo_produto, &list);

  ASSERT_EQ(list.size, 1);
  EXPECT_EQ(strcmp(list.items[0].name, "Arroz"), 0);
  EXPECT_EQ(list.items[0].price, 5);
  EXPECT_EQ(list.items[0].type, Sale);
  EXPECT_EQ(list.items[0].popularity, 100);

}

/*
  Teste da função AddProduct para adicionar o segundo produto à uma lista de
  produtos.
 */

TEST (AddProduct, Second) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Aulas de C++");
  CreateProduct(name, Service, 400, 95, &novo_produto);
  CopyProduct(&copia, &novo_produto);

  AddProduct(&novo_produto, &list);

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

/*
  Teste da função AddProduct para tentar adicionar um produto repetido à uma
  lista de produtos (algo inválido).
 */

TEST (AddProduct, Repeated_Product) {

  ASSERT_EQ(list.size, 2);

  EXPECT_EQ(AddProduct(&copia, &list), Failure);

  EXPECT_EQ(list.size, 2);

}

/*
  Teste da função AddProduct para tentar adicionar um produto com nome inválido
  à uma lista de produtos.
 */

TEST (AddProduct, Invalid_Name) {

  CleanProductList(&list);

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Coisas|Coisas");
  novo_produto.price = 400;
  novo_produto.popularity = 60;
  novo_produto.type = Rental;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Primeiro teste da função AddProduct para tentar adicionar um produto com preço
  ilegal à uma lista de produtos.
 */

TEST (AddProduct, Invalid_Price_01) {

  CleanProductList(&list);

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Iate de ouro");
  novo_produto.price = 400000000;
  novo_produto.popularity = 60;
  novo_produto.type = Rental;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Segundo teste da função AddProduct para tentar adicionar um produto com preço
  ilegal à uma lista de produtos.
 */

TEST (AddProduct, Invalid_Price_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Sick dog");
  novo_produto.price = -5;
  novo_produto.popularity = 0;
  novo_produto.type = Sale;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Primeiro teste da função AddProduct para tentar adicionar um produto com
  popularidade ilegal à uma lista de produtos.
 */

TEST (AddProduct, Invalid_Popularity_01) {

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Vitrola anos 70");
  novo_produto.price = 125;
  novo_produto.popularity = 120;
  novo_produto.type = Rental;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Segundo teste da função AddProduct para tentar adicionar um produto com
  popularidade ilegal à uma lista de produtos.
 */

TEST (AddProduct, Invalid_Popularity_02) {

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Brócolis com chucrute");
  novo_produto.price = 125;
  novo_produto.popularity = -5;
  novo_produto.type = Sale;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Teste da função AddProduct para tentar adicionar um produto de tipo ilegal à
  uma lista de produtos.
 */

TEST (AddProduct, Invalid_Type) {

  ASSERT_EQ(list.size, 0);

  strcpy(novo_produto.name, "Buffet all-incluse");
  novo_produto.price = 80;
  novo_produto.popularity = 20;
  novo_produto.type = All;

  EXPECT_EQ(AddProduct(&novo_produto, &list), Illegal_argument);

  ASSERT_EQ(list.size, 0);

}

/*
  Teste da função CleanProductList passando-se como argumento um ponteiro nulo.
 */

TEST (CleanProductList, Invalid_List) {

  EXPECT_EQ(CleanProductList(NULL), Illegal_argument);

}

/*
  Teste da função CleanProductList passando-se como argumento uma lista vazia.
 */

TEST (CleanProductList, New_List) {

  ASSERT_EQ((list2.items == NULL), true);

  EXPECT_EQ(CleanProductList(&list2), Success);

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

}

/* Teste da função AddProduct passando-se como argumento uma lista cheia. */

TEST (CleanProductList, Used_List) {

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

  strcpy(name, "Arroz integral");
  CreateProduct(name, Sale, 7, 70, &novo_produto);
  AddProduct(&novo_produto, &list2);

  strcpy(name, "Arroz branco");
  CreateProduct(name, Sale, 5, 85, &novo_produto);
  AddProduct(&novo_produto, &list2);

  ASSERT_EQ(list2.size, 2);
  ASSERT_EQ((list2.items == NULL), false);

  EXPECT_EQ(CleanProductList(&list2), Success);

  ASSERT_EQ(list2.size, 0);
  ASSERT_EQ((list2.items == NULL), true);

}

/*
  Teste da função CreateSpecification passando-se como argumento um endereço de
  especificação válido.
 */

TEST (CreateSpecification, Normal_Specification) {

  EXPECT_EQ(CreateSpecification(Rental, 0, 100000, 0, 100, &specific), Success);
  EXPECT_EQ(specific.type, Rental);
  EXPECT_EQ(specific.minimum_price, 0);
  EXPECT_EQ(specific.maximum_price, 100000);
  EXPECT_EQ(specific.minimum_popularity, 0);
  EXPECT_EQ(specific.maximum_popularity, 100);

}

/*
  Teste da função CreateSpecification passando-se como argumento um ponteiro
  nulo.
 */

TEST (CreateSpecification, Invalid_Specification) {

  EXPECT_EQ(CreateSpecification(Rental, 0, 10, 0, 100, NULL), Illegal_argument);

}

/* Teste da função ProductSearch para uma busca sem resultados. */

TEST (ProductSearch, Product_Not_Found) {

  strcpy(name, "Arroz");
  CreateProduct(name, Sale, 5, 100, &novo_produto);
  AddProduct(&novo_produto, &list);

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Chocolate");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Failure);
  EXPECT_EQ(query_results.size, 0);

}

/* Teste da função ProductSearch para uma busca com resultados. */

TEST (ProductSearch, Product_Found) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Arroz");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[0])), 0);

}

/* Teste da função ProductSearch para uma busca com múltiplos resultados. */

TEST (ProductSearch, Multiple_results) {

  ASSERT_EQ(list.size, 1);

  strcpy(name, "Carro");
  CreateProduct(name, Sale, 120000, 80, &novo_produto);
  AddProduct(&novo_produto, &list);

  strcpy(name, "Carro");
  CreateProduct(name, Rental, 2000, 85, &novo_produto);
  AddProduct(&novo_produto, &list);

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  ASSERT_EQ(SearchProduct(name, &list, &generic, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

}

/* Teste da função ProductSearch para uma busca com restrição de tipo. */

TEST (ProductSearch, Type_Restriction) {

  ASSERT_EQ(list.size, 3);

  strcpy(name, "Carro");

  CreateSpecification(Rental, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

}

/*
  Primeiro teste da função ProductSearch para uma busca com restrição de preço.
 */

TEST (ProductSearch, Price_Restriction_01) {

  strcpy(name, "Arroz");

  CreateProduct(name, Sale, 10, 90, &novo_produto);
  AddProduct(&novo_produto, &list);

  CreateProduct(name, Sale, 20, 95, &novo_produto);
  AddProduct(&novo_produto, &list);

  CreateProduct(name, Sale, 100, 82, &novo_produto);
  AddProduct(&novo_produto, &list);

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  CreateSpecification(All, 0, 15, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[0])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[3])), 0);

}

/*
  Segundo teste da função ProductSearch para uma busca com restrição de preço.
 */

TEST (ProductSearch, Price_Restriction_02) {

  ASSERT_EQ(list.size, 6);

  strcpy(name, "Arroz");

  CreateSpecification(All, 10, 20, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[3])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[4])), 0);

}

/*
  Teste da função ProductSearch para uma busca com restrição de popularidade.
 */

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

/*
  Teste da função ProductSearch para uma busca com um nome parcial do produto.
 */

TEST (ProductSearch, Partial_Name) {

  strcpy(name, "Camisa azul");

  CreateProduct(name, Sale, 35, 97, &novo_produto);
  AddProduct(&novo_produto, &list);

  ASSERT_EQ(list.size, 7);

  strcpy(name, "Camisa");

  CreateSpecification(All, 0, 1000000, 0, 100, &specific);

  ASSERT_EQ(SearchProduct(name, &list, &specific, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[6])), 0);

}

/*
  Teste da função ProductSearch para ponteiros nulos passados como argumentos.
 */

TEST (ProductSearch, Invalid_Adresses) {

  strcpy(name, "Camisa");

  EXPECT_EQ(SearchProduct(name, NULL, &generic, &query_results),
            Illegal_argument);
  EXPECT_EQ(SearchProduct(name, &list, NULL, &query_results), Illegal_argument);
  EXPECT_EQ(SearchProduct(name, &list, &generic, NULL), Illegal_argument);
  EXPECT_EQ(SearchProduct(name, NULL, NULL, &query_results), Illegal_argument);
  EXPECT_EQ(SearchProduct(name, NULL, &generic, NULL), Illegal_argument);
  EXPECT_EQ(SearchProduct(name, &list, NULL, NULL), Illegal_argument);
  EXPECT_EQ(SearchProduct(name, NULL, NULL, NULL), Illegal_argument);

}

/* Teste da função SelectProduct para uma seleção válida. */

TEST (SelectProduct, Valid_Select) {

  strcpy(name, "Carro");

  ASSERT_EQ((SearchProduct(name, &list, &generic, &query_results) == Success),
            true);
  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(SelectProduct(1, &query_results, &novo_produto), Success);
  EXPECT_EQ(CompareProducts(&novo_produto, &(query_results.items[1])), 0);

}

/* Teste da função SelectProduct para uma seleção com indíce inválido. */

TEST (SelectProduct, Invalid_Select) {

  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(SelectProduct(2, &query_results, &novo_produto), Illegal_argument);

}

/* Teste da função SelectProduct passando-se ponteiros NULL como argumentos. */

TEST (SelectProduct, Invalid_Adresses) {

  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(SelectProduct(0, NULL, &novo_produto), Illegal_argument);
  ASSERT_EQ(SelectProduct(0, &query_results, NULL), Illegal_argument);
  ASSERT_EQ(SelectProduct(0, NULL, NULL), Illegal_argument);

}

/* Teste da função DeleteProduct para uma deleção válida. */

TEST (DeleteProduct, Valid_Delete) {

  ASSERT_EQ(query_results.size, 2);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[1])), 0);
  EXPECT_EQ(CompareProducts(&(query_results.items[1]), &(list.items[2])), 0);

  ASSERT_EQ(DeleteProduct(0, &query_results), Success);
  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

}

/* Teste da função DeleteProduct para uma deleção inválida. */

TEST (DeleteProduct, Invalid_Delete) {

  ASSERT_EQ(query_results.size, 1);
  EXPECT_EQ(CompareProducts(&(query_results.items[0]), &(list.items[2])), 0);

  ASSERT_EQ(DeleteProduct(1, &query_results), Illegal_argument);

}

/* Teste da função DeleteProduct para uma lista vazia. */

TEST (DeleteProduct, Empty_List) {

  ASSERT_EQ(query_results.size, 1);
  ASSERT_EQ(DeleteProduct(0, &query_results), Success);
  ASSERT_EQ(query_results.size, 0);

  ASSERT_EQ(DeleteProduct(0, &query_results), Illegal_argument);

}

/* Teste da função SaveProductList para uma lista válida. */

TEST (SaveProductList, Valid_List) {

  ASSERT_EQ(list.size, 7);

  EXPECT_EQ(SaveProductList(&list), Success);

}

/*
  Teste da função SaveProductList passando um ponteiro NULL como endereço de
  lista de produtos (algo inválido).
 */

TEST (SaveProductList, Invalid_List) {

  EXPECT_EQ(SaveProductList(NULL), Illegal_argument);

}

/* Teste da função LoadProductList para uma lista vazia. */

TEST (LoadProductList, Clean_List) {

  CleanProductList(&list2);

  ASSERT_EQ(list2.size, 0);

  EXPECT_EQ(LoadProductList(&list2), Success);

  EXPECT_EQ(list2.size, 7);

}

/* Teste da função LoadProductList para uma lista com items. */

TEST (LoadProductList, List_With_Items) {

  CleanProductList(&list2);

  ASSERT_EQ(list2.size, 0);

  strcpy(name, "Arroz");

  CreateProduct(name, Sale, 10, 90, &novo_produto);
  AddProduct(&novo_produto, &list2);

  CreateProduct(name, Sale, 20, 95, &novo_produto);
  AddProduct(&novo_produto, &list2);

  CreateProduct(name, Sale, 100, 82, &novo_produto);
  AddProduct(&novo_produto, &list2);

  ASSERT_EQ(list2.size, 3);

  EXPECT_EQ(LoadProductList(&list2), Success);

  EXPECT_EQ(list2.size, 7);

}

/*
  Teste da função LoadProductList passando um ponteiro NULL como endereço de
  lista de produtos (algo inválido).
 */

TEST (LoadProductList, Invalid_List) {

  EXPECT_EQ(LoadProductList(NULL), Illegal_argument);

}

/*
  Finalização (desalocação de memória alocada dinamicamente) das variáveis
  utilizadas nos testes.
 */

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
