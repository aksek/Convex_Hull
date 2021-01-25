// Kosek, Convex_Hull

#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include<vector>
#include"Point.hpp"

class Preprocessing{
public:
    static void voxelize(std::vector<Point> &points, int d);
};


#endif //PREPROCESSING_H
