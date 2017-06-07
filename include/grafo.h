#define grafo_nome_tamanho 20
#define COR_NORMAL	"\x1B[0m"
#define COR_VERMELHO	"\x1B[31m"
#define COR_VERDE	"\x1B[32m"
#define COR_AMARELO	"\x1B[33m"
#define COR_AZUL	"\x1B[34m"
#define COR_MAGENTA	"\x1B[35m"
#define COR_CYAN	"\x1B[36m"
#define COR_BRANCO	"\x1B[37m"

/*!
 * @brief Condições de retorno para as funções da biblioteca grafo
*/
typedef enum
{
	ADJACENTES,
	NADJACENTES,
	SUCESSO,
	FALHA,
	FALHA_GRAFO_NULO,
	FALHA_VERTICE_NULO,
	FALHA_VERTICES_IGUAIS,
	FALHA_ARCO_NULO,
	FALHA_ALOCAR,
	FALHA_ARCO_INEXISTE,
	CORROMPIDO
} grafo_cte;

/*!
 * @brief Estrutura de um nó do grafo
*/
typedef struct
{
	int valor;
	char usado;
	void *prox_no;
	void *acesso_arco;
	void *acesso_ultimo_arco; /* Último arco, evita percorrimento */
	void *dados; /* Valor propriamente dito da estrutura */
} grafo_no;

/*!
 * @brief Estrutura de um arco do grafo
*/
typedef struct
{
	int valor;
	char usado;
	void *prox_arco;
	void *acesso_adjacente;
} grafo_arco;

/*!
 * @brief Estrutura da cabeça de um grafo
*/
typedef struct 
{
	char nome[grafo_nome_tamanho];
	void *raiz; /* Primeiro nó */
	void *ultimo; /* Último nó, evita percorrimento */
} grafo;

/*!
 * @brief Estrutura de uma lista de nós
*/
typedef struct
{
	void *prox_no;
	int valor;
} grafo_lista_no;

grafo_cte grafo_lista_no_inserir(grafo_lista_no **, int);

void grafo_string_aleatoria(char **, unsigned int);
unsigned int grafo_conta_string(const char *);
void print_log(const char *, const char *, const char *);
grafo_cte remove_aresta_end(grafo *, grafo_no*, int);
grafo_cte remove_vertice_end(grafo *, grafo_no *);
int grafo_verificador(grafo *);
void *grafo_percorre(void *, int, int (void *, int), int (void **));

grafo_no *grafo_busca_no(grafo *, int, int);
int grafo_busca_no_retorno_offset(void *, int);
int grafo_busca_no_retorno(void *, int);
int grafo_busca_no_parada(void **);

grafo_arco *grafo_busca_arco(grafo *, int, int);
int grafo_busca_arco_retorno(void *, int);
int grafo_busca_arco_parada(void **);

grafo *cria_grafo(const char *);
char *retorna_nome_grafo(grafo *);
grafo_cte destroi_grafo(grafo **);
grafo_cte adjacente(grafo *, int, int);
grafo_lista_no *vizinhos(grafo *, int);
grafo_cte adiciona_vertice(grafo *, int);
grafo_cte remove_vertice(grafo *, int);
grafo_cte adiciona_aresta(grafo *, int, int);
grafo_cte remove_aresta(grafo *, int, int);
void *retorna_valor_vertice(grafo *, int);
grafo_cte muda_valor_vertice(grafo *, int, void *);
int retorna_valor_aresta(grafo *, int, int);
grafo_cte muda_valor_aresta(grafo *, int, int, int);
