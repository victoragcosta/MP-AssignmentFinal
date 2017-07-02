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
 * Argumento passado por referência.
 * @param original Endereço do produto que será copiado.
 * Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja copiado com sucesso; Illegal_argument caso um dos argumentos
 * passados seja um ponteiro nulo.
 *
 * Copia os dados de um produto para outro produto.
 *
 * Assertivas de entrada:
 *  -Ambos copy e original devem ser diferentes de NULL.
 *  -Ambos copy e original devem apontar para estruturas de dados do tipo
 *   product.
 *
 * Assertivas de saída:
 *  -Os parâmetros do produto no endereço copy serão os mesmos que os parâmetros
 * do produto no endereço original.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço copy serão sobrescritas pelas
 * informações contidas no endereço original.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo product alocadas estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
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
 * criado. Argumento passado por referência.
 * @return A função retorna uma instância do tipo errorLevel: Success caso o
 * produto seja criado com sucesso; Illegal_argument caso os argumentos
 * passados para a criação do produto sejam inválidos ou caso um dos argumentos
 * passados seja um ponteiro nulo.
 *
 * Atualiza os dados de uma estrutura de dados do tipo product a partir de uma
 * string, uma estrutura de dados do tipo productType, um double e um int. Os
 * dados em new_product são sobrescritos com os dados fornecidos como argumentos
 * da função.
 *
 * Assertivas de entrada:
 *  -O parâmetro new_product deve ser diferente de NULL.
 *  -O parâmetro new_product deve apontar para uma estrutura de dados do tipo
 * product.
 *
 * Assertivas de saída:
 *  -Os membros do produto no endereço new_product serão aqueles passados como
 * argumentos para a função.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *
 * Assertivas de contrato:
 *  -As informações contidas no endereço new_product serão sobrescritas pelas
 * informações passadas como argumentos da função.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

errorLevel CreateProduct(char name[75], productType type, double price,
int popularity, product *new_product) {

  if(new_product == NULL || !ValidPrice(price) || !ValidPopularity(popularity)
     || type == All || !ValidName(name))
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
 * Argumento passado por referência.
 * @param second Endereço do segundo produto que faz parte da comparação.
 * Argumento passado por referência.
 * @return A função retorna -1 caso algum dos argumentos seja um ponteiro nulo,
 * 0 caso os produtos sejam iguais e 1 caso sejam diferentes.
 *
 * Verifica se todos os campos de duas estruturas de dados do tipo product são
 * iguais. Compara-se manualmente cada campo dos dois produtos.
 *
 * Assertivas de entrada:
 *  -Ambos first e second devem ser diferentes de NULL.
 *  -Ambos first e second devem apontar para estruturas de dados do tipo
 *   product.
 *
 * Assertivas de saída:
 *  -Os parâmetros do produto no endereço first e second estarão inalterados.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se os produtos são iguais ou
 * não ou se os argumentos passados são ilegais, sem alterar os produtos em si.
 *
 * Requisitos:
 *  -Duas estruturas de dados do tipo product alocadas estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
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

/**
 * @fn int ConvertIntToProductType(int number, productType *type)
 * @brief Função que converte um inteiro para um tipo de produto.
 * @param number Número convertido.
 * @param type Endereço de variável do tipo productType que recebe o resultado
 * da conversão.
 * @return A função retorna um inteiro: 0 se a conversão foi bem sucedida; -1 se
 * a função recebeu um ponteiro NULL como argumento.
 *
 * Realiza a conversão de um número inteiro para seu respectivo tipo de produto
 * contido na enumeração productType e atribui esse resultado
 * para a estrutura de dados productType no endereço type. Caso o número não
 * represente um productType válido, será atribuído o productType "All".
 *
 * Assertivas de entrada:
 *  -type != NULL.
 *  -type aponta para uma estrutura de dados do tipo productType.
 *
 * Assertivas de saída:
 *  -O tipo de produto contido em type será equivalente ao tipo de produto
 * representado por number.
 *
 * Assertivas estruturais:
 *  -Um estrutura de dados do tipo productType equivale a "Rental", "Sale",
 * "Service" ou "All".
 *
 * Assertivas de contrato:
 *  -A função sobrescreverá o tipo de produto contido no endereço type com o
 * tipo de produto obtido na conversão do inteiro number para um tipo de
 * produto.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo productType alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ConvertIntToProductType(int number, productType *type) {

  if(type == NULL)
    return -1;

  switch (number) {

    case 0:
      *type = Rental;
      break;

    case 1:
      *type = Sale;
      break;

    case 2:
      *type = Service;
      break;

    /*
      Utiliza-se o tipo "All" caso não seja possível identificar o tipo do
      produto. Note que, pelo fato de um produto não poder ser instaciado com o
      tipo "All", qualquer número inválido utilizado para geração de tipo fará
      com que não seja possível a geração de um produto, neutralizando erros de
      gravação/carregamento de produtos e de inputs de usuários.
     */

    default:
      *type = All;

  }

  return 0;

}

