#include "timer.hpp"

void timer::measure_time(int x_number, int cycle_per_point, int min_point_number, int max_point_number) {

    int step = (max_point_number - min_point_number) / (x_number - 1);
    //Naive_solver naive;
    //Quickhull_solver quickhull;
    data_generator g;
    data_converter c;
    std::vector<Point> points;
    std::string naive_time;
    std::string line;
    std::vector<std::string> lines;
    std::fstream file;

    lines.push_back("x,y_quickhull");

    for(int i = min_point_number; i <= max_point_number; i += step) {

        std::vector<double> times;
        line = std::to_string(i);
        line += ",";
        
        for(int j = 0; j < cycle_per_point; ++j) {
            
            Incremental_solver incremental;
            g.generate_sphere_data(i, i);
            points = c.load();
            Preprocessing::voxelize(points, 1);

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            incremental.solve(points);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> time_span = end - start;

            times.push_back(time_span.count());

            std::cout << "Point: " << i << " Cycle: " << j << std::endl;
        }

        double miliseconds = 0;

        for(auto time : times) {

            miliseconds += time;
        }

        miliseconds = miliseconds / times.size();
        line += std::to_string(miliseconds);
        lines.push_back(line);
    }

    file.open("./data/time_data.txt", std::ios::out);
    
    for(std::string s : lines)
        file << s << std::endl;

    file.close();
}
