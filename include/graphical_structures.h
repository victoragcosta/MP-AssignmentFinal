#ifndef GRAPHICAL_STRUCTURES_H_
#define GRAPHICAL_STRUCTURES_H_

typedef struct TInput{
	char *name;
	char *text;
	int focus;
	SDL_Rect box;
	int border_size;
}TextInput;

#endif