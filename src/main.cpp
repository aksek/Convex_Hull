#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"
#include "naive_solver.hpp"
#include "data_converter.hpp"
#include "data_generator.hpp"

using namespace std;

int main() {
    
    data_generator g;
    g.generate_data(100, 100);
    data_converter c;
    c.save(c.load());
    
    int d = 1;
    int n = 5;
    std::vector<Point> points = {Point(-1, 4, 0),
                            Point(3, -2, 0),
                            Point(0, 0, 8),
                            Point(-3, 0, 0),
                            Point(0, 0, 1)};

    if (d > 1) Preprocessing::voxelize(points, d);
    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i] << std::endl;
    }
    cout << endl;
    Naive_solver solver;
    vector<Triangle> convex_hull = solver.solve(points);
    for (int i = 0; i < convex_hull.size(); i++) {
        cout << convex_hull[i] << endl;
    }
}