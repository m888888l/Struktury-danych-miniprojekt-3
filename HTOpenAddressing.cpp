#include <iostream>
#include "HTOpenAddressing.hpp"

HTOpenAddressing::HTOpenAddressing(int size) : capacity(size * 2), size(0){
    data = new Element[capacity]{};
}

HTOpenAddressing::~HTOpenAddressing(){
    delete[] data;
}



void HTOpenAddressing::insert(int value, int key){
    if(load_factor() >= 0.7) resize();

    int i = hash(key, capacity);
    int free_space = -1;
    int start = i;

    while(data[i].key != -1 && data[i].key != key){
        if(data[i].key == -2 && free_space == -1) free_space = i;
        i++;
        if(i >= capacity) i = 0;
        if(i == start) break;
    }

    if(data[i].key == -1){
        if(free_space != -1) data[free_space] = {value, key};
        else data[i] = {value, key};
        size++;
    }
    else data[i] = {value, key};
}

Element HTOpenAddressing::remove(int key){
    int i = hash(key, capacity);
    int j = 1;
    while(data[i].key != key && data[i].key != -1){
        i++;
        if(i >= capacity) i = 0;
    }
    if(data[i].key != key) return Element{};

    Element temp = data[i];
    data[i].key = -2;

    size--;
    return temp;
}

void HTOpenAddressing::print(){
    for(int i = 0; i < capacity; i++){
        if(data[i].key > -1) std::cout<<"["<<i<<"]"<<"("<<data[i].key<<"; "<<data[i].value<<")\n";
    }
}

float HTOpenAddressing::load_factor(){return 1.0f * size / capacity;}

void HTOpenAddressing::resize(){
    int old_capacity = capacity;
    capacity = size * 2;
    Element* temp = new Element[capacity]{};
    for(int i = 0; i < old_capacity; i++){
        if(data[i].key < 0) continue;
        int j = hash(data[i].key, capacity);

        while(temp[j].key != -1){
            j++;
            if(j >= capacity) j = 0;
        }

        temp[j] = {data[i].value, data[i].key};
    }

    delete[] data;
    data = temp;
}