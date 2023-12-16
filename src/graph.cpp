#include <iostream>

struct vertex {
  int vertex, citizens, demand, cost;
  struct vertex *next;
};

class Graph {
public:
  int V, E;
  Graph(int v, int e);
  ~Graph();
  void add_edge(int from, int to, int weight, int citizens, int demand);
  struct vertex **adj_list;
};

Graph::Graph(int v, int e) : V(v), E(e) {
    adj_list = (struct vertex**)calloc(v, sizeof(struct vertex*));
    // adj_list = new node*[n]();
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

void Graph::add_edge(int from, int to, int weight, int citizens, int demand) {
  struct vertex **head = &adj_list[from];
  struct vertex *n = (struct vertex*)malloc(sizeof(struct vertex));
  n->vertex = to;
  n->citizens = citizens;
  n->cost = weight;
  n->demand = demand;
  n->next = *head;
  *head = n;
}
