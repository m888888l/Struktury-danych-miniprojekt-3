#pragma once

#include "Base.hpp"

class HTSeparateChaining : public Base {
    public:
    HTSeparateChaining(int size);
    ~HTSeparateChaining();
    void insert(int value, int key);
    Element remove(int key);
    void print();

    private:
    int size;
    int capacity;
    float load_factor();
    void resize();
    Element** data;
    int* bucket_size;
};