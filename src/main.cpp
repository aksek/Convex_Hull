#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"
#include "naive_solver.hpp"
#include "data_converter.hpp"
#include "data_generator.hpp"

int main() {
    
    data_generator g;
    data_converter c;
    int d = 1;
    std::string cmd = "python3 ./src/visualize.py";

    g.generate_data(100, 100);
    std::vector<Point> points = c.load();
    if (d > 1) Preprocessing::voxelize(points, d);
    Naive_solver solver;
    std::vector<Triangle> convex_hull = solver.solve(points);
    c.save(points, convex_hull);
    ::popen(cmd.c_str(), "r");
}