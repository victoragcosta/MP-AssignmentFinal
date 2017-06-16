// Módulo de pesquisa de produtos.

/**
 * @file product_search.c
 * @brief Implementação do módulo de pesquisa de produtos.
 */

#include "product_search.h"

/**
 * @fn errorLevel AddProduct(product *new_product, productList *list)
 * @brief Função que adiciona um produto à uma lista de produtos.
 * @param new_product Endereço do produto a ser adicionado.
 * @param list Endereço da lista que receberá o produto.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja adicionado à lista com sucesso; Failure caso o produto já
 * exista na lista; Illegal_argument, caso os parâmetros de produto passados
 * sejam inválidos ou a função receba um ponteiro nulo como parâmetro.
 */

errorLevel AddProduct(product *new_product, productList *list) {

  int i, empty_slot;

  /*
    Um produto não pode ter seu preço negativo ou maior que 1.000.000,00 nem
    ter sua popularidade negativa ou maior que 100. A função também não aceita
    receber um endereço que aponte para NULL. Caso uma dessas condições seja
    quebrada, a função retorna Illegal_argument.
   */

  if(new_product == NULL || new_product->price <= 0
     || new_product->price >= 1000000 || new_product->popularity < 0
     || new_product->popularity > 100)
      return Illegal_argument;

  /*
    Percorre-se a lista para verificar-se se o produto já não pertence à lista
    de produtos.
   */

  for (i = 0; i < (list->size); ++i) {

    if(!strcmp(new_product->name, list->items[i].name)
       && new_product->type == list->items[i].type
       && new_product->price == list->items[i].price
       && new_product->popularity == list->items[i].popularity)
      return Failure;

  }

  /*
    Caso o produto passado como argumento contenha campos válidos e ainda não
    pertença à lista, adiciona-se o produto à lista.
   */

  list->size++; /* Aumenta-se o tamanho da lista devido à adição. */

  /*
    Caso o produto adicionado seja o primeiro da lista, utiliza-se a função
    malloc para gerar o vetor de produtos. Do contrário, utiliza-se a função
    realloc para realocar o vetor de produtos.
   */

  if(list->size == 1)
    list->items = (product*) malloc(sizeof(product));

  else
    list->items = (product*) realloc(list->items, list->size * sizeof(product));

  empty_slot = (list->size)-1; /* Posição vaga na lista. */

  CopyProduct(&(list->items[empty_slot]), new_product);

  return Success;

}

/**
 * @fn errorLevel CleanProductList (productList *list)
 * @brief Função para limpar uma lista de produtos.
 * @param list Endereço da lista que será limpa.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * lista seja limpa com sucesso.
 */

errorLevel CleanProductList (productList *list) {

  /*
    Para limpar uma lista de produtos, atribui-se ao seu tamanho o valor 0 e,
    caso seja necessário, libera-se o vetor de items alocado dinamicamente e
    atribui-se a ele o valor NULL.
   */

  list->size = 0;

  if(list->items != NULL) {
    free(list->items);
    list->items = NULL;
  }

  return Success;

}

/**
 * @fn errorLevel CreateSpecification(productType type, double min_price,
 * double max_price, int min_popularity, int max_popularity,
 * productSpecification *new_specification)
 * @brief Função que cria uma especificação de busca.
 * @param type Tipo do produto a ser procurado.
 * @param min_price Preço mínimo do produto a ser procurado.
 * @param max_price Preço máximo do produto a ser procurado.
 * @param min_popularity Popularidade mínima do produto a ser procurado.
 * @param max_popularity Popularidade máxima do produto a ser procurado.
 * @param new_specification Endereço da estrutura de dados onde a especificação
 * será criada.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * especificação seja criada com sucesso; Illegal_argument caso a função receba
 * um ponteiro nulo como parâmetro.
 */

errorLevel CreateSpecification(
    productType type,
    double min_price,
    double max_price,
    int min_popularity,
    int max_popularity,
    productSpecification *new_specification) {

  if(new_specification == NULL)
    return Illegal_argument;

  new_specification->type = type;
  new_specification->minimum_price = min_price;
  new_specification->maximum_price = max_price;
  new_specification->minimum_popularity = min_popularity;
  new_specification->maximum_popularity = max_popularity;

  return Success;

}

/**
 * @fn errorLevel DeleteProduct (int index, productList *list)
 * @brief Função que remove um produto de uma lista de produtos.
 * @param index Índice do produto na lista de produtos.
 * @param list Endereço da lista que terá o produto removido.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja removido da lista com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido.
 */

