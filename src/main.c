/**
	Inicializa o programa com a interface gráfica
	e faz um controle básico da exibição.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "screen_management.h"

#define MIN_DELAY 16

int main(int argc, char const *argv[])
{
	//Usado para limitar para 1000/MIN_DELAY FPS dando um delay de no mínimo MIN_DELAY milissegundos
	unsigned int frame_limit = SDL_GetTicks() + MIN_DELAY;
	//Controla o loop principal de execução
	int executando;
	
	//Inicializa a tela
	InicializaTela("Teste");
	executando = 1;

	//Garante execuções finais antes de fechar programa
	atexit(Limpar);

	executando = 500;
	while(executando > 0){
		//SDL_Delay(5000);
		
		//Pega entrada
		CapturaEntrada();

		//Atualiza estado

		//Gera a nova tela e exibe
		Desenha();
		
		//Pausa o programa para evitar gasto excessivo da CPU
		Delay(frame_limit);
		frame_limit = SDL_GetTicks() + MIN_DELAY;
		printf("executando %d\n", executando);
		executando--;
	}

	//Limpeza final antes de encerrar o programa
	Limpar();

	return 0;
}