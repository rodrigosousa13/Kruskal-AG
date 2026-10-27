#ifndef kruskal_h
#define kruskal_h

typedef struct _ver {
    int altura;
    struct _ver *pai;
} Vertice;

typedef struct {
    int from, to, peso;
} Aresta;

Aresta *kruskal(int n, int m, Aresta *arestas, int *qtd);
Vertice *acha_comp(Vertice *v);
void une_comp(Vertice *u, Vertice *v);
void ordena_arestas(Aresta *A, int m);
Vertice *constroi_set(int n);
void print_arestas(Aresta *arestas, int m);

#endif