#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/grafo.h"

/*!
 * @brief Mostra um log que combina com o log do gtest 
 *
 * Recebe como parâmetros o tipo, uma string que ficará no início do log, 
 * o texto a ser mostrado do log 
 * e a cor da região com o tipo, usando as definições de grafo.h
 * 
 * @code
 * print_log("TEST", "Log de teste", COR_VERDE);
 * @endcode
 */
void print_log(const char *tipo, const char *texto, const char *COR)
{
	char *tipo_s = (char *)calloc(11, sizeof(char));
	unsigned int padding = (10-strlen(tipo))/2;
	for(unsigned int i=0; i < 10; i++) tipo_s[i] = ' ';
	for(unsigned int i=padding; i<10-padding; i++) if(tipo[i-padding] != '\0') tipo_s[i] = tipo[i-padding];
	tipo_s[10] = '\0';
	printf("%s[%s]%s %s\n", COR, tipo_s, COR_NORMAL, texto);
  free(tipo_s);
}

/*!
 * A função cria um grafo e retorna um ponteiro para a estrutura 
 * contendo o nome e o endereco do primeiro nó
 * 
 * Pelas definições de grafo.h o tamanho máximo para a string nome é
 * @code grafo_nome_tamanho @endcode
*/
grafo *cria_grafo(const char *nome)
{
	grafo *novo = (grafo *)calloc(1, sizeof(grafo));
	if(novo == NULL) {
		print_log("ERRO", "Não foi possível alocar memória para o grafo", COR_VERMELHO);
		return NULL;
	}
	else {
		unsigned int N = strlen(nome);
		if(N > grafo_nome_tamanho) N = grafo_nome_tamanho;
		strncpy(novo->nome, nome, N);
		novo->raiz = NULL;
		novo->ultimo = NULL;
		print_log("SUCESSO", "O grafo foi gerado", COR_VERDE);
	}
	return novo;
}

/*!
 * Retorna o nome do grafo 
*/
char *retorna_nome_grafo(grafo *G)
{
	if(G == NULL) return NULL;
	return G->nome;
}

/*!
 * Função verificadora de grafo, verifica se o grafo tem raiz, tem último elemento
 * e se é diferente de NULL
*/
int grafo_verificador(grafo *G)
{
	if(G == NULL || G->raiz == NULL || G->ultimo == NULL) return 1;
	return 0;	
}

/*!
 * Função percorredora 
 * 
 * Percorre o grafo de acordo com uma condição de parada para o vértice x
 * 
 * Recebe como parâmetro o endereço de um nodo, um inteiro x, uma função que indica
 * a condição de retorno e outra que indica a condição de parada do percorrimento
 *
 * @code
 * grafo_percorre((void *)G->raiz->acesso_arco, 5, grafo_busca_arco_retorno, grafo_busca_arco_parada);
 * @endcode
 * 
 * Vai buscar os arcos que saem de raiz até encontrar um arco que leve a um vértice
 * de valor 5.
 * 
 * A função grafo_percorre é geral de tal maneira que deve-se fazer um cast no 
 * G->raiz->acesso_arco pois essa entrada pode ser de qualquer tipo. O tratamento
 * adequado tipo a tipo é feito de acordo com as funções passadas como terceiro e 
 * quarto argumentos. Neste caso foram usadas as funções grafo_busca_arco_retorno, que
 * verifica se o valor do vértice levado pelo arco é igual a 5, e 
 * grafo_busca_arco_parada, que verifica se o próximo arco é diferente de NULL para que
 * o loop continue.
*/
void *grafo_percorre(void *tmp, int x, int f_retorno(void *tmp, int x), int f_parada(void **tmp))
{
	do
	{
		if(f_retorno(tmp, x)) return tmp;
	} while(f_parada(&tmp));	
	return NULL;
}

/*!
 * @brief Condição de retorno para grafo_busca_no com offset -1 
 *
 * Verifica se o próximo nó da lista de nós é diferente de NULL e
 * se o valor do próximo nó é o procurado x
*/
int grafo_busca_no_retorno_offset(void *tmp, int x)
{
	return ((grafo_no *)tmp)->prox_no != NULL && ((grafo_no *)((grafo_no *)tmp)->prox_no)->valor == x;
}

