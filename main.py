import networkx as nx
import matplotlib.pyplot as plt
import random
import build.path as path

G = nx.watts_strogatz_graph(20, 4, 0.20)

pos = nx.spring_layout(G)

for edge in G.edges():
    G.edges[edge]["weight"] = random.randint(20, 30)

for node in G.nodes():
    G.nodes[node]["citizens"] = random.randint(5, 10)
    G.nodes[node]["demand"] = random.randint(5, 10)

edges = list()

for n, nbrs in G.adj.items():
    for nbr, eattr in nbrs.items():
        wt = eattr["weight"]
        dest = G.nodes[nbr]
        ct = dest["citizens"]
        dm = dest["demand"]
        edge = [n, nbr, wt, ct, dm]
        edges.append(edge)

nx.draw_networkx_nodes(G, pos)

nx.draw_networkx_edges(G, pos)

nx.draw_networkx_labels(G, pos)

edge_labels = nx.get_edge_attributes(G, "weight")
nx.draw_networkx_edge_labels(G, pos, edge_labels)

v = G.number_of_nodes()
e = G.number_of_edges()
g = path.Graph(v, e)

for edge in edges:
    g.add_edge(*edge)

r = path.dijkstra(g, 0, 10)
n = r
for _ in range(r.n):
    print(n.i)
    n = n.next()

plt.show()
