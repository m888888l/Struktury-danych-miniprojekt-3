#include "Base.hpp"
using namespace std;

void Base::load_from_file(std::string fileName, char separator){
    ifstream file(fileName);
    if (!file.is_open())
        return;

    string line;

    while (getline(file, line)){
        stringstream ss(line);

        string valueStr;
        string keyStr;

        if (getline(ss, valueStr, separator) && getline(ss, keyStr, separator)){
        insert(stoi(valueStr), stoi(keyStr));
        }
    }
    file.close();
}

int Base::hash(int key, int size){
    return key % size;
}