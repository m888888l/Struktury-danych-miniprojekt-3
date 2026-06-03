#pragma once
#include <fstream>
#include <string>
#include <sstream>

struct Element {
  int value = 0;
  int key = -1;
};

class Base {
public:
  virtual void insert(int value, int key) = 0;
  virtual Element remove(int key) = 0;
  virtual void print() = 0;
  virtual ~Base() = default;
  void load_from_file(std::string fileName, char separator);
  int hash(int key, int size);
};
