#include <stdio.h>
#include <stdlib.h>
#include "../include/aleatorio.h"

/*
  Gera uma string aleatória composta por letras minúsculas
*/
char *stringAleatoria(unsigned int size){
	if(size == 0) return NULL;
	char *string = (char *)malloc(size);
	unsigned int i=0;
	if(string == NULL) return NULL;
	FILE *random = fopen("/dev/urandom", "r");
	for(;i<size-1;i++)
		string[i] = 97 + fgetc(random)%26;
	string[i] = '\0';
	fclose(random);
	return string;	
}

unsigned int numeroAleatorio(unsigned int limite){
	FILE *random = fopen("/dev/urandom", "r");
	unsigned int retorno;
	fread(&retorno, sizeof(unsigned int), 1, random);
	fclose(random);
	return limite?(retorno%limite):retorno;
}
