import networkx as nx
import matplotlib.pyplot as plt
import random
import build.path as path

def main():
    G, g, pos = generate()
    p = solve(g)
    draw(G, pos, p)

def generate(n=20):
    G = nx.watts_strogatz_graph(n, 4, 0.20)
    pos = nx.spring_layout(G)

    for edge in G.edges():
        G.edges[edge]["weight"] = random.randint(10, 20)
    for node in G.nodes():
        G.nodes[node]["citizens"] = random.randint(1, 5)
        G.nodes[node]["demand"] = random.randint(1, 5)

    edges = list()
    for n, nbrs in G.adj.items():
        for nbr, eattr in nbrs.items():
            wt = eattr["weight"]
            dest = G.nodes[nbr]
            ct = dest["citizens"]
            dm = dest["demand"]
            edge = [n, nbr, wt, ct, dm]
            edges.append(edge)

    v = G.number_of_nodes()
    e = G.number_of_edges()
    g = path.Graph(v, e)

    for edge in edges:
        g.add_edge(*edge)

    return G, g, pos

def solve(g, src=0, dest=15):
    r = path.dijkstra(g, src, dest)
    p = list()
    n = r
    for _ in range(r.n):
        p.append(n.i)
        n = n.next()
    p = list(zip(p, p[1:]))
    return p

def draw(g, pos, path):
    nx.draw_networkx_nodes(g, pos)
    edge_colors = [
        "red" if edge in path or tuple(reversed(edge)) in path else "black" for edge in g.edges()
    ]
    nx.draw_networkx_edges(g, pos, edge_color=edge_colors)
    nx.draw_networkx_labels(g, pos)
    edge_labels = nx.get_edge_attributes(g, "weight")
    nx.draw_networkx_edge_labels(g, pos, edge_labels)
    plt.show()

if __name__ == "__main__":
    main()
