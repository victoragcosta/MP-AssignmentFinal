/**
	Funções para gerenciamento da tela
*/

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "screen_management.h"
#include "pagina_inicial.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Para exibição
SDL_Window *janela;
SDL_Renderer *renderer;

//Seleciona a tela
int tela_atual = PAGINA_INICIAL;

void InicializaTela(char *screen_title)
{
	// Inicializa Vídeo
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Nao foi possivel inicializar SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Inicia tela
	janela = SDL_CreateWindow(
		screen_title, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, 
		SDL_WINDOW_OPENGL
		);

	if (janela == NULL) {
		printf("%s\n", SDL_GetError());
		printf("Nao foi possivel colocar no modo de tela %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	//Inicia Renderizador
	renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		printf("Nao foi possivel inicializar renderizador: %s\n", SDL_GetError());
		exit(1);
	}

	//Cor padrão da tela
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

void Limpar() 
{
	//Limpa Recursos da Pagina Inicial
	LimparPaginaInicial();

	//Destrói Renderizador
	SDL_DestroyRenderer(renderer);

	//Destrói a Janela
    SDL_DestroyWindow(janela);
	
	// Finaliza
	SDL_Quit();
}

void Delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

void CapturaEntrada()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)){

		switch(event.type){
			
			//Apertar x ou alt+f4
			case SDL_QUIT:
			exit(0);
			break;

			//Apertar qualquer tecla
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_UP:
				MudaTela(PAGINA_INICIAL);
				break;
			}
			break;

		}

		switch(tela_atual){
			case PAGINA_INICIAL:
				GerenciaEntradaPaginaInicial(event);
				break;
			default:
				GerenciaEntradaPaginaInicial(event);
				break;
		}
	}
}

int Desenha()
{
	if(janela == NULL){
		return 1;
	}
	//Limpa a janela
	SDL_RenderClear(renderer);

	//Desenha
	switch(tela_atual){
		case PAGINA_INICIAL:
			DesenhaPaginaInicial(janela, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;
		default:
			MudaTela(PAGINA_INICIAL);
			printf("Pagina nao existe, trocando para a pagina inicial!\n");
			break;
	}

	//Exibe na tela
	SDL_RenderPresent(renderer);

	//Delay para evitar uso excessivo de CPU
	SDL_Delay(1);

	return 0;
}

int MudaTela(int ind_tela)
{
	if(!(0 <= ind_tela && ind_tela < MAX_TELAS))
		return 1;

	switch(ind_tela){
		case PAGINA_INICIAL:
		TrocaPaginaInicial(renderer);
		tela_atual = PAGINA_INICIAL;
		break;

		default:
		printf("Pagina nao existe, trocando para a pagina inicial!\n");
		MudaTela(PAGINA_INICIAL);
		return 1;
		break;
	}

	return 0;
}