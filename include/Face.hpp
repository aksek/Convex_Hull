#ifndef FACE_H
#define FACE_H

#include<vector>

#include<Triangle.hpp>

class Vertex;

class Face {
public:
    Triangle triangle;
    std::vector<Vertex *> vertices;

    Face(Triangle T, std::vector<Vertex *> V);
};

#endif //FACE_H