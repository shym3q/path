#include <iostream>

struct vertex {
  int vertex, citizens, demand, cost;
  struct vertex *next;
};

struct edge {
  int from, to, weight, citizens, demand;
};

class Graph {
  void add_edge(edge e);
public:
  int V, E;
  Graph(edge edges[], int v, int e);
  ~Graph();
  struct vertex **adj_list;
};

Graph::Graph(edge edges[], int v, int e) : V(v), E(e) {
    adj_list = (struct vertex**)calloc(v, sizeof(struct vertex*));
    // adj_list = new node*[n]();

    for (int i = 0; i < e; i++)
      add_edge(edges[i]);
}

Graph::~Graph() {
  for (int i = 0; i < V; i++) {
    struct vertex *current = adj_list[i];
    while (current != nullptr) {
      struct vertex *next = current->next;
      delete current;
      current = next;
    }
  }
  delete []adj_list;
}

void Graph::add_edge(edge e) {
  struct vertex **head = &adj_list[e.from];
  struct vertex *n = (struct vertex*)malloc(sizeof(vertex));
  n->vertex = e.to;
  n->citizens = e.citizens;
  n->demand = e.demand;
  n->cost = e.weight;
  n->next = *head;
  // struct vertex *n = new vertex{e.to, e.citizens, e.demand, e.weight, *head};
  *head = n;
}
