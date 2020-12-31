#include "data_converter.hpp"

std::vector<Point> data_converter::load() {

    std::fstream file;
    std::string temp;
    std::vector<Point> data;
    std::string x, y, z;

    file.open( "./data/input.txt", std::ios::in );

    while(std::getline(file, temp)) {
        
        x = temp.substr(0, temp.find(" "));
        temp.erase(0, temp.find(" ") + 1);
        y = temp.substr(0, temp.find(" "));
        temp.erase(0, temp.find(" ") + 1);
        z = temp.substr(0, temp.find(" "));
        Point p(std::stoi(x), std::stoi(y), std::stoi(z));
        data.push_back(p);
    }

    file.close();
    return data;
}

void data_converter::save(std::vector<Point> data) {

    std::fstream file;
    std::string line;
    file.open( "./data/output.txt", std::ios::out );

    for( Point p : data ) {

        line += std::to_string(p.X());
        line += " ";
        line += std::to_string(p.Y());
        line += " ";
        line += std::to_string(p.Z());
        line += "\n";
    }
    file << line;
    file.close();
}