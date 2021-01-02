#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H
#include <random>
#include <chrono>
#include <fstream>

class data_generator {

public:

    data_generator() = default;
    ~data_generator() = default;
    unsigned generate_number();
    void generate_data(int point_number, int range);
};

#endif