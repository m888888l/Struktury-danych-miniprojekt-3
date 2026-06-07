#pragma once
#include "Base.hpp"

class AVLTree {
public:
  AVLTree();
  ~AVLTree();

  bool insert(int value, int key);
  Element remove(int key);
  void print();

  void fill_array(Element *arr, int &index);

private:
  struct Node {
    Element data;
    int height;
    Node *left;
    Node *right;

    Node(int v, int k) : data{v, k}, height(1), left(nullptr), right(nullptr) {}
  };

  Node *root;

  Node *find_min(Node *node);
  Node *insert_node(Node *node, int key, int value, bool &added);
  Node *remove_node(Node *node, int key, Element &removed_el);

  Node *rotate_left(Node *x);
  Node *rotate_right(Node *y);
  int get_balance_factor(Node *node);
  int get_height(Node *node);

  void destroy_tree(Node *node);
  void print_in_order(Node *node);
  void fill_array_recursive(Node *node, Element *arr, int &index);
};