/**
 * @fn int ValidName(char name[75])
 * @brief Função que verifica se um nome é válido.
 * @param name Nome testado.
 * @return A função retorna um inteiro: 1 se o nome é válido e 0 se o nome é
 * inválido.
 *
 * Verifica se um nome não contém o caractere reservado '|'.
 *
 * Assertivas de entrada:
 *  Nenhuma.
 *
 * Assertivas de saída:
 *  Nenhuma.
 *
 * Assertivas estruturais:
 *  Nenhuma.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se o nome passado como
 * parâmetro pode ser usado como nome de produto ou não.
 *
 * Requisitos:
 *  Nenhum.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidName(char name[75]) {

  /*
    O nome de um produto não pode conter o caractere '|', pois este é utilizado
    como separador entre os campos de um produto na gravação dos produtos no
    banco de dados.
   */

  if(strchr(name, '|') == NULL)
    return 1;

  else
    return 0;

}

/**
 * @fn int ValidPrice(double price)
 * @brief Função que verifica se um preço é válido.
 * @param price Preço testado.
 * @return A função retorna um inteiro: 1 se o preço é válido; 0 se o preço é
 * inválido.
 *
 * Verifica se um preço está contido no intervalo de preços válidos definido
 * previamente.
 *
 * Assertivas de entrada:
 *  Nenhuma.
 *
 * Assertivas de saída:
 *  Nenhuma.
 *
 * Assertivas estruturais:
 *  Nenhuma.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se o preço passado como
 * argumento pode ser usado como preço de produto ou não.
 *
 * Requisitos:
 *  Nenhum.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidPrice(double price) {

  /* Um produto não pode ter seu preço negativo ou maior que 1.000.000,00. */

  if(price > 0 && price <= 1000000)
    return 1;

  else
    return 0;

}

/**
 * @fn int ValidPopularity(int popularity)
 * @brief Função que verifica se uma popularidade é válida.
 * @param popularity Popularidade testada.
 * @return A função retorna um inteiro: 1 se a popularidade é válida e 0 se a
 * popularidade é inválida.
 *
 * Verifica se uma popularidade está contido no intervalo de popularidades
 * válidas definido previamente.
 *
 * Assertivas de entrada:
 *  Nenhuma.
 *
 * Assertivas de saída:
 *  Nenhuma.
 *
 * Assertivas estruturais:
 *  Nenhuma.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se a popularidade passada como
 * argumento pode ser usada como popularidade de produto ou não.
 *
 * Requisitos:
 *  Nenhum.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidPopularity(int popularity) {

  /* Um produto não pode ter sua popularidade negativa ou maior que 100. */

  if(popularity >= 0 && popularity <= 100)
    return 1;

  else
    return 0;

}

/**
 * @fn int ValidProduct(product *item)
 * @brief Função que verifica se um produto é válido.
 * @param item Endereço do produto que será testado. Argumento passado por
 * referência.
 * @return A função retorna um inteiro: 1 se o produto é válido; 0 se o produto
 * é inválido.
 *
 * Verifica se um produto contém os parâmetros nome, preço, tipo e popularidade
 * válidos conforme métricas definidas previamente. Faz-se isso passando-se o
 * nome, o preço e a popularidade do produto para as funções ValidName,
 * ValidPrice e ValidPopularity, respectivamente, e verificando-se se o tipo do
 * produto é diferente de "All".
 *
 * Assertivas de entrada:
 *  -O parâmetro item deve ser diferente de NULL.
 *  -O parâmetro item deve apontar para uma estrutura de dados do tipo
 * product.
 *
 * Assertivas de saída:
 *  -Os parâmetros do produto no endereço item permanecerão inalterados.
 *
 * Assertivas estruturais:
 *  -Uma estrutura de dados product possui como membros um vetor de chars para
 * seu nome, uma estrutura de dados do tipo productType para seu tipo, um double
 * para seu preço e um int para sua popularidade.
 *
 * Assertivas de contrato:
 *  -A função retornará um inteiro representando se o produto cujo endereço foi
 * passado como argumento contém os membros válidos ou não ou se o argumento
 * fornecido à função ValidProduct é inválido.
 *
 * Requisitos:
 *  -Uma estrutura de dados do tipo product alocada estaticamente.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 */

int ValidProduct(product *item) {

  if(item == NULL)
    return -1;

  else if(ValidPrice(item->price) && ValidPopularity(item->popularity)
          && item->type != All && ValidName(item->name))
    return 1;

  else
    return 0;

}