/*!
 * @brief Condição de retorno para grafo_busca_no com offset 0 
 *
 * Verifica se o valor do nó corrente é o esperado x
*/
int grafo_busca_no_retorno(void *tmp, int x)
{
	return ((grafo_no *)tmp)->valor == x;
}

/*!
 * @brief Condição de parada para grafo_busca_no
 * 
 * Caso o próximo nó seja NULL ele para, além disso, por receber **tmp, ele
 * faz o procedimento de pular para o próximo nó da lista
*/
int grafo_busca_no_parada(void **tmp)
{
	return ((grafo_no *)(*tmp))->prox_no != NULL && (*tmp = ((grafo_no *)(*tmp))->prox_no);
}

/*!
 * @brief Função que busca um nó a partir de seu identificador x
 *
 * O offset é útil caso se deseje obter um nó anterior ao nó x
 * bastando passar -1, no momento há apenas duas opções para offset: 0 e -1 
*/
grafo_no *grafo_busca_no(grafo *G, int x, int offset)
{
	if(grafo_verificador(G)) return NULL;
	void *tmp = G->raiz;
	return (grafo_no *) grafo_percorre(tmp, x, (offset)?grafo_busca_no_retorno_offset:grafo_busca_no_retorno, grafo_busca_no_parada);
}

/*! 
 * @brief Condição de retorno para grafo_busca_arco 
 * 
 * Caso o valor do nó acessado pelo arco corrente for o esperado y, ele retorna verdade.
*/
int grafo_busca_arco_retorno(void *tmp, int y)
{
	return ((grafo_no *)((grafo_arco *)tmp)->acesso_adjacente)->valor == y;
}

/*!
 * @brief Condição de parada para grafo_busca_arco 
 * 
 * Caso se chegue ao fim da lista de arcos de um nó paramos,
 * a função também faz o pulo para o próximo arco, por isso recebe **tmp
*/
int grafo_busca_arco_parada(void **tmp)
{
	return ((grafo_arco *)(*tmp))->prox_arco != NULL && (*tmp = (grafo_arco *)((grafo_arco *)(*tmp))->prox_arco);
}

/*!
 * @brief Análogo ao grafo_busca_arco, mas busca um arco que vai de x a y 
*/
grafo_arco *grafo_busca_arco(grafo *G, int x, int y)
{
	if(grafo_verificador(G)) return NULL;
	
	grafo_no *X = grafo_busca_no(G, x, 0);
	if(X == NULL) return NULL;
	
	grafo_arco *tmp = (grafo_arco *)X->acesso_arco;
	if(tmp == NULL) return NULL;
	
	return (grafo_arco *)grafo_percorre(tmp, y, grafo_busca_arco_retorno, grafo_busca_arco_parada);
}

/*!
 * @breif Função para adicionar um vértice de indentificador x no grafo G
*/
grafo_cte adiciona_vertice(grafo *G, int x)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	grafo_no *novo = (grafo_no *)calloc(1, sizeof(grafo_no));
	if(novo == NULL) return FALHA_ALOCAR;
	novo->valor = x;
	novo->usado = (char)0;
	novo->prox_no = NULL;
	novo->acesso_arco = NULL;
	novo->acesso_ultimo_arco = NULL;
	novo->dados = NULL;
	
	if(G->raiz == NULL) G->raiz = (void *)novo;
	else if(G->ultimo != NULL)
	{
		if(grafo_busca_no(G, x, 0) != NULL) {
			free(novo);
			return FALHA_VERTICES_IGUAIS;
		}
		((grafo_no *)G->ultimo)->prox_no = (void *)novo;
	}
	else {
		free(novo);
		return CORROMPIDO;
	}
	
	G->ultimo = (void *)novo;
	return SUCESSO;
}

