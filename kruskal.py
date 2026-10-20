from typing import List


class Node:
    def __init__(self, node, comp_size):
        self.node = node # vertice que nomeia a componente
        self.size = comp_size # tamanho da componente
        self.next = None # proximo no da componente

class UnionFind:
    def __init__(self):
        self.nodes: List[Node | None] = []

    def get_nodes(self, grafo):
        for node in range(len(grafo)):
            self.nodes.append(Node(node, 1))

    def find_comp(self, node):
        """Retorna a componente de node
        A componente de um nó será o ultimo Node na lista encadeada"""
        atual = self.nodes[node]
        while atual.next is not None:
            atual = atual.next
        return atual.node       

    def union(self, comp1, comp2):
        """comp_menor e comp_maior indicam o indice do nó
           que representa a componente"""
        size1 = self.nodes[comp1].size
        size2 = self.nodes[comp2].size
        if size1 <= size2:
            self.nodes[comp1].next = comp2
        else:
            self.nodes[comp2].next = comp1

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

def kruskal(G):
    """Retorna a Arvore Geradora Minima"""
    T = [[]] * len(G)
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
            arestas[u].append((v, peso))
            peso_total += peso
            
    return T


