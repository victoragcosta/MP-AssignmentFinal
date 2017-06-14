#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "aleatorio.h"
#include "usuarios.h"
#include "grafo.h"

/*!
 * @brief Grafo de usuários
*/
static grafo *usuarios_grafo = NULL; /* Grafo de usuários */
static unsigned int usuarios_contador = 0; /* Contador de usuários no grafo */
static unsigned int usuarios_identificador_max = 0; /* Contador do maior id de usuário no grafo */

/*!
 * @brief Sessão aberta
*/
static tpUsuario *usuarios_sessao = NULL; /* Inicialmente NULL significa que não há usuário logado */

/*!
 * @brief Estrutura de usuário temporário para uso do usuarios_args nas funções
*/
static tpUsuario *usuarios_dadosTemp = (tpUsuario *)malloc(sizeof(tpUsuario));

/*!
 * @brief Argumentos padrão aceitáveis pelas funções ao buscar/alterar/definir dados de usuário
*/
static unsigned int usuarios_cadastro_argumentos_n = 5;

static usuarios_cadastro_argumentos usuarios_args[] = {
	{.validos = "usuario", .tamanho = USUARIOS_LIMITE_USUARIO, .destino = usuarios_dadosTemp->usuario},
	{.validos = "nome", .tamanho = USUARIOS_LIMITE_NOME, .destino = usuarios_dadosTemp->nome},
	{.validos = "email", .tamanho = USUARIOS_LIMITE_EMAIL, .destino = usuarios_dadosTemp->email},
	{.validos = "senha", .tamanho = USUARIOS_LIMITE_SENHA, .destino = usuarios_dadosTemp->senha},
	{.validos = "endereco", .tamanho = USUARIOS_LIMITE_ENDERECO, .destino = usuarios_dadosTemp->endereco}
};

/*!
 * @brief Copiamos os dados de uma lista de argumentos para usuarios_dadosTemp
*/
void usuarios_copiarDadosTemp(unsigned int n, va_list argumentos){
	unsigned int i=0,j;
	char *argumento;
	for(;i<n;i++){
		argumento = va_arg(argumentos, char *);
		for(j=0;j<usuarios_cadastro_argumentos_n;j++)
			if(!strcmp(argumento, usuarios_args[j].validos)) strncpy(usuarios_args[j].destino, va_arg(argumentos, char *), usuarios_args[j].tamanho);
		
		/* Casos especiais diferentes de char * */
		if(!strcmp(argumento, "formaPagamento")) 
			usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(argumentos, int);
		if(!strcmp(argumento, "tipo")) 
			usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(argumentos, int);
	}
}

/*!
 * @brief Função que verifica se há repetição nos dados
 * 
 * A função busca no grafo de usuários se já há algum usuário com o dado
 * igual ao do argumento passado
 * 
 * @code
 * usuarios_verificaRepeticao("nome", "João Antônio");
 * @endcode
 * Vai retornar USUARIOS_DADOS_REPETICAO caso já haja um usuário com este nome
 * e USUARIOS_DADOS_OK caso contrário.
 *
 * Observação, a verificação de nome ignora se o caracter é caixa alta ou não
 
*/
static usuarios_condRet usuarios_verificaRepeticao(const char *argumento, char *dado){
	unsigned int i = 0; /* Contador dos nós */
	tpUsuario *informacao;
	
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	/* Buscamos por um usuario igual */
	if(!strcmp(argumento, "usuario")) {
		for(i=0;i<usuarios_contador;i++){
			informacao = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
			/* Asertiva */
			if(informacao == NULL) return USUARIOS_GRAFO_CORROMPIDO;
			
			/* São iguais */ 
			//printf("'%s' == '%s'\n", informacao->usuario, dado);
			if(!strcmp(informacao->usuario, dado)) return USUARIOS_DADOS_REPETICAO;
		}
		return USUARIOS_DADOS_OK;
	}
	
	/* Buscamos por um email igual (REPETIÇÃO DE CÓDIGO) */
	if(!strcmp(argumento, "email")) {
		for(i=0;i<usuarios_contador;i++){
			informacao = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
			/* Asertiva */
			if(informacao == NULL) return USUARIOS_GRAFO_CORROMPIDO;
			
			/* São iguais */ 
			//printf("'%s' == '%s'\n", informacao->email, dado);
			if(!strcmp(informacao->email, dado)) return USUARIOS_DADOS_REPETICAO;
		}
		return USUARIOS_DADOS_OK;
	}
	
	return USUARIOS_ARGUMENTOINVALIDO;
}