/*!
 * @brief Função para adicionar aresta que vai do vértice x ao y no grafo
*/
grafo_cte adiciona_aresta(grafo *G, int x, int y)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	grafo_no *X = grafo_busca_no(G,x,0);
	grafo_no *Y = grafo_busca_no(G,y,0);
		
	if(X == NULL || Y == NULL) return FALHA_VERTICE_NULO;
	if(X == Y) return FALHA_VERTICES_IGUAIS;
	
	grafo_arco *novo = (grafo_arco *)calloc(1, sizeof(grafo_arco));
	if(novo == NULL) return FALHA_ALOCAR;
	novo->valor = 0;
	novo->usado = (char)0;
	novo->prox_arco = NULL;
	novo->acesso_adjacente = (void *)Y;
	
	if(X->acesso_arco == NULL) X->acesso_arco = novo;
	else if(X->acesso_ultimo_arco != NULL)
	{
		((grafo_arco *)X->acesso_ultimo_arco)->prox_arco = (void *)novo;
	}
	else {
		free(novo);
		return CORROMPIDO;
	}
	
	X->acesso_ultimo_arco = novo;
	
	return SUCESSO;
}

/*!
 * @brief Remove uma aresta pelo endereço de memória do nó ao qual ela sai e do identificador
   do nó para onde ela vai 
*/
grafo_cte remove_aresta_end(grafo *G, grafo_no *X, int y)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	if(X == NULL) return FALHA_VERTICE_NULO;
	if(X->valor == y) return FALHA_VERTICES_IGUAIS;
	
	if(X->acesso_arco == NULL) return FALHA_ARCO_NULO;
	
	grafo_arco *tmp = (grafo_arco *)X->acesso_arco;
	grafo_arco *tmp_anterior = NULL;
	
	if(tmp == NULL) return FALHA_ARCO_INEXISTE;
	do
	{
		if(tmp->acesso_adjacente == NULL) return CORROMPIDO;
		else if(((grafo_no *)tmp->acesso_adjacente)->valor == y)
		{
			if(tmp_anterior != NULL) tmp_anterior->prox_arco = tmp->prox_arco;
			else X->acesso_arco = (grafo_arco *)tmp->prox_arco;
			free(tmp);
			return SUCESSO;
		}
		tmp_anterior = tmp;
	} while(tmp->prox_arco != NULL && (tmp = (grafo_arco *)tmp->prox_arco));
	
	return FALHA_ARCO_INEXISTE;
}

/*!
 * @brief Remove uma aresta a partir dos identificadores x e y 
*/
grafo_cte remove_aresta(grafo *G, int x, int y)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	if(x == y) return FALHA_VERTICES_IGUAIS;
	
	return remove_aresta_end(G, grafo_busca_no(G,x,0),y);
}

/*!
 * @brief Remove um vértice a partir de seu endereço 
*/
grafo_cte remove_vertice_end(grafo *G, grafo_no *X)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	if(X == NULL) return FALHA_VERTICE_NULO;
	
	grafo_arco *tmp;
	while(X->acesso_arco != NULL) 
	{
		tmp = (grafo_arco *)X->acesso_arco;
		X->acesso_arco = (void *)tmp->prox_arco;
		free(tmp);
	}
	
	grafo_no *tmp_no = (grafo_no *)G->raiz;
	grafo_no *tmp_no_anterior = NULL;
	
	if(G->raiz == (void *)X) G->raiz = X->prox_no;
	else {
		do
		{
			if(tmp_no != X) remove_aresta_end(G, tmp_no, ((grafo_no *)X)->valor);
			if(tmp_no == X) {
				if(tmp_no_anterior != NULL) tmp_no_anterior->prox_no = (void *)X->prox_no;
				else return CORROMPIDO;
			}
		} while(tmp_no->prox_no != NULL && (tmp_no = (grafo_no *)tmp_no->prox_no) && (tmp_no_anterior = tmp_no));
	}
	
	if(G->ultimo == (void *)X) G->ultimo = (void *)tmp_no_anterior;
	
	free(X->dados);
	free(X);
	return SUCESSO;
}

