#ifndef NAIVE_SOLVER_H
#define NAIVE_SOLVER_H

#include<vector>
#include<unordered_set>

#include"Point.hpp"
#include"Triangle.hpp"

class Naive_solver {
public:
    // Naive_solver();
    std::unordered_set<Triangle, Triangle::hash> solve(std::vector<Point> &points);
};

#endif //NAIVE_SOLVER_H