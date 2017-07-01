#ifndef GRAPHIC_GRAPHICAL_STRUCTURES_H_
#define GRAPHIC_GRAPHICAL_STRUCTURES_H_

typedef struct TInput{
	char *name;
	char *text;
	int focus;
	SDL_Rect box;
	int border_size;
}TextInput;

TextInput *InicializaTextInput(char *name, int x, int y, int width, int height, int border, int max_length);
void LiberaTextInput(TextInput *text_input);
void DesenhaTextInput(TextInput *text_input, SDL_Renderer *renderer);

#endif