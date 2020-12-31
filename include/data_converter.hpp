#ifndef DATA_CONVERTER_H
#define DATA_CONVERTER_H
#include<iostream>
#include<vector>
#include "Point.hpp"
#include <fstream>

class data_converter {

public:
    
    data_converter() = default;
    ~data_converter() = default;

    std::vector<Point> load();
    void save(std::vector<Point> data);
};

#endif