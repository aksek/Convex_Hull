// Kowalski, Convex_Hull

#pragma once
#include "Vector.hpp"
#include "Point.hpp"
#include <algorithm>

class Edge {

    Point start;
    Vector direction;
    
public:

    void setStart(Point start);
    const Point& getStart() const;
    const Vector& getDirection() const;
    void setDirection(Vector direction);
    Edge() = default;
    ~Edge() = default;
    bool operator==(const Edge &that);
    Edge(const Edge &e) {start = e.start; direction = e.direction;} 
    Edge& operator=(const Edge &e);
};
