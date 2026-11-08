#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

void salva_grafo(const char *nome, Aresta *arestas, int n, int qtd) {
    FILE *f = fopen(nome, "w");
    if (f == NULL) {;
        return;
    }
    exporta_grafo(f, arestas, n, qtd);
    fclose(f);
}

int maxNumEdgesToRemove(int n, int **edges, int edgesSize, int *edgesColSize) {
    int totalArestas = edgesSize;
    int i, qtdAlice = 0, qtdBob = 0, qtdAmbos = 0;   /* quantidade de arestas de cada tipo */
    int qtdArvoreAlice, qtdArvoreBob;
    int qtdAmbosUsadas = 0;                       /* arestas tipo 3 que entraram na árvore */
    int resultado;
    Aresta aresta;
    Aresta *arestasAlice, *arestasBob, *arestasAmbos, *todas;
    Aresta *vetorAlice, *vetorBob;
    Aresta *arvoreAlice, *arvoreBob;

    arestasAlice = malloc((totalArestas + 1) * sizeof(Aresta));   /* só Alice */
    arestasBob   = malloc((totalArestas + 1) * sizeof(Aresta));   /* só Bob   */
    arestasAmbos = malloc((totalArestas + 1) * sizeof(Aresta));   /* os dois  */
    todas        = malloc((totalArestas + 1) * sizeof(Aresta));

    /* separa as arestas por tipo tipo 3 tem peso 0, exclusivas têm peso 1 */
    for (i = 0; i < totalArestas; i++) {
        aresta.from = edges[i][1] - 1;
        aresta.to   = edges[i][2] - 1;

        if (edges[i][0] == 3) {
            aresta.peso = 0;
            arestasAmbos[qtdAmbos] = aresta;
            qtdAmbos++;
        } else if (edges[i][0] == 1) {
            aresta.peso = 1;
            arestasAlice[qtdAlice] = aresta;
            qtdAlice++;
        } else {
            aresta.peso = 1;
            arestasBob[qtdBob] = aresta;
            qtdBob++;
        }
        todas[i] = aresta;
        todas[i].peso = edges[i][0];
    }

    salva_grafo("./data_json/grafo_leetcode.json", todas,  n, totalArestas);

    /* Alice: kruskal para vetor com tipo 3 + tipo 1 (exclusivas)*/
    vetorAlice = malloc((qtdAmbos + qtdAlice + 1) * sizeof(Aresta));

    for (i = 0; i < qtdAmbos; i++) {
        vetorAlice[i] = arestasAmbos[i];
    }
    for (i = 0; i < qtdAlice; i++) {
        vetorAlice[qtdAmbos + i] = arestasAlice[i];
    }

    arvoreAlice = kruskal(n, qtdAmbos + qtdAlice, vetorAlice, &qtdArvoreAlice);

      /* exporta agm alice */
    salva_grafo("./data_json/alice_agm.json",   arvoreAlice, n, qtdArvoreAlice);

    /* se Alice não alcançar todos os vertices já retorna -1 */
    if (qtdArvoreAlice != n - 1) {
        free(arestasAlice); free(arestasBob); free(arestasAmbos);
        free(vetorAlice); free(arvoreAlice);
        return -1;
    }

    /* conta quantas arestas tipo 3 (peso 0) entraram na árvore da Alice */
    for (i = 0; i < qtdArvoreAlice; i++) {
        if (arvoreAlice[i].peso == 0) {
            qtdAmbosUsadas++;
        }
    }

    /* Bob: kruskal para vetor com tipo 3 + tipo 2 (exclusivas)  */
    vetorBob = malloc((qtdAmbos + qtdBob + 1) * sizeof(Aresta));

    for (i = 0; i < qtdAmbos; i++) {
        vetorBob[i] = arestasAmbos[i];
    }
    for (i = 0; i < qtdBob; i++) {
        vetorBob[qtdAmbos + i] = arestasBob[i];
    }

    arvoreBob = kruskal(n, qtdAmbos + qtdBob, vetorBob, &qtdArvoreBob);

    /* exporta agm do bob */
    salva_grafo("./data_json/bob_agm.json",   arvoreBob, n, qtdArvoreBob);

    /*se Bob não alcançar todos os vertices já retorna -1 */
    if (qtdArvoreBob != n - 1) {
        free(arestasAlice); free(arestasBob); free(arestasAmbos);
        free(vetorAlice); free(vetorBob);
        free(arvoreAlice); free(arvoreBob);
        return -1;
    }

    /*  total - arestas mantidas (tipo 3 + arestas exclusivas) */
    resultado = totalArestas - (qtdArvoreAlice + qtdArvoreBob - qtdAmbosUsadas);

    free(arestasAlice); free(arestasBob); free(arestasAmbos);
    free(vetorAlice); free(vetorBob);
    free(arvoreAlice); free(arvoreBob);
    return resultado;
}

int main() {
    int dados[][3] = {
    {3, 1, 2},
    {3, 2, 3},
    {3, 1, 3},  
    {3, 4, 5},
    {1, 3, 4},
    {1, 5, 6},
    {1, 6, 7},
    {1, 7, 8},
    {1, 1, 8},   
    {2, 2, 4},
    {2, 5, 7},
    {2, 6, 8},
    {2, 4, 8},
    {2, 3, 5}    
};
    int n = 8;
    int qtd = sizeof(dados) / sizeof(dados[0]);
    int i;

    int **edges = malloc(qtd * sizeof(int *));
    int *colSize = malloc(qtd * sizeof(int));
    for (i = 0; i < qtd; i++) {
        edges[i] = dados[i];
        colSize[i] = 3;
    }

    int r = maxNumEdgesToRemove(n, edges, qtd, colSize);
    printf("Maximo de arestas removiveis: %d\n", r);

    free(edges);
    free(colSize);
    return 0;
}