#include <iostream>
#include "heap.h"

#define PARENT(i) ((i-1) / 2)
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*i + 2)

MinHeap::MinHeap(int cap) : capacity(cap) {
  arr = (struct node**)calloc(capacity, sizeof(struct node*));
  // arr = new struct HeapNode* [cap]();
  pos = (int*)calloc(capacity, sizeof(int));
  size = 0;
}

MinHeap::~MinHeap() {
  for (int i = 0; i < capacity; i++) {
    if (arr[i] != nullptr) {
      delete arr[i];
    }
  }
  delete []arr;
  delete []pos;
}

void MinHeap::insert(int v, int key) {
  if (size == capacity)
    return;

  struct node *n = (struct node*)malloc(sizeof(struct node));
  n->n = v;
  n->key = key;
  // struct HeapNode *n = new HeapNode{from, key};
  int i = size;
  arr[i] = n;
  pos[v] = i;
  size++;

  while (arr[i]->key < arr[PARENT(i)]->key && i != 0) {
    std::swap(arr[i], arr[PARENT(i)]);
    pos[arr[PARENT(i)]->n] = PARENT(i);
    pos[arr[i]->n] = i;
    i = PARENT(i);
  }
}

struct node *MinHeap::extract_min() {
  if (is_empty())
    return NULL;
  struct node *min = arr[0];
  std::swap(arr[0], arr[size-1]);
  pos[arr[0]->n] = 0;
  arr[size-1] = nullptr;
  size--;
  down_heapify(0);
  return min;
}

void MinHeap::decrease(int v, int key) {
  int i = pos[v];
  arr[i]->key = key;
  up_heapify(i);
}

void MinHeap::down_heapify(int i) {
  int l, r, smallest;
  l = LEFT(i);
  r = RIGHT(i);
  smallest = i;

  if (l < size && arr[l]->key < arr[i]->key)
    smallest = l;
  if (r < size && arr[r]->key < arr[smallest]->key)
    smallest = r;
  if (smallest != i) {
    std::swap(arr[smallest], arr[i]);
    pos[arr[i]->n] = i;
    pos[arr[smallest]->n] = smallest;
    down_heapify(smallest);
  }
}

void MinHeap::up_heapify(int i) {
  int parent = (i-1) / 2;
  if (i > 0 && arr[i]->key < arr[parent]->key) {
    std::swap(arr[i], arr[parent]);
    pos[arr[i]->n] = i;
    pos[arr[parent]->n] = parent;
    up_heapify(parent);
  }
}

bool MinHeap::is_empty() {
  return size == 0;
}
