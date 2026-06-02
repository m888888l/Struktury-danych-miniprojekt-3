#include "AVLTree.hpp"
#include <cstddef>
#include <iostream>

using namespace std;

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {}

int AVLTree::get_height(Node *node) {
  if (node == nullptr)
    return 0;
  else
    return node->height;
}

int AVLTree::get_balance_factor(Node *node) {
  if (node == nullptr)
    return 0;
  else
    return get_height(node->left) - get_height(node->right);
}

AVLTree::Node *AVLTree::rotate_right(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(get_height(y->left), get_height(y->right)) + 1;
  x->height = max(get_height(x->left), get_height(x->right)) + 1;

  return x;
}

AVLTree::Node *AVLTree::rotate_left(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(get_height(x->left), get_height(x->right)) + 1;
  y->height = max(get_height(y->left), get_height(y->right)) + 1;

  return y;
}

void AVLTree::insert(int key, int value) {
  root = insert_node(root, key, value);
}

AVLTree::Node *AVLTree::insert_node(Node *node, int key, int value) {
  if (node == nullptr)
    return new Node(key, value);

  if (key < node->data.key)
    node->left = insert_node(node->left, key, value);
  else if (key > node->data.key)
    node->right = insert_node(node->left, key, value);
  else {
    node->data.value = value;
    return node;
  }

  node->height = 1 + max(get_height(node->left), get_height(node->right));

  int balance = get_balance_factor(node);

  if (balance > 1 && key < node->left->data.key)
    return rotate_right(node);

  if (balance < -1 && key > node->left->data.key)
    return rotate_left(node);

  if (balance > 1 && key > node->left->data.key) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  }

  if (balance < -1 && key < node->right->data.key) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}

void AVLTree::remove(int key) { root = remove_node(root, key); }

AVLTree::Node *AVLTree::find_min(Node *node) {
  Node *current = node;
  while (current->left != nullptr)
    current = current->left;
  return current;
}
AVLTree::Node *AVLTree::remove_node(Node *node, int key) {
  if (node == nullptr)
    return node;

  if (key < data->key)
    node->left = remove_node(node->left, key);
  else if (key > data->key)
    node->right = remove_node(node->right, key);
  else {
    if ((node->left == nullptr) || (node->right == nullptr)) {
      Node *temp;
      if (node->left != nullptr) {
        temp = node->left;
      } else {
        temp = node->right;
      }

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      Node *temp = find_min(node->right);
      node->data.key = temp->data.key;
      node->data.value = temp->data.value;
      node->right = remove_node(node->right, temp->data.key);
    }
  }
  if (node == nullptr)
    return node;

  node->height = 1 + max(get_height(node->left), get_height(node->right));

  int balance = get_balance_factor(node);

  if (balance > 1 && get_balance_factor(node->left) >= 0)
    return rotate_right(node);

  if (balance > 1 && get_balance_factor(node->left) < 0)
    return rotate_right(node);

  if (balance < -1 && get_balance_factor(node->right) <= 0)
    return rotate_right(node);

  if (balance < -1 && get_balance_factor(node->right) > 0) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}