/*!
 * @brief Remove um vértice a partir de seu identificador x 
*/
grafo_cte remove_vertice(grafo *G, int x)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	grafo_no *X = grafo_busca_no(G, x, 0);
	return remove_vertice_end(G, X);
}

/*!
 * @brief Mostra se dois nós de identificadores x e y são adjacentes 
*/
grafo_cte adjacente(grafo *G, int x, int y)
{
	if(grafo_busca_arco(G, x, y) == NULL) return NADJACENTES;
	else return ADJACENTES;
}

/*!
 * @brief Insere um nó em uma lista de nós
*/
grafo_cte grafo_lista_no_inserir(grafo_lista_no **raiz, int valor)
{
	grafo_lista_no *novo = (grafo_lista_no *)calloc(1, sizeof(grafo_lista_no));
	if(novo == NULL) {
    free(novo);
    return FALHA_ALOCAR;
  }
	novo->prox_no = NULL;
	novo->valor = valor;
	
	if(*raiz == NULL) *raiz = novo;
	else
	{
		grafo_lista_no *tmp = *raiz;
		while(tmp->prox_no != NULL) tmp = (grafo_lista_no *)tmp->prox_no;
		tmp->prox_no = novo;
	}
	return SUCESSO;
}

grafo_cte grafo_lista_no_limpar(grafo_lista_no **raiz){
  grafo_lista_no *tmp = *raiz, *tmp_prox;
  while(tmp != NULL) {
    tmp_prox = (grafo_lista_no *)tmp->prox_no;
    free(tmp);
    tmp = tmp_prox;
  }
  *raiz = NULL;
  return SUCESSO;
}

/*!
 * @brief Verifica os nós vizinhos a x retornando uma lista de nós 
*/
grafo_lista_no *vizinhos(grafo *G, int x)
{
	grafo_no *X = grafo_busca_no(G, x, 0);
	grafo_lista_no *lista = NULL;
	
	grafo_arco *tmp = (grafo_arco *)X->acesso_arco;
	while(tmp != NULL) 
	{
		grafo_lista_no_inserir(&lista, ((grafo_no *)tmp->acesso_adjacente)->valor);
		tmp = (grafo_arco *)tmp->prox_arco;
	}
	return lista;
}

/*!
 * @brief Retorna o valor do vértice de identificador x 
*/
void *retorna_valor_vertice(grafo *G, int x)
{
	grafo_no *X = grafo_busca_no(G, x, 0);
	if(X == NULL) return NULL;
	return X->dados;
}

/*!
 * @brief Muda o valor do vértice de identificador x para o valor v 
*/
grafo_cte muda_valor_vertice(grafo *G, int x, void *v)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	grafo_no *X = grafo_busca_no(G, x, 0);
	if(X == NULL) return FALHA_VERTICE_NULO;
	X->dados = v;
	return SUCESSO;
}

/*!
 * @brief Retorna o valor da aresta que vai de x a y 
*/
int retorna_valor_aresta(grafo *G, int x, int y)
{
	grafo_arco *A = grafo_busca_arco(G, x, y);
	if(A == NULL) return 0;
	return A->valor;
}

/*!
 * @brief Muda o valor da aresta que vai de x a y com o valor v
*/
grafo_cte muda_valor_aresta(grafo *G, int x, int y, int v)
{
	if(G == NULL) return FALHA_GRAFO_NULO;
	grafo_arco *A = grafo_busca_arco(G, x, y);
	if(A == NULL) return FALHA_ARCO_NULO;
	A->valor = v;
	return SUCESSO;
}

/*!
 * @brief Destroi grafo G 
*/
grafo_cte destroi_grafo(grafo **G)
{
	if(*G == NULL) return FALHA_GRAFO_NULO;
	grafo_cte a;
	while((*G)->raiz != NULL) 
	{
		a = remove_vertice_end(*G, ((grafo_no *)(*G)->raiz));
		if(a != SUCESSO) return a;
	}
	free(*G);
	*G = NULL;
	return SUCESSO;
}
