// Kosek, Convex_Hull

#ifndef NAIVE_SOLVER_H
#define NAIVE_SOLVER_H

#include<vector>

#include"Point.hpp"
#include"Triangle.hpp"

class Naive_solver {
public:
    std::vector<Triangle> solve(std::vector<Point> &points);
};

#endif //NAIVE_SOLVER_H
