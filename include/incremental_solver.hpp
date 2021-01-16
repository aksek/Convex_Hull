#ifndef INCREMENTAL_SOLVER_H
#define INCREMENTAL_SOLVER_H

#include<vector>
#include<unordered_map>

class Triangle;
class Point;

struct point_hash;

class Incremental_solver {
private:
public:
    std::vector<Triangle> solve(std::vector<Point> &points);
};

#endif //INCREMENTAL_SOLVER_H