errorLevel DeleteProduct (int index, productList *list) {

  int i;

  /*
    O índice do produto não pode ser negativo ou maior que o tamanho da lista,
    pois isso acessaria uma área da memória fora do vetor de produtos.
   */

  if(index < 0 || index >= list->size) {
    return Illegal_argument;
  }

  /*
    Caso a lista contenha apenas 1 item, libera-se o vetor de items e atribui-se
    a ele o valor NULL.
   */

  else if(list->size == 1) {
    free(list->items);
    list->items = NULL;
  }

  /* Caso contrário, o procedimento de deleção é mais complicado. */

  else {

    /*
      Primeiro, vamos "mover" todos os elementos do vetor de produtos que estão
      à direita do produto a ser removido uma "posição" para esquerda.
      Atingimos tal resultado sobrescrevendo o produto a ser removido com o
      produto que está a sua direita (o que pode ser feito com a função de
      copiar produtos) e repetindo esse procedimento até o penúltimo produto do
      vetor de produtos.
     */

    for (i = index; i < list->size - 1; ++i)
      CopyProduct(&(list->items[i]), &(list->items[i + 1]));

      /*
        Por fim, basta realocar a lista para que ela tenha um espaço a menos.
        Como o produto da última posição terá sido copiado para a penúltima
        posição, o produto que será "perdido" com o realocamento do vetor será
        aquele que deveria ser removido.
       */

    list->items = (product*) realloc(list->items, (list->size - 1)
                                     * sizeof(product));

  }

  /*
    Após uma deleção bem sucedida, deve-se diminuir o tamanho da lista em uma
    unidade.
   */

  (list->size) -= 1;

  return Success;

}

/**
 * @fn errorLevel InitializeProductList (productList *list)
 * @brief Função para iniciar uma lista de produtos.
 * @param list Endereço da lista que será incializada.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * lista seja inicializada com sucesso.
 */

errorLevel InitializeProductList (productList *list) {

  /*
    Para inicializar uma lista, basta dizer que seu tamanho é 0 e que seu
    vetor de produtos é NULL.
   */

  list->size = 0;
  list->items = NULL;

  return Success;

}

/**
 * @fn errorLevel SearchProduct(char query[75], productList *list,
 * productSpecification *specifics, productList *matches)
 * @brief Função que realiza a busca por um produto.
 * @param query Nome ou parte de nome dos produtos procurados.
 * @param list Endereço da lista onde a pesquisa de produtos será realizada.
 * @param specifics Endereço da especificação de busca utilizada para busca.
 * @param matches Endereço da lista de produtos onde os resultados serão
 * armazenados.
 * @return A função retorna uma instância do tipo errorLevel: Success caso a
 * busca retorne algum resultado; Failure caso a busca não retorne resultados;
 * Illegal_argument caso a função receba um ponteiro nulo como parâmetro.
 */

errorLevel SearchProduct(char query[75], productList *list,
                          productSpecification *specifics,
                          productList *matches) {

  int i;

  if(specifics == NULL)
    return Illegal_argument;

  CleanProductList(matches);

  /*
    Varre-se a lista de produtos procurando-se produtos cujo nome contenha a
    chave de busca e cujas características sejam permitidas pela especificação
    de busca. Caso encontre-se um produto que se encaixe nessa situação, ele
    é adicionado à lista de resultados.
   */

  for (i = 0; i < (list->size); ++i) {

    if((strstr(list->items[i].name, query) != NULL)
      && (specifics->type == All
      || specifics->type == list->items[i].type)
      && (list->items[i].price >= specifics->minimum_price
      && list->items[i].price <= specifics->maximum_price)
      && (list->items[i].popularity >= specifics->minimum_popularity
      && list->items[i].popularity <= specifics->maximum_popularity)) {

      AddProduct(&(list->items[i]), matches);

    }

  }

  if(matches->size == 0)
    return Failure;

  else
    return Success;

}

/**
 * @fn errorLevel SelectProduct(int index, productList *list,
 * product *selection)
 * @brief Função que seleciona um produto de uma lista de produtos.
 * @param index Índice do produto na lista de produtos.
 * @param list Endereço da lista que contém o produto desejado.
 * @param selection Endereço da estrutura de dados que reberá os parâmetros do
 * produto desejado.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja selecionado com sucesso; Illegal_argument, caso o índice
 * passado como argumento seja inválido ou seja fornecido um ponteiro nulo como
 * parâmetro.
 */

errorLevel SelectProduct(int index, productList *list, product *selection) {

  if(selection == NULL)
    return Illegal_argument;

  /*
    O índice do produto não pode ser negativo ou maior que o tamanho da lista,
    pois isso acessaria uma área da memória fora do vetor de produtos.
   */

  if(index >= list->size || index < 0)
    return Illegal_argument;

  CopyProduct(selection, &(list->items[index]));

  return Success;

}
