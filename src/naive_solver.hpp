#ifndef NAIVE_SOLVER_H
#define NAIVE_SOLVER_H

#include<vector>

#include"Point.hpp"
#include"Triangle.hpp"

class Naive_solver {
public:
    // Naive_solver();
    std::vector<Triangle> solve(std::vector<Point> &points);
};

#endif //NAIVE_SOLVER_H