#pragma once

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "Base.hpp"
#include "HTOpenAddressing.hpp"
#include "HTSeparateChaining.hpp"
#include "HTAVLTree.hpp"

class Benchmark{
    public:
    Benchmark();
    ~Benchmark();

    void run();

    private:
    void fill_structure(int size, int seed, Base* structure);
    void write_result_to_file(std::ofstream &file, int size, const std::string &opName, int structure, const unsigned long long &time);
    Element* generate_values_to_add(int seed, int size);
    Base** create_structure_samples(int structure, int size);
};