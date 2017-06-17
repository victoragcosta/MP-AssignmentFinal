/*!
 * @brief Header das estruturas de usuário
*/

#ifndef HEADER_AVALIACAO
#define HEADER_AVALIACAO

/*!
 * @brief Estrutura do banco de dados
 *
 * ID AVALIADOR | ID AVALIADO | NOTA | COMENTÁRIO
*/

#define AVALIACAO_DB "../../db/avaliacao.txt"
#define AVALIACAO_DB_ESTRUTURA "%-4u\t%-4u\t%-4u\t%-200s\n"
#define AVALIACAO_LIMITE_INT 4
#define AVALIACAO_LIMITE_COMENTARIO 200

/*!
 * @brief Condições de retorno para as funções do módulo
*/

typedef enum {
  AVALIACAO_SUCESSO,
  AVALIACAO_FALHA_SEMSESSAO,
  AVALIACAO_FALHA_USUARIOS,
  AVALIACAO_FALHA_AUTOAVALIACAO,
  AVALIACAO_FALHA_NOTAINVALIDA,
  AVALIACAO_FALHA_CRIARDB
} avaliacao_condRet;

/*!
 * @brief Protótipos das funções
*/
avaliacao_condRet avaliacao_fazerAvaliacao(unsigned int, unsigned int, char *);

#endif


