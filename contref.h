#include <stdio.h>
#include <stdlib.h>

#define MAX_ALLOC 1024  // Número máximo de alocações suportadas

// Vetores para armazenar os ponteiros alocados e a contagem de referências
void* memoria[MAX_ALLOC];
int cont_ref[MAX_ALLOC];
int cont_alloc = 0;

void* malloc2(size_t size);
void liberar_bloco(int indice);
void atrib2(void *dest, void *src);
void dump();