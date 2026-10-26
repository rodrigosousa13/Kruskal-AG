#ifndef kruskal_h
#define kruskal_h

#include <stdio.h>
#include <stdlib.h>

#define NUM_ARESTAS (int) sizeof(arestas) / sizeof(Aresta)


typedef struct _ver {
    int altura;
    struct _ver *pai;
} Vertice;

typedef struct {
    int from, to, peso;
} Aresta;


Aresta *kruskal(int n, int m, Vertice vertices[], Aresta *arestas);
Vertice *acha_comp(Vertice *v);
void une_comp(Vertice *u, Vertice *v);
void ordena_arestas(Aresta *A, int m);


#endif