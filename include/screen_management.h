/**
	Funções para gerenciamento da tela
*/

#ifndef GRAPHIC_SCREEN_MANAGEMENT_H_
#define GRAPHIC_SCREEN_MANAGEMENT_H_

//Enumera telas
enum{
	PAGINA_INICIAL,
	MAX_TELAS
};

void InicializaTela(char *screen_title);
void Limpar();
void Delay(unsigned int frameLimit);
void CapturaEntrada();
int Desenha();
int MudaTela(int ind_tela);

#endif