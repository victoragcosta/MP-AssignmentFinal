#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>


#include "graphical_structures.h"

TextInput *InicializaTextInput(char *name, int x, int y, int width, int height, int border, int max_length)
{
	if(name == NULL){
		printf("Erro ao instanciar entrada de texto: Sem nome.\n");
		return NULL;
	}

	TextInput *novo = (TextInput*) malloc(sizeof(TextInput));
	if(novo == NULL){
		printf("Erro ao instanciar entrada de texto: Nao alocou TextInput.\n");
		return NULL;
	}

	novo->name = (char*)malloc((strlen(name)+1)*sizeof(char));
	if(novo->name == NULL){
		printf("Erro ao instanciar entrada de texto: Nao alocou nome.\n");
		return NULL;
	}

	strcpy(novo->name, name);
	novo->text = (char*)malloc(max_length*sizeof(char));
	novo->box = {x, y, width, height};
	novo->border_size = border;
	novo->focus = 0;

	return novo;
}

void LiberaTextInput(TextInput *text_input)
{
	free(text_input->name);
	free(text_input->text);
}

void DesenhaTextInput(TextInput *text_input, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(renderer, &(text_input->box));
}