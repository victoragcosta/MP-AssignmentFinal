// Módulo de índice válido.

/**
 * @file valid_index.c
 * @brief Implementação do módulo de índice válido.
 */

#include "valid_index.h"

/**
 * @fn ValidIndex (int index, int list_size)
 * @brief Função que verifica se um índice para um vetor é válido.
 * @param index Índice testado.
 * @param list_size Tamanho do vetor no qual o índice é testado.
 * @return A função retorna um inteiro: 1 se o índice é válido; 0 se o índice é
 * inválido.
 *
 * Verifica se um índice passado como parâmetro para função pode ser utilizado
 * como índice válido para acessar um vetor cujo tamanho é fornecido como
 * parâmetro.
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
 *  -A função retornará um inteiro representando se o índice fornecido pode ser
 * utilizado para acessar um dos membros do vetor cujo tamanho é fornecido.
 *
 * Requisitos:
 *  Nenhum.
 *
 * Hipóteses:
 *  Nenhuma.
 *
 * Interface:
 *  valid_index(int index, int list_size) => int return
 *
 * Items da interface explícita:
 *
 *  -Recebe dados:
 *    -index: Índice testado.
 *    -list_size: Tamanho do vetor no qual o índice é testado.
 *
 *  -Produz resultados:
 *    -return: A função retorna um inteiro: 1 se o índice é válido; 0 se o
 *  índice é inválido.
 *
 * Items da interface implícita:
 *  Nenhum.
 *
 */

int ValidIndex (int index, int list_size) {

  /*
    Um índice deve ser positivo e menor que o tamanho da lista, pois, do
    contrário, ele acessaria uma área da memória fora do vetor da lista.
   */

  if(index >= 0 && index < list_size)
    return 1;

  else
    return 0;

}
