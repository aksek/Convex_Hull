#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"

int main() {
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
    std::cout << std::endl;
    // Naive_solver solver;
    // vector<Triangle> convex_hull = solver.solve(points);
    // for (int i = 0; i < convex_hull.size(); i++) {
    //     cout << convex_hull[i].A() << convex_hull[i].B() << convex_hull[i].C() << endl;
    // }
    std::cout << Triangle(&points[0], &points[1], &points[2]) << std::endl;
}