/*!
 * @brief Função leitora de string em um arquivo de dados
*/
static void usuarios_lerString(FILE *arquivo, char *dstStr, unsigned int limite){
	unsigned int i = 0, espaco = 0;
	char caracter;
	
	while (
		!feof(arquivo) && \
		(caracter = fgetc(arquivo)) != '\t' && \
		caracter != '\n' && \
		i < limite - 1
	) {
		/* Controle para evitar strings cheias de espaços no final */
		if(caracter != ' ') espaco = i; 
		dstStr[i++] = caracter;
	}
		
	dstStr[espaco+1] = '\0';
	
	/* Se o próximo não for \t ou \n voltamos um byte */
	if((caracter = fgetc(arquivo)) != '\t' && caracter != '\n')
		fseek(arquivo, -1, SEEK_CUR);
	
}

/*!
 * @brief Função carregadora do arquivo 
 * de usuários e suas relações
 *
 * A relação de um usuário com o outro é a relação de amizade, 
 * o grafo é direcionado, assim a relação entre A e B 
 * de fato existe se e só se existir uma aresta
 * indo de A a B e outra indo de B a A.
 * Se isso não ocorrer temos a pendencia de uma relação, na qual
 * aguarda-se a confirmação da parte solicitada para criá-la.
*/

usuarios_condRet usuarios_carregarArquivo(){
	FILE *db_usuarios = fopen(USUARIOS_DB, "r");
	FILE *db_amigos;
		
	/* Cria-se o grafo de usuários */
	usuarios_grafo = cria_grafo("Usuários");
	
	/* Verificamos se o arquivo existe */
	if(db_usuarios == NULL){
		db_usuarios = fopen(USUARIOS_DB, "w");
		fclose(db_usuarios);
		return USUARIOS_SUCESSO;
	}
	
	/* Índice dos usuários carregados (para acesso via funções de grafo) */
	int i = 0;
	
	/* Identificadores para os amigos */
	unsigned int identificador_A, identificador_B;

	/* Dados do usuário corrente */
	tpUsuario *corrente;
	while(!feof(db_usuarios)){
		corrente = (tpUsuario *)malloc(sizeof(tpUsuario));
		
		/* Lemos do arquivo */
		fscanf(db_usuarios, "%u\t", &(corrente->identificador));
		usuarios_lerString(db_usuarios, corrente->usuario, USUARIOS_LIMITE_USUARIO);
		usuarios_lerString(db_usuarios, corrente->nome, USUARIOS_LIMITE_NOME);
		usuarios_lerString(db_usuarios, corrente->email, USUARIOS_LIMITE_EMAIL);
		usuarios_lerString(db_usuarios, corrente->senha, USUARIOS_LIMITE_SENHA);
		usuarios_lerString(db_usuarios, corrente->endereco, USUARIOS_LIMITE_ENDERECO);
				
		fscanf(db_usuarios, "%d\t%d\t%d\t%lf\t%d", 
			(int *)&(corrente->formaPagamento), \
			(int *)&(corrente->tipo), \
			(int *)&(corrente->estado), \
			&(corrente->avaliacao), \
			&(corrente->n_avaliacao)
		);
		
		/*printf("'%d'\n'%s'\n'%s'\n'%s'\n'%s'\n'%s'\n'%d'\n'%d'\n-------------\n", 
			corrente->identificador,  \
			corrente->usuario, \
			corrente->nome, \
			corrente->email, \
			corrente->senha, \
			corrente->endereco, \
			(int)corrente->formaPagamento, \
			(int)corrente->tipo
		);*/
		
		/* Atualizamos o máximo */
		if(corrente->identificador > usuarios_identificador_max)
			usuarios_identificador_max = corrente->identificador;
		
		
		/* Adicionamos ao grafo */
		if(adiciona_vertice(usuarios_grafo, i) != SUCESSO) {
			fclose(db_usuarios);
			free(corrente);
			return USUARIOS_FALHA_ADICIONAR_GRAFO;
		}
		
		/* Definimos o valores correntes no vértice */
		if(muda_valor_vertice(usuarios_grafo, i, (void *)corrente) != SUCESSO) {
			fclose(db_usuarios);
			free(corrente);
			return USUARIOS_FALHA_INSERIR_DADOS;
		}
		
		i++;
		
	}
	
	fclose(db_usuarios);
	
	usuarios_contador = i; /* Número de usuários carregados */
	
	/* Análogo para amigos */
	db_amigos = fopen(USUARIOS_DB_AMIGOS, "r");
	if(db_amigos == NULL){
		db_amigos = fopen(USUARIOS_DB_AMIGOS, "w");
		fclose(db_amigos);
		return USUARIOS_SUCESSO;
	}
	
	/* Agora carregamos os amigos */
	while(!feof(db_amigos)){
		/* Lemos do arquivo */
		fscanf(db_amigos, "%u\t%u\n", &identificador_A, &identificador_B);
		printf("%u %u\n", identificador_A, identificador_B);
		/* Vemos se já há um arco entre eles nesta direção, uma assertiva */
		if(grafo_busca_arco(usuarios_grafo, identificador_A, identificador_B) != NULL){
			fclose(db_amigos);
			return USUARIOS_DB_CORROMPIDO;
		}
		
		if(adiciona_aresta(usuarios_grafo, identificador_A, identificador_B) != SUCESSO){
			fclose(db_amigos);
			return USUARIOS_FALHA_CRIARAMIZADE;
		}
	}
	
	fclose(db_amigos);
	
	return USUARIOS_SUCESSO;
}

