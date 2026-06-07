#include <iostream>
#include "Benchmark.hpp"
#include "HTOpenAddressing.hpp"
#include "HTSeparateChaining.hpp"
#include "HTAVLTree.hpp"
#include "cstdlib"

using namespace std;

int main(){
    Benchmark test;

    test.run();
    int choice;

    while(1){
        system("cls");
        cout<<"1. Adresowanie Otwarte\n2. Kubelki z lisa\n3. Drzewo AVL\n4. Benchmark\n5. Wyjdz\n";
        cin>>choice;
        Base* structure;
        if(choice == 1) structure = new HTOpenAddressing(10);
        else if(choice == 2) structure = new HTSeparateChaining(10);
        else if(choice == 3) structure = new HTAVLTree(10);
        else if(choice == 4) {Benchmark benchmark; benchmark.run(); break;}
        else if(choice == 5) break;
        else continue;
        system("cls");
        while(choice != 4){
            cout << "1. Dodaj element\n2. Wyswietl strukture\n3. Zaladuj wartosci z pliku\n4. Wyczysc strukture i wyjdz\n";
            cin>>choice;
            system("cls");
            if(choice == 1){
                int key = 0;
                int value = 0;
                cout<<"Klucz: "; cin >>key;
                cout<<"Wartosc: "; cin >>value;
                structure->insert(value, key);
            }
            else if(choice == 2) structure->print();
            else if(choice == 3){
                string file_name{};
                char separator{};
                cout<<"Nazwa pliku: "; cin>>file_name;
                cout<<"Separator: "; cin>>separator;
                structure->load_from_file(file_name, separator);
            }
            else if(choice == 4) delete structure;
        }
    }


return 0;
}