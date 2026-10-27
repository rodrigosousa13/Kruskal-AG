#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

Aresta *kruskal(int n, int m, Aresta *arestas, int *qtd) {
    Aresta *T = malloc((n-1) * sizeof(Aresta));
    Vertice *vertices = constroi_set(n);
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
            break;
    }
    free(vertices);
    *qtd = j;
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

Vertice *constroi_set(int n) {
    Vertice *vertices = malloc(n * sizeof(Vertice));
    for (int i = 0; i < n; i++) {
        vertices[i] = (Vertice){
            .altura = 1,
            .pai = NULL
        };
    }

    return vertices;
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

void print_arestas(Aresta *arestas, int m) {
    for (int i = 0; i < m; i++) {
        printf("%c -- %c (peso %d):\n", arestas[i].from+65, arestas[i].to+65, arestas[i].peso);
    }
}