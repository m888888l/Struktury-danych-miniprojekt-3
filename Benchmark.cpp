#include "Benchmark.hpp"

const int SIZES[8] = {500000, 1000000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000};
const int SAMPLES = 100;

Benchmark::Benchmark(){};
Benchmark::~Benchmark(){};

void Benchmark::fill_structure(int size, int seed, Base* structure){
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist_values(0, 100000);
    std::uniform_int_distribution<> dist_keys(0, size * 10);
    for(int i = 0; i < size; i++) structure->insert(dist_values(gen), dist_keys(gen));
}

Base** Benchmark::create_structure_samples(int structure, int size){
    Base** strucuture_samples = new Base*[SAMPLES];
    for(int i = 0; i < SAMPLES; i++){
        if(structure == 0) strucuture_samples[i] = new HTOpenAddressing(size);
        if(structure == 1) strucuture_samples[i] = new HTSeparateChaining(size);
        if(structure == 2) strucuture_samples[i] = new HTAVLTree(size);
    }
    return strucuture_samples;
}

Element* Benchmark::generate_values_to_add(int seed, int size){
    Element* values = new Element[SAMPLES];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist_values(0, 100000000);
    std::uniform_int_distribution<> dist_keys(0, size * 10);
    for(int i = 0; i < SAMPLES; i++) values[i] = {dist_values(gen), dist_keys(gen)};
    return values;
}

void Benchmark::write_result_to_file(std::ofstream &file, int size, const std::string &opName, int structure, const unsigned long long &time) {
    std::string structure_name;
    if(structure == 0) structure_name = "Open Addressing";
    else if(structure == 1) structure_name = "Seperate Chaining";
    else if(structure == 2) structure_name = "AVL Tree";
    file << size << ";" << opName << ";" << structure_name << ";" << time << "\n";
}

void Benchmark::run(){
    std::ofstream file("wyniki_testow.csv");
    file << "Rozmiar;Operacja;Struktura;czas[ns]\n";

    for(int const& size : SIZES){
        for(int structure = 0; structure < 3; structure++){
            auto start = std::chrono::high_resolution_clock::now();
            auto end = start;

            //insert()
            std::cout<<"Wypelnianie struktury "<< structure <<" dla insert, rozmiar "<<size<<"\n";
            Base** structure_samples = create_structure_samples(structure, size);
            for(int i = 0; i < SAMPLES; i++){
                fill_structure(size, size + i, structure_samples[i]);   //seed zalezy od size'a i numeru probki aby kazdy rozmiar i probka miala
            }                                                           //inne wartosci, ale kazda struktura ogolnie miala te same
            Element* values_to_add = generate_values_to_add(size, size); //tablica elementow do dodania do konkretnych probek
            
            std::cout<<"Testowanie insert dla struktury "<< structure <<", rozmiar "<<size<<"\n";

            start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < SAMPLES; i++){
                structure_samples[i]->insert(values_to_add[i].value, values_to_add[i].key);
            }
            end = std::chrono::high_resolution_clock::now();
            write_result_to_file(file, size, "insert", structure, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/SAMPLES);

            std::cout<<"Czysczenie struktury "<< structure <<", po insert rozmiar "<<size<<"\n";

            delete[] values_to_add;
            for(int i = 0; i < SAMPLES; i++){
                delete structure_samples[i];
            }
            delete[] structure_samples;

            //remove()

            std::cout<<"Wypelnianie struktury "<< structure <<" dla remove, rozmiar "<<size<<"\n";
            structure_samples = create_structure_samples(structure, size);
            for(int i = 0; i < SAMPLES; i++){
                fill_structure(size, size + i, structure_samples[i]);
            } 
            values_to_add = generate_values_to_add(size, size); //tablica losowych elementow, taka sama dla kazdej struktury, teraz
                                                                //bedzie uzyta do wyboru klucza do usuniecia
            std::cout<<"Testowanie remove dla struktury "<< structure <<", rozmiar "<<size<<"\n";

            start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < SAMPLES; i++){
                structure_samples[i]->remove(values_to_add[i].key);
            }
            end = std::chrono::high_resolution_clock::now();
            write_result_to_file(file, size, "remove", structure, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/100);

            std::cout<<"Czysczenie struktury "<< structure <<", po remove rozmiar "<<size<<"\n";

            delete[] values_to_add;
            for(int i = 0; i < SAMPLES; i++){
                delete structure_samples[i];
            }
            delete[] structure_samples;
        }
    }
}