#ifndef FACE_H
#define FACE_H

#include<vector>
#include<unordered_set>

#include<Triangle.hpp>

class Vertex;

class Face {
public:
    Triangle triangle;
    std::vector<Vertex *> vertices;
    std::unordered_set<int> conflicting_points;

    Face(Triangle T, std::vector<Vertex *> V);
};

#endif //FACE_H