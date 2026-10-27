#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

enum {A, B, C, D, E, F, G, NUM_VERTICES};
static Aresta arestas[] = {
        {A, B, 7},
        {A, D, 5},
        {B, C, 8},
        {B, D, 9},
        {B, E, 7},
        {C, E, 5},
        {D, E, 15},
        {D, F, 6},
        {E, F, 8},
        {E, G, 9},
        {F, G, 11}
    };


int main() {

    Vertice vertices[NUM_VERTICES];
    for (int i = 0; i < NUM_VERTICES; i++) {
        vertices[i] = (Vertice){
            .altura = 1,
            .pai = NULL
        };
    }

    Aresta *AGM = kruskal(NUM_VERTICES, NUM_ARESTAS, vertices, arestas);

    printf("Arvore Geradora Minima:\n");
    for (int i = 0; i < NUM_VERTICES - 1; i++) {
        printf("%d -- %d == %d:\n", AGM[i].from, AGM[i].to, AGM[i].peso);
    }
    

    FILE *arquivo = fopen("grafo.json", "w");
    
    if (arquivo == NULL) {
        printf("Nao foi possivel criar o arquivouivo grafo.json");
        return 1;
    }
    
    exporta_grafo(arquivo, AGM, NUM_VERTICES, NUM_VERTICES - 1);


    fclose(arquivo);

    free(AGM);
    return 0;
}