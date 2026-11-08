#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

enum {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, NUM_VERTICES};

static Aresta arestas[] = {
    {A, B, 4},
    {A, C, 8},
    {A, D, 6},
    {B, C, 2},
    {B, E, 5},
    {B, F, 9},
    {C, D, 7},
    {C, F, 1},
    {C, G, 11},
    {D, G, 10},
    {D, H, 14},
    {E, F, 3},
    {E, I, 8},
    {F, G, 4},
    {F, I, 7},
    {F, J, 6},
    {G, H, 12},
    {G, J, 2},
    {G, K, 9},
    {H, K, 5},
    {H, L, 10},
    {I, J, 11},
    {I, M, 7},
    {J, K, 8},
    {J, M, 3},
    {J, N, 6},
    {K, L, 4},
    {K, N, 9},
    {K, O, 13},
    {L, O, 2},
    {M, N, 5},
    {N, O, 8}
};

#define NUM_ARESTAS (int) sizeof(arestas) / sizeof(Aresta)

int main() {

    int qtd; // quantidade de arestas da AGM retornada
    Aresta *AGM = kruskal(NUM_VERTICES, NUM_ARESTAS, arestas, &qtd);

    FILE *f1 = fopen("./data_json/grafo.json", "w");
    exporta_grafo(f1, arestas, NUM_VERTICES, NUM_ARESTAS);
    fclose(f1);
        
    printf("Arvore Geradora Minima:\n");
    print_arestas(AGM, qtd);
    
    FILE *f2 = fopen("./data_json/agm.json", "w");
    exporta_grafo(f2, AGM, NUM_VERTICES, qtd);
    fclose(f2);

    free(AGM);
    return 0;
}