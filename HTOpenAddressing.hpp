#pragma once

#include "Base.hpp"

class HTOpenAddressing : public Base {
    public:
    HTOpenAddressing(int size);
    ~HTOpenAddressing();
    void insert(int value, int key);
    Element remove(int key);
    void print();

    private:
    int size;
    int capacity;
    float load_factor();
    void resize();
    Element* data;
};