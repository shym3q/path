#ifndef HEAP_H
#define HEAP_H

struct node {
  int n, key;
};

class MinHeap {
  struct node **arr;
  int *pos;
  int capacity, size;
  void down_heapify(int i);
  void up_heapify(int i);
public:
  MinHeap(int cap);
  ~MinHeap();
  struct node *extract_min();
  void insert(int v, int key);
  void decrease(int v, int key);
  bool is_empty();
};

#endif // !HEAP_H
