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

    FILE *f1 = fopen("grafo.json", "w");
    exporta_grafo(f1, arestas, NUM_VERTICES, NUM_ARESTAS);
    fclose(f1);
        
    printf("Arvore Geradora Minima:\n");
    print_arestas(AGM, qtd);
    
    FILE *f2 = fopen("agm.json", "w");
    exporta_grafo(f2, AGM, NUM_VERTICES, qtd);
    fclose(f2);

    free(AGM);
    return 0;
}