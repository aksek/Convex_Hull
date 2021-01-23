#pragma once
#include "Vector.hpp"
#include "Point.hpp"
#include <algorithm>

class Edge {

    Point start;
    Point end;
    Vector direction;

public:

    void setEnd(Point end) {
        this->end = end;
    }
    
    Point& getEnd() {
        return end;
    }

    void setStart(Point start);
    const Point& getStart() const;
    const Vector& getDirection() const;
    void setDirection(Vector direction);
    Edge() = default;
    ~Edge() = default;
    bool operator==(const Edge &that) const;
    Edge(const Edge &e) {start = e.start; direction = e.direction; end = e.end;} 
    Edge& operator=(const Edge &e) {
        
        start = e.start;
        direction = e.direction;
        end = e.end;
        return *this;
    } 
};