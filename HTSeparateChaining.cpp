#include <iostream>
#include <algorithm>
#include "HTSeparateChaining.hpp"

HTSeparateChaining::HTSeparateChaining(int size) : capacity(size), size(0){
    data = new Element*[capacity]{};
    bucket_size = new int[capacity]{};
}

HTSeparateChaining::~HTSeparateChaining(){
    for(int i = 0; i < capacity; i++){
        delete[] data[i];
    }
    delete[] data;
    delete[] bucket_size;
}

void HTSeparateChaining::insert(int value, int key){
    if(load_factor() >= 1.5) resize();

    int i = hash(key, capacity);

    for(int j = 0; j < bucket_size[i]; j++){//jesli istnieje juz element z podanym kluczem, nadpisuje go
        if(data[i][j].key == key){
            data[i][j].value = value;
            return;
        }
    }

    Element* new_bucket = new Element[bucket_size[i] + 1];

    for(int j = 0; j < bucket_size[i]; j++){
        new_bucket[j] = data[i][j];
    }

    new_bucket[bucket_size[i]] = {value, key};

    delete[] data[i];
    data[i] = new_bucket;

    bucket_size[i]++;
    size++;
}

Element HTSeparateChaining::remove(int key){
    int i = hash(key, capacity);

    if (bucket_size[i] == 0) {
        return Element{};
    }

    Element* new_bucket = new Element[bucket_size[i] - 1]{};

    Element temp{};
    bool found = false;
    int k = 0;

    for (int j = 0; j < bucket_size[i]; j++) {
        if (data[i][j].key == key && !found) {
            temp = data[i][j];
            found = true;
            continue;
        }

        new_bucket[k++] = data[i][j];
    }

    if (!found) {
        delete[] new_bucket;
        return Element{};
    }

    delete[] data[i];
    data[i] = new_bucket;

    bucket_size[i]--;
    size--;

    return temp;
}

void HTSeparateChaining::print(){
    for(int i = 0; i < capacity; i++){
        for(int j = 0; j < bucket_size[i]; j++){
            std::cout<<"["<<i<<"]"<<"("<<data[i][j].key<<"; "<<data[i][j].value<<")\n";
        }
    }
}

float HTSeparateChaining::load_factor(){return 1.0f * size / capacity;}

void HTSeparateChaining::resize() {
    int old_capacity = capacity;
    Element** old_data = data;
    int* old_bucket_size = bucket_size;

    capacity = std::max(size * 2, 2);

    data = new Element*[capacity]{};
    bucket_size = new int[capacity]{};

    for (int i = 0; i < capacity; i++) {
        data[i] = nullptr;
    }

    for (int i = 0; i < old_capacity; i++) {
        for (int j = 0; j < old_bucket_size[i]; j++) {

            Element new_element = old_data[i][j];
            int index = hash(new_element.key, capacity);

            Element* new_bucket = new Element[bucket_size[index] + 1];

            for (int k = 0; k < bucket_size[index]; k++) {
                new_bucket[k] = data[index][k];
            }

            new_bucket[bucket_size[index]] = new_element;

            delete[] data[index];
            data[index] = new_bucket;

            bucket_size[index]++;
        }
    }

    for (int i = 0; i < old_capacity; i++) {
        delete[] old_data[i];
    }
    delete[] old_data;
    delete[] old_bucket_size;
}