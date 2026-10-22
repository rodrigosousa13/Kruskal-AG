#include <stdio.h>

typedef struct _ver {
    int comp_size;
    struct _ver *next;
} Vertice;

typedef struct {
    int from, to, peso;
} Aresta;

enum {A, B, C, D, E, F, G, NUM_VERTICES};

void acha();
void une();
void ordena_arestas(Aresta **arestas);

int main() {
    Vertice vertices[NUM_VERTICES];
    for (int i; i < NUM_VERTICES; i++) {
        vertices[i] = (Vertice){
            .comp_size = 1,
            .next = NULL
        };
    }
    Aresta arestas[] = {
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
}