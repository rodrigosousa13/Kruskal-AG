#include <stdio.h>
#include <stdlib.h>

typedef struct _ver {
    int altura;
    struct _ver *pai;
} Vertice;

typedef struct {
    int from, to, peso;
} Aresta;

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

Vertice *acha_comp(Vertice *v);
void une_comp(Vertice *u, Vertice *v);
void ordena_arestas(Aresta *arestas, int m);
Aresta *kruskal(int n, int m, Vertice vertices[], Aresta *arestas);

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

    free(AGM);
    return 0;
}

Aresta *kruskal(int n, int m, Vertice vertices[], Aresta *arestas) {
    Aresta *T = malloc((n-1) * sizeof(Aresta));
    int i = 0, j = 0;

    ordena_arestas(arestas, m);

    for (i = 0; i < m; i++) {
        int label_u = arestas[i].from;
        int label_v = arestas[i].to;
        Vertice *u = &vertices[label_u];
        Vertice *v = &vertices[label_v];

        if (acha_comp(u) != acha_comp(v)) {
            une_comp(u, v);
            T[j] = arestas[i];
            j++;
        }

        if (j >= n - 1) // j vai de 0 a n-2 (n-1 arestas)
            return T;
    }

    return T;
}

Vertice *acha_comp(Vertice *v) {
    if (v->pai != NULL)
        return acha_comp(v->pai);
    return v;
}

void une_comp(Vertice *u, Vertice *v) {
    u = acha_comp(u); 
    v = acha_comp(v); 

    if (u->altura < v->altura) {
        u->pai = v;
    } else if (u->altura > v-> altura) {
        v->pai = u;
    } else {
        v->pai = u;
        u->altura++;
    }
}

void ordena_arestas(Aresta *A, int m) {
    /* usa comb sort pra ordenar as arestas */
    int i, j, intervalo, trocado = 1;
    Aresta temp;

	intervalo = m;
	while (intervalo > 1 || trocado == 1)
	{
		intervalo = intervalo * 10 / 13;
		if (intervalo == 9 || intervalo == 10) intervalo = 11;
		if (intervalo < 1) intervalo = 1;
		trocado = 0;
		for (i = 0, j = intervalo; j < m; i++, j++)
		{
			if (A[i].peso > A[j].peso) {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
		}
	}
}