#include "data_generator.hpp"

unsigned data_generator::generate_number() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    return generator();
}

void data_generator::generate_data(int point_number, int range) {

    int x, y, z;
    std::fstream file;
    file.open( "./data/input.txt", std::ios::out );
    std::string line;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{5,1};

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