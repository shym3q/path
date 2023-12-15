import networkx as nx
import matplotlib.pyplot as plt
import random
import build.path as path

class Edge:
    def __init__(src, dest, weight, citizens, demand):
        self.src = src
        self.dest = dest
        self.weight = weight
        self.citizens = demand

G = nx.watts_strogatz_graph(10, 4, 0.20)

pos = nx.spring_layout(G)

for edge in G.edges():
    G.edges[edge]["weight"] = random.randint(10, 20)

for node in G.nodes():
    G.nodes[node]["citizens"] = random.randint(1, 16)
    G.nodes[node]["demand"] = random.randint(1, 4)

edges = list()

for n, nbrs in G.adj.items():
    for nbr, eattr in nbrs.items():
        wt = eattr["weight"]
        dest = G.nodes[nbr]
        ct = dest["citizens"]
        dm = dest["demand"]
        edge = [n, nbr, wt, ct, dm]
        edges.append(edge)
        # print(edge)

nx.draw_networkx_nodes(G, pos)

nx.draw_networkx_edges(G, pos)

nx.draw_networkx_labels(G, pos)

edge_labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, edge_labels)

plt.show()

v = G.number_of_nodes()
e = G.number_of_edges()
g = path.Graph(v, e)

for edge in edges:
    g.add_edge(*edge)

path.dijkstra(g, 0)
