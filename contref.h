#include <stdio.h>
#include <stdlib.h>

#define MAX_ALLOC 100  // Número máximo de alocações suportadas

// Vetor para armazenar os ponteiros alocados e a contagem de referências
void* memoria[MAX_ALLOC];
int cont_ref[MAX_ALLOC];
int cont_alloc=0;

void* malloc2(size_t tipo){
    if (cont_alloc >= MAX_ALLOC){
        printf("Erro: Número máximo de alocações atingido.\n");
        return NULL;
    }
    void* var = malloc(tipo);
    if (var != NULL){
        memoria[cont_alloc] = var;
        cont_ref[cont_alloc] = 1;  // Inicia com 1 referência
        cont_alloc++;
    }
    return var;
}

//Função para liberar a memória e remover seus dados
void liberar_bloco(int indice) {
    free(memoria[indice]);
    memoria[indice] = NULL;
    cont_ref[indice] = 0;

    // Reorganiza os vetores para preencher o espaço vazio
    for (int i = indice; i < cont_alloc - 1; i++) {
        memoria[i] = memoria[i + 1];
        cont_ref[i] = cont_ref[i + 1];
    }

    // Ajusta o último elemento
    memoria[cont_alloc - 1] = NULL;
    cont_ref[cont_alloc - 1] = 0;

    // Decrementa o contador de alocações
    cont_alloc--;
}


// Função para fazer o primeiro ponteiro apontar para a mesma área do segundo
void atrib2(void *pont1, void *pont2) {
    //Caso não exista o primeiro ponteiro, é criado um novo 
    if(pont1==NULL){
        malloc2(sizeof(pont2));
    }
    // Decrementa a referência do ponteiro antigo,
    else {
        for (int i = 0; i < cont_alloc; i++){
            if (memoria[i] == pont1){
                cont_ref[i]--;
                if (cont_ref[i] == 0){
                    liberar_bloco(i);
                }
                break;
            }
        }
    }

    // Atualiza o ponteiro de ponteiro e incrementa a referência do novo ponteiro
    pont1 = pont2;
    if (pont2 != NULL){
        for (int i = 0; i < cont_alloc; i++) {
            if (memoria[i] == pont2){
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
