#include <cstdlib>
#include <iostream>
#include <limits.h>
#include <pybind11/pybind11.h>
#include "graph.cpp"
#include "heap.cpp"

namespace py = pybind11;

struct result {
  int i, n;
  struct result *next;
  struct result *next_element();
};

struct result *dijkstra(struct Graph *g, int from, int to) {
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
    if (u == to) break;
    for (struct vertex *v = g->adj_list[u]; v != nullptr; v = v->next) {
      int alt = cost[u] + v->cost - v->demand - v->citizens;
      // int alt = cost[u] + v->cost;
      int n = v->vertex;
      if (alt < cost[n]) {
        cost[n] = alt;
        prev[n] = u;
        q.decrease(n, alt);
      }
    }
  }

  int len = 0;
  struct result *r = NULL;
  for (int i = to; i != -1; i = prev[i]) {
    struct result *next = (struct result*)malloc(sizeof(struct result));
    next->i = i;
    next->next = r;
    r = next;
    len++;
  }
  r->n = len;

  return r;
}

struct result *result::next_element() {
  return next;
}

PYBIND11_MODULE(path, m) {
  m.def("dijkstra", &dijkstra);

  py::class_<Graph>(
      m, "Graph"
      )
    .def(py::init<int, int>())
    .def("add_edge", &Graph::add_edge);

  py::class_<result>(
      m, "Result"
      )
    .def_readwrite("i", &result::i)
    .def_readwrite("n", &result::n)
    .def("next", &result::next_element);
}
