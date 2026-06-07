#include "AVLTree.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>

using namespace std;

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() { destroy_tree(root); }

void AVLTree::destroy_tree(Node *node) {
  if (node != nullptr) {
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

int AVLTree::get_height(Node *node) {
  return node == nullptr ? 0 : node->height;
}

int AVLTree::get_balance_factor(Node *node) {
  return node == nullptr ? 0 : get_height(node->left) - get_height(node->right);
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

bool AVLTree::insert(int value, int key) {
  bool added = false;
  root = insert_node(root, key, value, added);
  return added; // Zwraca true jeśli dodano nowy węzeł, false jeśli
                // zaktualizowano wartość
}

AVLTree::Node *AVLTree::insert_node(Node *node, int key, int value,
                                    bool &added) {
  if (node == nullptr) {
    added = true;
    return new Node(value, key);
  }

  if (key < node->data.key)
    node->left = insert_node(node->left, key, value, added);
  else if (key > node->data.key)
    node->right =
        insert_node(node->right, key, value, added); // Tu był błąd z node->left
  else {
    node->data.value = value; // Klucz istnieje, nadpisujemy wartość
    return node;
  }

  node->height = 1 + max(get_height(node->left), get_height(node->right));
  int balance = get_balance_factor(node);

  if (balance > 1 && key < node->left->data.key)
    return rotate_right(node);

  if (balance < -1 && key > node->right->data.key)
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

Element AVLTree::remove(int key) {
  Element removed_el;
  root = remove_node(root, key, removed_el);
  return removed_el;
}

AVLTree::Node *AVLTree::find_min(Node *node) {
  Node *current = node;
  while (current->left != nullptr)
    current = current->left;
  return current;
}

AVLTree::Node *AVLTree::remove_node(Node *node, int key, Element &removed_el) {
  if (node == nullptr)
    return node;

  if (key < node->data.key) // Tu był błąd z data->key
    node->left = remove_node(node->left, key, removed_el);
  else if (key > node->data.key) // Tu był błąd z data->key
    node->right = remove_node(node->right, key, removed_el);
  else {
    if (removed_el.key == -1)
      removed_el = node->data; // Zapisujemy usuwany element

    if ((node->left == nullptr) || (node->right == nullptr)) {
      Node *temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp; // Kopiujemy zawartość jedynego dziecka
      }
      delete temp;
    } else {
      Node *temp = find_min(node->right);
      node->data.key = temp->data.key;
      node->data.value = temp->data.value;
      node->right = remove_node(node->right, temp->data.key, removed_el);
    }
  }

  if (node == nullptr)
    return node;

  node->height = 1 + max(get_height(node->left), get_height(node->right));
  int balance = get_balance_factor(node);

  if (balance > 1 && get_balance_factor(node->left) >= 0)
    return rotate_right(node);

  if (balance > 1 && get_balance_factor(node->left) < 0) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  }

  if (balance < -1 && get_balance_factor(node->right) <= 0)
    return rotate_left(node);

  if (balance < -1 && get_balance_factor(node->right) > 0) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}

void AVLTree::print() { print_in_order(root); }

void AVLTree::print_in_order(Node *node) {
  if (node == nullptr)
    return;
  print_in_order(node->left);
  cout << "  (" << node->data.key << "; " << node->data.value << ")\n";
  print_in_order(node->right);
}

void AVLTree::fill_array(Element *arr, int &index) {
  fill_array_recursive(root, arr, index);
}

void AVLTree::fill_array_recursive(Node *node, Element *arr, int &index) {
  if (node == nullptr)
    return;
  fill_array_recursive(node->left, arr, index);
  arr[index++] = node->data;
  fill_array_recursive(node->right, arr, index);
}
