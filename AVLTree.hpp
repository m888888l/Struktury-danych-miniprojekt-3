#pragma once
#include "Base.hpp"

class AVLTree {
public:
  AVLTree();
  ~AVLTree();
  void insert();
  void remove();

private:
  void rotate_left();
  void rotate_right();
  void get_balance_factor();
  Element *data;
};
