#pragma once
#include "Base.hpp"

class AVLTree {
public:
  AVLTree();
  ~AVLTree();
  void insert(int key, int value);
  void remove(int key);

private:
  struct Node {
    Element data;
    int height;
    Node *left;
    Node *right;

    Node(int a, int b) : data{b, a}, height(1), left(nullptr), right(nullptr) {}
  };

  Node *root;

  Node *find_min(Node *node);
  Node *insert_node(Node *node, int key, int value);
  Node *remove_node(Node *node, int key);

  Node *rotate_left(Node *x);
  Node *rotate_right(Node *y);
  int get_balance_factor(Node *node);
  int get_height(Node *node);
  Element *data;
};
