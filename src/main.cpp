#include <cstdlib>
#include <iostream>
#include <limits.h>
#include <pybind11/pybind11.h>
#include "graph.cpp"
#include "heap.cpp"

namespace py = pybind11;

void dijkstra(struct Graph *g, int from) {
  int n = g->V;
  int cost[n], prev[n];
  struct MinHeap q = MinHeap(n);

  for (int v = 0; v < n; v++) {
    int key = INT_MAX;
    if (v == from)
      key = 0;
    prev[v] = -1;
    cost[v] = key;
    q.insert(v, key);
  }

  while (!q.is_empty()) {
    struct node *min = q.extract_min();
    int u = min->n;
    for (struct vertex *v = g->adj_list[u]; v != nullptr; v = v->next) {
      int alt;
      if ((alt = cost[u] + v->cost - v->demand - v->citizens) < cost[v->vertex]) {
        cost[v->vertex] = alt;
        prev[v->vertex] = u;
        q.decrease(v->vertex, alt);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (i == from) continue;
    std::cout<<cost[i]<<std::endl;
    // std::cout<<prev[i]<<std::endl;
    std::cout<<std::endl;
  }
  std::cout<<std::endl<<std::endl;
}

PYBIND11_MODULE(path, m) {
  m.doc() = "MODULE DOC";

  m.def("dijkstra", &dijkstra);

  py::class_<Graph>(
      m, "Graph"
      )
    .def(py::init<int, int>())
    .def("add_edge", &Graph::add_edge);
}

int main (int argc, char *argv[]) {
  Graph g = Graph(4, 8);
  g.add_edge(0, 1, 5, 1, 2);
  g.add_edge(1, 0, 5, 3, 2);
  g.add_edge(1, 2, 4, 3, 4);
  g.add_edge(2, 1, 4, 1, 2);
  g.add_edge(2, 0, 8, 3, 2);
  g.add_edge(0, 2, 8, 3, 4);
  g.add_edge(2, 3, 16, 1, 1);
  g.add_edge(3, 2, 16, 3, 4);
  
  // dijkstra(&g, 0);
  // dijkstra(&g, 1);
  // dijkstra(&g, 2);
  // dijkstra(&g, 3);

  return 0;
}