/*!
 * @brief Função de cadastro de usuários
 * 
 * Recebe como parâmetros nome, endereço, email, senha repetida duas vezes, forma de 
 * pagamento, tipo de usuário da seguinte maneira:
 * 
 * @code 
 * usuarios_cadastro(8, "usuario", "jose123", "nome", "José Antônio", "email", "joao@antonio.com", "endereco", "Rua Foo Casa Bar", "senha", "123456", "senha_confirmacao", "123456", "formaPagamento", BOLETO, "tipo", CONSUMIDOR);
 * @endcode
 *
 * Assertiva de entrada: o arquivo USUARIOS_DB já existe,
 * isto é a função usuarios_carregarArquivo já foi executada. E devem ser passados o número correto de argumentos
*/

usuarios_condRet usuarios_cadastro(int n, ...){
	FILE *db_usuarios;
	
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	/* Retorna USUARIOS_FALHA_ARGUMENTOSINVALIDOS se n for diferente de 8 */
	if(n!=8) return USUARIOS_FALHA_ARGUMENTOSINVALIDOS;
	
	/* Dados a armazenar */
	tpUsuario *novo;
	char senha_confirmacao[USUARIOS_LIMITE_SENHA];
	
	/* Argumentos */	
	va_list argumentos;
	va_start(argumentos, n);
	unsigned int i = 0, j;
	
	char *argumento;
	
	/* Percorremos os argumentos, armazenamos os dados em usuarios_dadosTemp */
	for(;i<n;i++){
		argumento = va_arg(argumentos, char *);
		for(j=0;j<usuarios_cadastro_argumentos_n;j++)
			if(!strcmp(argumento, usuarios_args[j].validos)) strncpy(usuarios_args[j].destino, va_arg(argumentos, char *), usuarios_args[j].tamanho);
			
		/* Casos especiais diferentes de char * */
		if(!strcmp(argumento, "senha_confirmacao")) 
			strncpy(senha_confirmacao, va_arg(argumentos, char *), USUARIOS_LIMITE_SENHA);
		if(!strcmp(argumento, "formaPagamento")) 
			usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(argumentos, int);
		if(!strcmp(argumento, "tipo")) 
			usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(argumentos, int);
	}
	
	usuarios_dadosTemp->estado = ATIVO;
	usuarios_dadosTemp->avaliacao = 0;
	usuarios_dadosTemp->n_avaliacao = 0;
	
	va_end(argumentos);
	
	/* Verificamos se o grafo de usuários foi iniciado */
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	/* Procuramos por caracteres ilegais, '\n' e '\t' pois são separadores */
	for(j=0;j<usuarios_cadastro_argumentos_n;j++)
		if(strstr(usuarios_args[j].destino, "\t") != NULL || strstr(usuarios_args[j].destino, "\n") != NULL)
			return USUARIOS_FALHA_CARACTERESILEGAIS;
	
	/* Verificamos se o email é válido */
	if(strstr(usuarios_dadosTemp->email, "@") == NULL || strstr(usuarios_dadosTemp->email, ".") == NULL) return USUARIOS_FALHA_EMAIL_INVALIDO;
	
	/* Verificamos se as senhas coincidem */
	if(strcmp(usuarios_dadosTemp->senha, senha_confirmacao)) return USUARIOS_FALHA_SENHAS_INVALIDAS;
	
	/* Verificamos se já há um usuário desse */
	if(usuarios_verificaRepeticao("usuario", usuarios_dadosTemp->usuario) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
		
	/* Verificamos se já há um email desse */
	if(usuarios_verificaRepeticao("email", usuarios_dadosTemp->email) != USUARIOS_DADOS_OK) return USUARIOS_USUARIOEXISTE;
	
	/* Define-se o identificador */
	usuarios_dadosTemp->identificador = ++usuarios_identificador_max;
	
	/* Copiamos o valor temporário para o alocado */
	novo = (tpUsuario *)malloc(sizeof(tpUsuario));
	memcpy(novo, usuarios_dadosTemp, sizeof(tpUsuario));
	
	/* Devemos percorrer o grafo usuarios_grafo e salvar no arquivo */
	db_usuarios = fopen(USUARIOS_DB, "a+");
	
	/* Gravamos no arquivo */
	int fprintf_retorno = fprintf(db_usuarios, "%u\t%*s\t%*s\t%*s\t%*s\t%*s\t%d\t%d\t%d\t%lf\t%u\n", 
		usuarios_identificador_max,  \
		-USUARIOS_LIMITE_USUARIO, novo->usuario, \
		-USUARIOS_LIMITE_NOME, novo->nome, \
		-USUARIOS_LIMITE_EMAIL, novo->email, \
		-USUARIOS_LIMITE_SENHA, novo->senha, \
		-USUARIOS_LIMITE_ENDERECO, novo->endereco, \
		(int)novo->formaPagamento, \
		(int)novo->tipo, \
		(int)novo->estado, \
		novo->avaliacao, \
		novo->n_avaliacao
	);
	
	/* Adicionamos ao grafo */
	
	if(adiciona_vertice(usuarios_grafo, usuarios_contador) != SUCESSO) {
		fclose(db_usuarios);
		free(novo);
		return USUARIOS_FALHA_ADICIONAR_GRAFO;
	}
	
	/* Definimos o valores correntes no vértice */
	if(muda_valor_vertice(usuarios_grafo, usuarios_contador, (void *)novo) != SUCESSO) {
		fclose(db_usuarios);
		free(novo);
		return USUARIOS_FALHA_INSERIR_DADOS;
	}
	
	usuarios_contador++; /* Atualizamos o número de usuários */
	
	fclose(db_usuarios);
	
	return USUARIOS_SUCESSO;
}

/*!
 * @brief Função verifica um usuário é amigo do usuário na sessão
*/
usuarios_relacao usuarios_verificarAmizade(unsigned int identificador){
	unsigned int i=0;
	tpUsuario *corrente;
	grafo_arco *A, *B;
	if(usuarios_grafo == NULL) return ERRO;
	if(identificador == usuarios_sessao->identificador) return ERRO;
	
	A = grafo_busca_arco(usuarios_grafo, usuarios_sessao->identificador, identificador);
	B = grafo_busca_arco(usuarios_grafo, identificador, usuarios_sessao->identificador);
	
	if(A != NULL && B != NULL) return AMIGOS;
	if(A == NULL && B == NULL) return NENHUMA;
	if(A == NULL && B != NULL) return ACONFIRMAR;
	if(A != NULL && B == NULL) return AGUARDANDOCONFIRMACAO;
	
}

/*!
 * @brief Função que cria parte de uma relação de amizade na sesão iniciada para algum
 * outro cliente
 *
 * Deve receber o identificador do amigo pretendido
*/
usuarios_condRet usuarios_criarAmizade(unsigned int identificador){
	unsigned int i=0;
	tpUsuario *corrente;
	FILE *db_amigos;
	
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	/* Verificamos se não é o próprio usuário querendo criar uma amizade consigo mesmo */
	if(identificador == usuarios_sessao->identificador) return USUARIOS_AMIZADEINVALIDA;
	
	/* Buscamos no grafo o identificador */
	for(;i<usuarios_contador;i++){
		corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
		if(corrente == NULL) return USUARIOS_GRAFO_CORROMPIDO;
		
		if(corrente->identificador == identificador){
			/* Criamos uma aresta entre eles se não existir uma */
			if(grafo_busca_arco(usuarios_grafo, usuarios_sessao->identificador, identificador) != NULL)
				return USUARIOS_AMIZADEJASOLICITADA;
			
			if(adiciona_aresta(usuarios_grafo, usuarios_sessao->identificador, identificador) == SUCESSO){
				db_amigos = fopen(USUARIOS_DB_AMIGOS, "a+");
				if(db_amigos == NULL) return USUARIOS_FALHACRIARAMIZADE;
				
				/* Gravamos no arquivo */
				fprintf(db_amigos, "%u\t%u\n", usuarios_sessao->identificador, identificador);
				fclose(db_amigos);
				return USUARIOS_SUCESSO;
				
			}
			else return USUARIOS_FALHACRIARAMIZADE;
		}
	}
	return USUARIOS_FALHAUSUARIONAOEXISTE;
}

/*!
 * @brief Busca no grafo de usuários
*/
usuarios_condRet usuarios_busca(int condParada(tpUsuario *, va_list), tpUsuario **retorno, ...){
	unsigned int i = 0;
	tpUsuario *corrente;
	
	va_list argumentos, passado;
	
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	va_start(argumentos, retorno);
	
	for(;i<usuarios_contador;i++){
		corrente = (tpUsuario *)retorna_valor_vertice(usuarios_grafo, i);
		/* Asertiva */
		if(corrente == NULL) {
			va_end(argumentos);
			return USUARIOS_GRAFO_CORROMPIDO;
		}
		va_copy(passado, argumentos);
		if(condParada(corrente, passado)){
			va_end(passado);
			*retorno = corrente;
			return USUARIOS_SUCESSO;
		}
		va_end(passado);
	}
	
	va_end(argumentos);
	return USUARIOS_FALHA_DADOSINCORRETOS;
}

/*!
 * @brief Condição de parada para usuario e senha corretos do login
*/
int usuarios_condParada_login(tpUsuario *corrente, va_list argumentos){
	return !strcmp(corrente->usuario, va_arg(argumentos, char *)) && !strcmp(corrente->senha, va_arg(argumentos, char *));
}

/*!
 * @brief Buscamos a conta correspondente ao login e senha passados
*/
usuarios_condRet usuarios_login(char *usuario, char *senha){
	tpUsuario *corrente;
	usuarios_condRet busca;
	if(usuarios_sessao != NULL) return USUARIOS_FALHA_SESSAOABERTA;
	
	busca = usuarios_busca(usuarios_condParada_login, &corrente, usuario, senha);
	
	if(busca != USUARIOS_SUCESSO) return busca;
	
	/* Vemos se o usuário está ativo */
	if(corrente->estado == ATIVO) {
		usuarios_sessao = corrente;
		return USUARIOS_SUCESSO;
	}
	else return USUARIOS_FALHA_INATIVO;
}

/*!
 * @brief Função de logout
*/

usuarios_condRet usuarios_logout(){
	usuarios_sessao = NULL;
	return USUARIOS_SUCESSO;
}

/*!
 * @brief Condição de parada para encontrar identificador
*/
int usuarios_condParada_identificador(tpUsuario *corrente, va_list argumentos){
	return corrente->identificador == va_arg(argumentos, unsigned int);
}

/*!
 * @brief Retorna os dados do usuário do identificador passado
 *
 * Se identificador for zero, retornamos os dados da sessão
*/
usuarios_condRet usuarios_retornaDados(unsigned int identificador, char *nomeDado, void *retorno){
	unsigned int i = 0;
	tpUsuario *corrente;
	usuarios_condRet busca;
		
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	if(identificador){	
		/* Buscamos o identificador */
		busca = usuarios_busca(usuarios_condParada_identificador, &corrente, identificador);
		if(busca != USUARIOS_SUCESSO) return busca;
	}
	else corrente = usuarios_sessao;
	
	
	/* Copiamos os dados para usuarios_dadosTemp */
	memcpy(usuarios_dadosTemp, corrente, sizeof(tpUsuario));
	
	/* Dados possíveis */
	for(;i<usuarios_cadastro_argumentos_n;i++)
		if(!strcmp(nomeDado, usuarios_args[i].validos)) {
			*((char **)retorno) = usuarios_args[i].destino;
		}
	/* Outros casos (não char *) */
	if(!strcmp(nomeDado, "formaPagamento")) 
		*((usuarios_forma_de_pagamento *)retorno) = usuarios_dadosTemp->formaPagamento;
	if(!strcmp(nomeDado, "tipo")) 
		*((usuarios_tipo_usuario *)retorno) = usuarios_dadosTemp->tipo;
	if(!strcmp(nomeDado, "estado")) 
		*((usuarios_estado_de_usuario *)retorno) = usuarios_dadosTemp->estado;
	if(!strcmp(nomeDado, "avaliacao")) 
		*((double *)retorno) = usuarios_dadosTemp->avaliacao;
	if(!strcmp(nomeDado, "n_avaliacao")) 
		*((unsigned int *)retorno) = usuarios_dadosTemp->n_avaliacao;
	
	return USUARIOS_SUCESSO;
	
}

/*!
 * @brief Atualiza dados do usuário de identificador passado
*/
usuarios_condRet usuarios_atualizarDados(unsigned int identificador, char *nomeDado, ...){
	unsigned int i, j;
	usuarios_condRet busca;
	tpUsuario *corrente;
	FILE *db_usuarios;
	va_list arg;
	
	if(usuarios_grafo == NULL) return USUARIOS_FALHA_GRAFONULL;
	
	if(identificador){
		/* Buscamos o identificador */
		busca = usuarios_busca(usuarios_condParada_identificador, &corrente, identificador);
		if(busca != USUARIOS_SUCESSO) return busca;
	}
	else corrente = usuarios_sessao;
	
	va_start(arg, nomeDado);
	
	/* Analizamos os argumentos passados armazenando em usuarios_dadosTemp */
	memcpy(usuarios_dadosTemp, corrente, sizeof(tpUsuario));
	
	for(i=0;i<usuarios_cadastro_argumentos_n;i++)
		if(!strcmp(nomeDado, usuarios_args[i].validos)) {
			strncpy(usuarios_args[i].destino, va_arg(arg, char *), usuarios_args[i].tamanho);
		}
	/* Outros casos (não char *) */
	if(!strcmp(nomeDado, "formaPagamento")) 
		usuarios_dadosTemp->formaPagamento = (usuarios_forma_de_pagamento)va_arg(arg, int);
	if(!strcmp(nomeDado, "tipo")) 
		usuarios_dadosTemp->tipo = (usuarios_tipo_usuario)va_arg(arg, int);
	if(!strcmp(nomeDado, "estado")) 
		usuarios_dadosTemp->estado = (usuarios_estado_de_usuario)va_arg(arg, int);
	if(!strcmp(nomeDado, "avaliacao")) 
		usuarios_dadosTemp->avaliacao = va_arg(arg, double);
	if(!strcmp(nomeDado, "n_avaliacao")) 
		usuarios_dadosTemp->n_avaliacao = va_arg(arg, unsigned int);
		
	va_end(arg);
	
	/* Copiamos no grafo */
	memcpy(corrente, usuarios_dadosTemp, sizeof(tpUsuario));
	
	/* Atualizamos no arquivo de dados */
	db_usuarios = fopen(USUARIOS_DB, "r+");
	if(db_usuarios == NULL) return USUARIOS_FALHA_LERDB;
	
	fseek(db_usuarios, (corrente->identificador-1)*174, SEEK_SET);
	
	int fprintf_retorno = fprintf(db_usuarios, "%u\t%*s\t%*s\t%*s\t%*s\t%*s\t%d\t%d\t%d\t%lf\t%u\n", 
		corrente->identificador,  \
		-USUARIOS_LIMITE_USUARIO, corrente->usuario, \
		-USUARIOS_LIMITE_NOME, corrente->nome, \
		-USUARIOS_LIMITE_EMAIL, corrente->email, \
		-USUARIOS_LIMITE_SENHA, corrente->senha, \
		-USUARIOS_LIMITE_ENDERECO, corrente->endereco, \
		(int)corrente->formaPagamento, \
		(int)corrente->tipo, \
		(int)corrente->estado, \
		corrente->avaliacao, \
		corrente->n_avaliacao
	);
	
	fclose(db_usuarios);
	
	return USUARIOS_SUCESSO;
	
	
}

usuarios_condRet usuarios_limpar(){
	/* Fechamos qualquer sessão aberta */
	if(usuarios_logout() != USUARIOS_SUCESSO) return USUARIOS_FALHA_FECHARSESSAO;
	/* Limpamos o grafo */
	if(destroi_grafo(&usuarios_grafo) != SUCESSO) return USUARIOS_FALHA_LIMPAR;
	
	return USUARIOS_SUCESSO;
}


