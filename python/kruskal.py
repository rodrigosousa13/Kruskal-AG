from typing import List


class Node:
    def __init__(self, node, altura):
        self.node = node # vertice que nomeia a componente
        self.altura = altura # altura do vertice na arvore da componente
        self.pai = None # proximo no da componente

class UnionFind:
    def __init__(self):
        self.nodes: List[Node | None] = []

    def get_nodes(self, grafo: List[List[tuple[int]]]) -> None:
        for node in range(len(grafo)):
            self.nodes.append(Node(node, 1))

    def find_comp(self, node: int) -> int:
        """Retorna a componente de node
        A componente de um nó será o ultimo Node na lista encadeada"""
        atual = self.nodes[node]
        while atual.pai is not None:
            atual = self.nodes[atual.pai]
        return atual.node       

    def union(self, comp1: int, comp2: int) -> None:
        """comp1 e comp2 indicam os indices dos nós
           que representam a componente"""    
        altura1 = self.nodes[comp1].altura
        altura2 = self.nodes[comp2].altura
        if altura1 < altura2:
            self.nodes[comp1].pai = comp2
        elif altura1 > altura2:
            self.nodes[comp2].pai = comp1
        else:
            self.nodes[comp2].pai = comp1
            self.nodes[comp1].altura += 1


def kruskal(G):
    """Retorna a Arvore Geradora Minima"""
    T = [[] for _ in range(len(G))]
    arestas = [] # (u, v, peso)
    for i in range(len(G)): # para cada nó i
        for e in G[i]: # para cada aresta que sai do nó i
            u = i
            v = e[0]
            peso = e[1]
            aresta = (u, v, peso)
            arestas.append(aresta)

    arestas.sort(key=lambda e: e[2]) # ordena as arestas com base no peso

    uf = UnionFind()
    uf.get_nodes(G)

    peso_total = 0
    for aresta in arestas:
        u, v, peso = aresta[0], aresta[1], aresta[2]
        comp_u = uf.find_comp(u)
        comp_v = uf.find_comp(v)

        if comp_u != comp_v: # se T + (u,v) nao forma ciclo
            uf.union(comp_u, comp_v)
            T[u].append((v, peso))
            peso_total += peso

    return T, peso_total


if __name__ == "__main__":
    # indice do vertice (A=0, ..., G=6): [(indice do vizinho, peso), ...]
    grafo_lista = [
        [(1, 7), (3, 5)],
        [(0, 7), (2, 8), (3, 9), (4, 7)],
        [(1, 8), (4, 5)],
        [(0, 5), (1, 9), (4, 15), (5, 6)],
        [(1, 7), (2, 5), (3, 15), (5, 8), (6, 9)],
        [(3, 6), (4, 8), (6, 11)],
        [(4, 9), (5, 11)],
    ]

    letras = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
    agm, peso_total = kruskal(grafo_lista)
    print("Arestas da Árvore Geradora Mínima:")
    for node in range(len(agm)):
        for aresta in agm[node]:
            print(f"{letras[node]} -- {letras[aresta[0]]} (peso {aresta[1]})")
    print(f"Peso total da AGM: {peso_total}")


