#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"
#include "naive_solver.hpp"
#include "data_converter.hpp"
#include "data_generator.hpp"
#include "gift_wrapping.hpp"
#include "Edge.hpp"
#include "timer.hpp"

int main() {
    
    data_generator g;
    data_converter c;
    int d = 1;
    std::string cmd = "python3 ./src/visualize.py";

    g.generate_data(1000, 10000);
    std::vector<Point> points = c.load();
    Preprocessing::voxelize(points, d);
    gift_wrapping solver;
    std::vector<Triangle> convex_hull = solver.solve(points);
    c.save(points, convex_hull);
    ::popen(cmd.c_str(), "r");

    // timer t;
    // std::string cmd = "python3 ./src/time.py";

    // t.measure_time(2, 100, 200);
    // ::popen(cmd.c_str(), "r");
}