#include<iostream>
#include<vector>
#include<unordered_set>

#include "Point.hpp"
#include "Triangle.hpp"
#include "preprocessing.hpp"
#include "naive_solver.hpp"

using namespace std;

int main() {
    int d = 2;
    int n = 10;
    vector<Point> points = {Point(0, 0, 0),
                            Point(0, 0, 1),
                            Point(3, 3, 0),
                            Point(4, 6, 0),
                            Point(-1, 2, 0),
                            Point(10, 0, 10),
                            Point(0, 10, 0),
                            Point(0, 11, 0),
                            Point(0, 12, 0)};
    Preprocessing::voxelize(points, d);
    for (int i = 0; i < points.size(); i++) {
        cout << points[i] << endl;
    }
    Naive_solver solver;
    unordered_set<Triangle, Triangle::hash> convex_hull = solver.solve(points);
    for (auto it = convex_hull.begin(); it != convex_hull.end(); it++) {
        cout << points[it->A] << " " << points[it->B] << " " << points[it->C] << endl;
    }
}