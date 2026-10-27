#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"
#include <cjson/cJSON.h>

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


void exporta_grafo(FILE *f, Aresta *arestas, int num_vertices, int num_arestas) {
    const char *nomes[] = {"A", "B", "C", "D", "E", "F", "G"};

    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        printf("erro ao criar objeto JSON\n");
        return;
    }

    cJSON_AddBoolToObject(json, "directed", false);
    cJSON_AddBoolToObject(json, "multigraph", false);
    cJSON_AddItemToObject(json, "graph", cJSON_CreateObject());

    /* vertices */
    cJSON *nodes = cJSON_AddArrayToObject(json, "nodes");
    for (int i = 0; i < num_vertices; i++) {
        cJSON *node = cJSON_CreateObject();
        cJSON_AddStringToObject(node, "id", nomes[i]);
        cJSON_AddItemToArray(nodes, node);
    }

    /* arestas */
    cJSON *links = cJSON_AddArrayToObject(json, "links");
    for (int i = 0; i < num_arestas; i++) {
        cJSON *link = cJSON_CreateObject();
        cJSON_AddNumberToObject(link, "weight", arestas[i].peso);
        cJSON_AddStringToObject(link, "source", nomes[arestas[i].from]);
        cJSON_AddStringToObject(link, "target", nomes[arestas[i].to]);
        cJSON_AddItemToArray(links, link);
    }

    /* escrita no arquivo */
    char *texto = cJSON_PrintUnformatted(json);
    if (texto != NULL) {
        printf("%s\n", texto);
        fputs(texto, f);
        free(texto);
    }

    cJSON_Delete(json);
}