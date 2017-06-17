#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avaliacao.h"
#include "usuarios.h"

/*!
 * @brief Função que avalia um usuário
 *
 * Necessita de sessão aberta
 *
 * Modo de uso:
 * @code
 * avaliacao_fazerAvaliacao(5, 4, "Bom serviço");
 * @endcode
 * O usuário da sessão avalia o usuário 5 com nota 4 e comentando "Bom serviço".
 *
 * A nota deve ser um inteiro de 0 a 5
 *
 * O comentário não deve exceder 200 caracteres (incluindo '\0')
*/
avaliacao_condRet avaliacao_fazerAvaliacao(unsigned int identificadorAvaliado, unsigned int nota, char *comentario){
  unsigned int identificadorAvaliador, n_avaliacao;
  double avaliacao;
  FILE *db_avaliacao;
  /* Verificamos se há uma sessão */
  if(!usuarios_sessaoAberta()) return AVALIACAO_FALHA_SEMSESSAO;
  
  /* Evitamos autoavaliação */
  if(usuarios_retornaDados(0, "identificador", (void *)&identificadorAvaliador) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  if(identificadorAvaliador == identificadorAvaliado) return AVALIACAO_FALHA_AUTOAVALIACAO;
  
  /* Verificamos o intervalo da nota */
  if(nota > 5) return AVALIACAO_FALHA_NOTAINVALIDA;
  
  /* Obtemos os dados iniciais */
  if(usuarios_retornaDados(identificadorAvaliado, "n_avaliacao", (void *)&n_avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  if(usuarios_retornaDados(identificadorAvaliado, "avaliacao", (void *)&avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  
  /* Calculamos a nova avaliação e atualizamos no grafo de usuários */
  avaliacao = (double)(n_avaliacao*avaliacao+nota)/(++n_avaliacao);
  if(usuarios_atualizarDados(identificadorAvaliado, "n_avaliacao", n_avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  if(usuarios_atualizarDados(identificadorAvaliado, "avaliacao", avaliacao) != USUARIOS_SUCESSO) return AVALIACAO_FALHA_USUARIOS;
  
  /* Salvamos no banco de dados, cria-se um caso não haja */
  db_avaliacao = fopen(AVALIACAO_DB, "a+");
  if(db_avaliacao == NULL) return AVALIACAO_FALHA_CRIARDB;
  
  fprintf(db_avaliacao, AVALIACAO_DB_ESTRUTURA, identificadorAvaliador, identificadorAvaliado, nota, comentario);
  
  fclose(db_avaliacao);
  
  return AVALIACAO_SUCESSO;
  
}
