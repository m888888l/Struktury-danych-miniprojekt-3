#include "HTAVLTree.hpp"
#include <algorithm>
#include <iostream>

HTAVLTree::HTAVLTree(int size) : capacity(size), size(0) {
  buckets = new AVLTree[capacity];
}

HTAVLTree::~HTAVLTree() { delete[] buckets; }

void HTAVLTree::insert(int value, int key) {
  if (load_factor() >= 1.5) {
    resize();
  }

  int index = hash(key, capacity);

  bool added = buckets[index].insert(value, key);

  if (added) {
    size++;
  }
}

Element HTAVLTree::remove(int key) {
  int index = hash(key, capacity);

  Element removed_el = buckets[index].remove(key);

  if (removed_el.key != -1) {
    size--;
  }

  return removed_el;
}

void HTAVLTree::print() {
  for (int i = 0; i < capacity; i++) {
    std::cout << "[" << i << "]\n";
    buckets[i].print();
  }
}

float HTAVLTree::load_factor() { return 1.0f * size / capacity; }

void HTAVLTree::resize() {
  int old_capacity = capacity;
  capacity = std::max(capacity * 2, 2);

  AVLTree *old_buckets = buckets;
  buckets = new AVLTree[capacity];

  Element *all_elements = new Element[size];
  int idx = 0;

  for (int i = 0; i < old_capacity; i++) {
    old_buckets[i].fill_array(all_elements, idx);
  }

  int old_size = size;
  size = 0;

  for (int i = 0; i < old_size; i++) {
    insert(all_elements[i].value, all_elements[i].key);
  }

  delete[] all_elements;
  delete[] old_buckets;
}
