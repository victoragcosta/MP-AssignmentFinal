/**
	Gerencia as entradas e exibição da pagina inicial
*/


#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "pagina_inicial.h"

#include "graphical_structures.h"

#define NUM_TEXT_INPUTS 2

TextInput *text_inputs[NUM_TEXT_INPUTS] = {NULL, NULL};

char *composition;
Sint32 cursor;
Sint32 selection_len;

void DesenhaPaginaInicial(SDL_Window *janelinha, SDL_Renderer *renderer, int width, int height)
{
	int i;
	for(i = 0; i < NUM_TEXT_INPUTS; i++){
		DesenhaTextInput(text_inputs[i], renderer);
	}

	//Muda para a cor de fundo
	SDL_SetRenderDrawColor(renderer, 51, 51, 51, 255);
}

void GerenciaEntradaPaginaInicial(SDL_Event event)
{
	switch(event.type){

		case SDL_TEXTINPUT:
        strcat(text_inputs[0]->text, event.text.text);
        break;
    	
    	case SDL_TEXTEDITING:
        /*
        Update the composition text.
        Update the cursor position.
        Update the selection length (if any).
        */
        composition = event.edit.text;
        cursor = event.edit.start;
        selection_len = event.edit.length;
        break;

	}

}

void TrocaPaginaInicial(SDL_Renderer *renderer)
{
	if(text_inputs[0] == NULL){
		text_inputs[0] = InicializaTextInput("username",10,20,100,30,3,20);
		if(text_inputs[0] == NULL){
			printf("Erro ao instanciar entrada de texto.\n");
			exit(1);
		}
	}
	if(text_inputs[1] == NULL){
		text_inputs[1] = InicializaTextInput("password",100,100,100,30,3,20);
		if(text_inputs[1] == NULL){
			printf("Erro ao instanciar entrada de texto.\n");
			exit(1);
		}
	}
}

void LimparPaginaInicial()
{
	int i;
	for(i = 0; i < NUM_TEXT_INPUTS; i++){
		LiberaTextInput(text_inputs[i]);
		free(text_inputs[i]);
	}
}