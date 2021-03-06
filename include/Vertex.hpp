// Kosek, Convex_Hull

#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<unordered_set>

#include"Point.hpp"
#include"Face.hpp"

struct point_hash;

class Vertex {
public:
    const Point *point;
    int index;
    std::unordered_set<Face *> faces;

    Vertex(const Point *point, int index);
};

#endif //VERTEX_H
