#ifndef QUICKHULL_SOLVER_H
#define QUICKHULL_SOLVER_H

#include<vector>
#include<unordered_map>

#include<boost/functional/hash.hpp>

#include"Point.hpp"
#include"Triangle.hpp"

struct point_hash;

class Quickhull_solver {
private:
    std::list<Triangle> quickhull(int A, int B, int C, std::vector<Point> &points, std::unordered_map<Point, int, point_hash> &remaining);
public:
    std::vector<Triangle> solve(std::vector<Point> &points);
};

#endif //QUICKHULL_SOLVER_H