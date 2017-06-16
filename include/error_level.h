// Módulo de retorno - Cabeçalho.

#ifndef ERROR_LEVEL_H_
#define ERROR_LEVEL_H_

/**
 * @enum errorLevel
 * @brief Contém possíveis retornos para funções.
 *
 * Deve ser utilizado como retorno para funções que causem exclusivamente
 * "efeitos colaterais" e que podem falhar.
 */

typedef enum {
  Success,  /**< A função funcionou adequadamente. */
  Failure,  /**< A função não funcionou adequadamente. */
  Illegal_argument /**< Os parâmetros passados para a função são ilegais. */
}errorLevel;

#endif  // ERROR_LEVEL_H_
