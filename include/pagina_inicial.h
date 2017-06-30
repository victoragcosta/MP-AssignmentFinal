#ifndef GRAPHIC_PAGINA_INICIAL_H_
#define GRAPHIC_PAGINA_INICIAL_H_

void DesenhaPaginaInicial(SDL_Window *janela, SDL_Renderer *renderer, int width, int height);
void GerenciaEntradaPaginaInicial(SDL_Event event);
void TrocaPaginaInicial(SDL_Renderer *renderer);

#endif