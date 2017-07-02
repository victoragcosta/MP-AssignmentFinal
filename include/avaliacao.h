
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
 * @enum avaliacao_condRet
 * @brief Condições de retorno para as funções do módulo, significados definidos nas funções que os retornam
*/

typedef enum {
  AVALIACAO_SUCESSO,
  AVALIACAO_FALHA_SEMSESSAO,
  AVALIACAO_FALHA_USUARIOS,
  AVALIACAO_FALHA_AUTOAVALIACAO,
  AVALIACAO_FALHA_NOTAINVALIDA,
  AVALIACAO_FALHA_CRIARDB,
  AVALIACAO_FALHA_FREE,
  AVALIACAO_FALHA_ABRIRDB,
  AVALIACAO_VALORINVALIDO,
  AVALIACAO_FALHA_DEFINIR,
  AVALIACAO_FALHA_AVALIAR,
  AVALIACAO_NAO_ENCONTRADO
} avaliacao_condRet;

/*!
 * @enum avaliacao_tipo
 * Enumeração de tipos de usuário no que tange avaliação
*/
typedef enum {
  AVALIADOR, /**< Busca por avaliações em que o usuário é o avaliador */
  AVALIADO /**< Busca por avaliações em que o usuário é o avaliado */
} avaliacao_tipo;

/*!
 * @typedef avaliacao
 * @brief Estrutura de dados de uma avaliação
*/

typedef struct avaliacao {
  unsigned int identificador; /**< Id da avaliação */
  unsigned int avaliador; /**< Id do avaliador no grafo de usuários */
  unsigned int avaliado; /**< Id do avaliado no grafo de usuários */
  unsigned int nota; /**< Nota atribuída pelo avaliador ao avaliado */
  char comentario[AVALIACAO_LIMITE_COMENTARIO];  /**< Comentário feito pelo avaliador ao avaliado */
} avaliacao;

/*!
  * @typedef reclamacao DEPRECATED
*/
typedef struct reclamacao {
  unsigned int reclamador;
  unsigned int reclamado;
  char comentario[AVALIACAO_LIMITE_COMENTARIO];
} reclamacao;

/*!
 * @brief Lista de avaliações DEPRECATED
*/
typedef struct avaliacao_vetor {
  unsigned int length;
  avaliacao **array;
} avaliacao_vetor;

/*!
 * @brief Protótipos das funções
*/

avaliacao_condRet avaliacao_fazerAvaliacao(avaliacao *);
avaliacao *avaliacao_iniciar();
avaliacao_condRet avaliacao_definir(avaliacao *, const char *, ...);
avaliacao_condRet avaliacao_limpar(avaliacao **);
avaliacao_condRet avaliacao_listar(unsigned int);
avaliacao_condRet avaliacao_pegarContador();
avaliacao_condRet avaliacao_obterAvaliacao(unsigned int, unsigned int, avaliacao_tipo, avaliacao *);
avaliacao_condRet avaliacao_avaliar(unsigned int, unsigned int, unsigned int, char *);

#endif


