#pragma once
#include "naive_solver.hpp"
#include "data_generator.hpp"
#include "data_converter.hpp"
#include <chrono>
#include <sstream>
#include <vector>

class timer {

public:
    timer() = default;
    ~timer() = default;
    void measure_time(int x_number, int min_point_number, int max_point_number);
};