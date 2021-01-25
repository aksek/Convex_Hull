// Kowalski, Convex_Hull

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>

class data_generator {

public:

    data_generator() = default;
    ~data_generator() = default;
    unsigned generate_number();
    void generate_normal_distribution(double point_number, double range);
    void generate_cube_data(int point_number, int edge_lenght);
    void generate_sphere_data(int point_number, double radius);
};

#endif
