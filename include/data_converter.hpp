#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H
#include <iostream>
#include <vector>
#include "Point.hpp"
#include "Triangle.hpp"
#include <fstream>
#include <algorithm>

class data_converter {

public:
    
    data_converter() = default;
    ~data_converter() = default;

    std::vector<Point> load(std::string input_file = "./data/input.txt");
    void save(std::vector<Point> data, std::vector<Triangle> faces);
};

#endif