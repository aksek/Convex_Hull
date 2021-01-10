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

int main() {
    
    data_generator g;
    data_converter c;
    int d = 1;
    std::string cmd = "python3 ./src/visualize.py";

    Edge e1, e2, e3, e4;
    e1.setDirection(Vector(1, 2, 3));
    e1.setStart(Point(0,0,0));

    e2.setDirection(Vector(-1, -2, -3));
    e2.setStart(Point(1,2,3));

    e3.setDirection(Vector(1, 2, 3));
    e3.setStart(Point(0,0,0));

    e4.setDirection(Vector(-1, -2, -3));
    e4.setStart(Point(-1,-2,-3));

    bool is_true = e1 == e2;
    bool is_true2 = e3 == e4;
    bool is_true3 = e2 == e4;
    bool is_true4 = e1 == e3;

    //g.generate_data(100, 100);
    std::vector<Point> points = c.load();
    if (d > 1) Preprocessing::voxelize(points, d);
    Naive_solver solver1;
    gift_wrapping solver;
    std::vector<Triangle> convex_hull = solver.solve(points);
    //std::vector<Triangle> convex_hull1 = solver1.solve(points);
    c.save(points, convex_hull);
    ::popen(cmd.c_str(), "r");
}