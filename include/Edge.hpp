#pragma once
#include "Vector.hpp"
#include "Point.hpp"

class Edge {

    Point start;
    Vector direction;
    
public:

    void setStart(Point start);
    Point& getStart();
    Vector& getDirection();
    void setDirection(Vector direction);
    Edge() = default;
    ~Edge() = default;
    bool operator==(Edge &that);
};