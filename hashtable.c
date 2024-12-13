#include <stdio.h>
#include <stdlib.h>

#define M 23 //tamanho da tabela hash

typedef struct tlist {
    int valor;          
    struct tlist *next; 
} tlist;

int hash(int valor);
void inserirLista(int fv, tlist **array);
void printLista(tlist **array);
void liberarMemoria(tlist **array);

int main() {

    FILE *file = fopen("./casos_de_teste.txt", "r");

    tlist **array = (tlist **)malloc(M * sizeof(tlist *));

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 0;
    }

    int valor_aux;
    while (fscanf(file, "%d", &valor_aux) == 1) {
        fgetc(file);
        inserirLista(valor_aux, array);
    }

    printLista(array);

    liberarMemoria(array);
    fclose(file);

    return 0;
}

// calcula o indice na tabela hash
int hash(int valor) {
    return valor % M; 
}

// insere o valor a tabela
void inserirLista(int fv, tlist **array) {
    tlist *novo = (tlist *)malloc(sizeof(tlist));
    novo->valor = fv;
    novo->next = NULL;

    int index = hash(fv);

    if (array[index] == NULL) {
        array[index] = novo;
    }
    else {
        tlist *aux = array[index];
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = novo;
    }
}

// printa a tabela hash
void printLista(tlist **array) {
    printf("[\n");

    // percorre a tabela
    for (int i = 0; i < M; i++) {
        //printa o indice
        printf("    %d: ", i);
        // se a lista estiver vazia printa NULL
        if (array[i] == NULL) {
            printf("NULL");
        } else {
            // printa a lista
            tlist *aux = array[i];
            printf("[");
            while (aux != NULL) {
                printf("%d", aux->valor);
                if (aux->next != NULL) {
                    printf(", ");
                }
                aux = aux->next;
            }
            printf("]");
        }
        // printa a virgula se nao for o ultimo indice
        printf("%s\n", (i < M - 1) ? "," : "");
    }
    printf("]\n");
}

// libera a memoria usada
void liberarMemoria(tlist **array) {
    for (int i = 0; i < M; i++) {
        tlist *atual = array[i];
        while (atual != NULL) {
            tlist *next = atual->next;
            free(atual);
            atual = next;
        }
    }
    free(array);
}
