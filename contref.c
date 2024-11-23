#include "contref.h"

// Função para alocar memória e registrar a alocação
void* malloc2(size_t size){
    if (cont_alloc >= MAX_ALLOC){
        printf("Erro: Número máximo de alocações atingido.\n");
        return NULL;
    }
    void *var = malloc(size);
    if (var != NULL){
        memoria[cont_alloc] = var;
        cont_ref[cont_alloc] = 1;  // Inicia com 1 referência
        cont_alloc++;
    }
    return var;
}

//Função para liberar a memória e remover seus dados
void liberar_bloco(int indice){
    free(memoria[indice]);
    memoria[indice]=NULL;
    cont_ref[indice]=0;
}

// Função para fazer o primeiro ponteiro apontar para a mesma área do segundo
void atrib2(void *dest, void *src) {
    // Decrementa a referência do ponteiro antigo, se houver
    if (dest != NULL) {
        for (int i = 0; i < cont_alloc; i++){
            if (memoria[i] == dest){
                cont_ref[i]--;
                if (cont_ref[i] == 0){
                    liberar_bloco(i);
                }
                break;
            }
        }
    }

    // Atualiza o ponteiro de destino e incrementa a referência do novo ponteiro
    dest = src;
    if (src != NULL){
        for (int i = 0; i < cont_alloc; i++) {
            if (memoria[i] == src){
                cont_ref[i]++;
                break;
            }
        }
    }
}

// Função para exibir o estado atual das alocações e contadores de referência
void dump(){
    printf("Estado:\n");
    for (int i = 0; i < cont_alloc; i++) {
        if (memoria[i] != NULL) {
            printf("Endereco: %p, Contador de Referencias: %d\n", memoria[i], cont_ref[i]);
        }
    }
    printf("\n");
}