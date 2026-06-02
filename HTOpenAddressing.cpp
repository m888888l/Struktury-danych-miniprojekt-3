#include <iostream>
#include "HTOpenAddressing.hpp"

HTOpenAddressing::HTOpenAddressing(int size) : capacity(size * 1.5), size(0){
    data = new Element[capacity];
}

HTOpenAddressing::~HTOpenAddressing(){
    delete[] data;
}

int HTOpenAddressing::hash(int key, int size){
    return key % size;
}

void HTOpenAddressing::insert(int value, int key){
    if(load_factor() >= 0.7) resize();

    int i = hash(key, capacity);

    while(data[i].key != -1){
        i++;
        if(i >= capacity) i = 0;
    }

    data[i].value = value;
    data[i].key = key;

    size++;
}

Element HTOpenAddressing::remove(int key){
    int i = hash(key, capacity);
    while(data[i].key != key){
        i++;
        if(i >= capacity) i = 0;
    }

    return data[i];
    data[i].key = -1;

    size--;
}

void HTOpenAddressing::print(){
    for(int i = 0; i < capacity; i++){
        if(data[i].key != -1) std::cout<<"["<<i<<"]"<<"("<<data[i].key<<"; "<<data[i].value<<")\n";
    }
}

float HTOpenAddressing::load_factor(){return size / capacity;}

void HTOpenAddressing::resize(){
    int old_capacity = capacity;
    capacity = size * 1.5;
    Element* temp = new Element[capacity];
    for(int i = 0; i < old_capacity; i++){
        if(data[i].key == -1) continue;
        int j = hash(data[i].key, capacity);

        while(temp[j].key != -1){
            j++;
            if(j >= capacity) j = 0;
        }

        temp[j].key = data[i].key;
        temp[j].value = data[i].value;
    }

    delete[] data;
    data = temp;
}