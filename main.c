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
#define NUM_ARESTAS (int) sizeof(arestas) / sizeof(Aresta)

int main() {

    int qtd; // quantidade de arestas da AGM retornada
    Aresta *AGM = kruskal(NUM_VERTICES, NUM_ARESTAS, arestas, &qtd);

    printf("Arvore Geradora Minima:\n");
    print_arestas(AGM, qtd);

    FILE *arquivo = fopen("grafo.json", "w");
    
    if (arquivo == NULL) {
        printf("Nao foi possivel criar o arquivouivo grafo.json");
        return 1;
    }
    
    exporta_grafo(arquivo, AGM, NUM_VERTICES, qtd);
    
    fclose(arquivo);
    free(AGM);
    return 0;
}