import json
import sys
import matplotlib.pyplot as plt
import networkx as nx
from matplotlib.widgets import Button
from networkx.readwrite import json_graph

CORES = plt.cm.Set2.colors
CINZA = "lightgray"


def carrega_grafo(caminho):
    """Devolve os dados crus e o grafo do networkx."""
    with open(caminho) as f:
        dados = json.load(f)
    return dados, json_graph.node_link_graph(dados)


def carrega_passos(dados, caminho_agm):
    """Devolve a lista de passos do kruskal."""
    with open(caminho_agm) as f:
        agm = [{l["source"], l["target"]} for l in json.load(f)["links"]]

    # percorre as arestas na ordem do kruskal: se for a proxima da AGM,
    # foi aceita; senao, rejeitada. Para quando a AGM fica completa.
    passos, i = [], 0
    for l in dados["links"]:
        if i == len(agm):
            break
        aceita = {l["source"], l["target"]} == agm[i]
        i += aceita
        passos.append({**l, "accepted": aceita})
    return passos


def mostra_grafo(G, pos):
    """Desenha o grafo normal, sem passos."""
    fig, ax = plt.subplots(figsize=(9, 7))
    nx.draw_networkx_edges(G, pos, ax=ax, edge_color=CINZA, width=1.5)
    nx.draw_networkx_nodes(G, pos, ax=ax, node_size=800, edgecolors="black",
                           node_color=CINZA)
    nx.draw_networkx_labels(G, pos, ax=ax, font_size=16)
    nx.draw_networkx_edge_labels(G, pos, nx.get_edge_attributes(G, "weight"), ax=ax)
    ax.set_title("Grafo")
    ax.axis("off")
    plt.show()


def visualiza_kruskal(G, pos, passos):
    fig, ax = plt.subplots(figsize=(9, 7))
    plt.subplots_adjust(bottom=0.15)
    estado = {"k": 0}  # quantos passos ja foram executados

    def desenha():
        k = estado["k"]
        ax.clear()
        ate_agora = passos[:k]
        aceitas = [(p["source"], p["target"]) for p in ate_agora if p["accepted"]]
        rejeitadas = [(p["source"], p["target"]) for p in ate_agora if not p["accepted"]]

        # componentes formadas pelas arestas aceitas ate aqui
        H = nx.Graph(aceitas)
        H.add_nodes_from(G)
        componentes = sorted(sorted(c) for c in nx.connected_components(H))

        # vertices sozinhos ficam cinza; cada componente maior ganha uma cor
        cor = dict.fromkeys(G, CINZA)
        for i, comp in enumerate(c for c in componentes if len(c) > 1):
            cor.update(dict.fromkeys(comp, CORES[i % len(CORES)]))

        # arestas: todas em cinza, rejeitadas e aceitas por cima
        nx.draw_networkx_edges(G, pos, ax=ax, edge_color=CINZA, width=1.5)
        nx.draw_networkx_edges(G, pos, ax=ax, edgelist=rejeitadas,
                               edge_color="red", style="dashed", width=2)
        nx.draw_networkx_edges(G, pos, ax=ax, edgelist=aceitas, width=4)

        # aresta do passo atual em destaque
        msg = "Inicio: cada vertice e uma componente"
        if k > 0:
            p = passos[k - 1]
            nx.draw_networkx_edges(G, pos, ax=ax,
                                   edgelist=[(p["source"], p["target"])],
                                   edge_color="green" if p["accepted"] else "red",
                                   width=6)
            status = "aceita" if p["accepted"] else "rejeitada (formaria ciclo)"
            msg = f"{p['source']}-{p['target']} (peso {p['weight']}): {status}"

        nx.draw_networkx_nodes(G, pos, ax=ax, node_size=800, edgecolors="black",
                               node_color=[cor[v] for v in G])
        nx.draw_networkx_labels(G, pos, ax=ax, font_size=16)
        nx.draw_networkx_edge_labels(G, pos, nx.get_edge_attributes(G, "weight"), ax=ax)

        peso = sum(p["weight"] for p in ate_agora if p["accepted"])
        ax.set_title(f"Passo {k}/{len(passos)} | {len(componentes)} componentes | "
                     f"peso da AGM: {peso}\n{msg}")
        ax.axis("off")
        fig.canvas.draw_idle()

    def mover(delta):
        """Avanca (+1) ou volta (-1) um passo"""
        estado["k"] = max(0, min(len(passos), estado["k"] + delta))
        desenha()

    b_ant = Button(plt.axes([0.30, 0.04, 0.17, 0.07]), "Anterior")
    b_prox = Button(plt.axes([0.53, 0.04, 0.17, 0.07]), "Proximo")
    b_ant.on_clicked(lambda _: mover(-1))
    b_prox.on_clicked(lambda _: mover(+1))

    desenha()
    plt.show()


def main():
    args = sys.argv[1:]
    if len(args) not in (1, 2):
        sys.exit(f"Uso: python {sys.argv[0]} grafo.json [agm.json]")

    dados, G = carrega_grafo(args[0])
    pos = nx.spring_layout(G, seed=7, weight=None)

    if len(args) == 1:
        mostra_grafo(G, pos)
    else:
        passos = carrega_passos(dados, args[1])
        visualiza_kruskal(G, pos, passos)


if __name__ == "__main__":
    main()