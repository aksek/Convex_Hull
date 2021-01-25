// Kowalski, Convex_Hull

#include "data_converter.hpp"


std::vector<Point> data_converter::load() {

    std::fstream file;
    std::string temp;
    std::vector<Point> data;
    std::string x, y, z;

    file.open("./data/input.txt", std::ios::in);

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

void data_converter::save(std::vector<Point> data, std::vector<Triangle> faces) {

    std::fstream file;
    std::vector<std::string> lines;
    std::string line;
    int size = std::max(data.size(), faces.size());
    
    lines.reserve(size + 1);
    lines.push_back("x,y,z,i,j,k");

    for(int i = 0; i < size; ++i) {

        lines.push_back(",,,");
    }

    int i = 1;

    for(Point p : data) {

        line = std::to_string(p.X());
        line += ",";
        line += std::to_string(p.Y());
        line += ",";
        line += std::to_string(p.Z());
        line += ",";
        lines[i] = line;
        ++i;
    }

    i = 1;

    for(Triangle t : faces) {

        line = std::to_string(t.A());
        line += ",";
        line += std::to_string(t.B());
        line += ",";
        line += std::to_string(t.C());
        lines[i] += line;
        ++i;
    }

    file.open("./data/output.txt", std::ios::out);
    
    for(std::string s : lines)
        file << s << std::endl;

    file.close();
}
