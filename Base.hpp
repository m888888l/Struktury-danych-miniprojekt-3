#pragma once

struct Element {
  int value;
  int key;
};

class Base {
public:
  virtual void insert(int value, int key) = 0;
  virtual Element remove(int key) = 0;
  virtual void print() = 0;
  virtual ~Base() = default;
};
