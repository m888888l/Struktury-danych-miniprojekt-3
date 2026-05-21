#pragma once

struct Element {
  int value;
  int key;
};

class Base {
public:
  virtual void insert(int value, int key) = 0;
  virtual Element extract_max() = 0;
  virtual Element find_max() = 0;
  virtual int return_size() = 0;
  virtual void modify_key(int value, int key) = 0;
  virtual void print() = 0;
  virtual ~Base() = default;
};
