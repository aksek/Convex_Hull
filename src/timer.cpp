#include "timer.hpp"

void timer::measure_time(int x_number, int min_point_number, int max_point_number) {

    int step = (max_point_number - min_point_number) / (x_number - 1);
    Naive_solver naive;
    data_generator g;
    data_converter c;
    std::vector<Point> points;
    std::string naive_time;
    std::string line;
    std::vector<std::string> lines;
    std::fstream file;

    lines.push_back("x,y_naive");

    for(int i = min_point_number; i <= max_point_number; i += step) {

        g.generate_data(i, 100);
        points = c.load();

        line = std::to_string(i);
        line += ",";

        auto start = std::chrono::system_clock::now();

        naive.solve(points);

        auto end = std::chrono::system_clock::now();

        std::time_t time2 = std::chrono::system_clock::to_time_t( start );
        std::time_t time1 = std::chrono::system_clock::to_time_t( end );
        auto seconds = time1 - time2;
        std::stringstream ss;
        ss << seconds;
        naive_time = ss.str();

        line += naive_time;

        lines.push_back(line);
    }

    file.open("./data/time_data.txt", std::ios::out);
    
    for(std::string s : lines)
        file << s << std::endl;

    file.close();
}
