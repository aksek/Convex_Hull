#include "data_generator.hpp"

unsigned data_generator::generate_number() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    return generator();
}

void data_generator::generate_normal_distribution(double point_number, double range) {

    int x, y, z;
    std::fstream file;
    file.open( "./data/input.txt", std::ios::out );
    std::string line;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{range,range/5};

    for(int i = 0; i < point_number; ++i) {

        x = d(gen);
        y = d(gen);
        z = d(gen);
        line = std::to_string(x);
        line += " ";
        line += std::to_string(y);
        line += " ";
        line += std::to_string(z);
        line += "\n";
        file << line;
    }

    file.close();
}

void data_generator::generate_cube_data(int point_number, int edge_lenght) {

    int x, y, z;
    std::fstream file;
    file.open( "./data/input.txt", std::ios::out );
    std::string line;
    std::random_device rd{};
    std::mt19937 gen{rd()};

    for(int i = 0; i < point_number; ++i) {

        x = gen() % edge_lenght;
        y = gen() % edge_lenght;
        z = gen() % edge_lenght;
        line = std::to_string(x);
        line += " ";
        line += std::to_string(y);
        line += " ";
        line += std::to_string(z);
        line += "\n";
        file << line;
    }

    file.close();
}

void data_generator::generate_sphere_data(int point_number, double radius) {

    int x, y, z;
    std::fstream file;
    file.open( "./data/input.txt", std::ios::out );
    std::string line;
    std::random_device rd{};
    std::mt19937 gen{rd()};

    for(int i = 0; i < point_number; ++i) {

        double a, b, r;
        a = gen();
        b = gen();
        r = gen();
        double sin_a = std::sin(a);
        x = std::cos(a) * std::cos(b) * std::fmod(r, radius);
        y = std::cos(a) * std::sin(b) * std::fmod(r, radius);
        z = std::sin(a) * std::fmod(r, radius);
        line = std::to_string(x);
        line += " ";
        line += std::to_string(y);
        line += " ";
        line += std::to_string(z);
        line += "\n";
        file << line;
    }

    file.close();
}