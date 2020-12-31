#include<iostream>
#include<vector>

#include "Point.hpp"
#include "preprocessing.hpp"

using namespace std;

int main() {
    int d = 5;
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
}