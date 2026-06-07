#pragma once

#include "AVLTree.hpp"
#include "Base.hpp"

class HTAVLTree : public Base {
public:
  HTAVLTree(int size);
  ~HTAVLTree();

  void insert(int value, int key) override;
  Element remove(int key) override;
  void print() override;

private:
  int capacity;
  int size;
  AVLTree *buckets;

  float load_factor();
  void resize();
};
