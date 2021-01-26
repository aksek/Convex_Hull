// Kowalski, Convex_Hull

#include "Edge.hpp"

const Point& Edge::getStart() const {
    return start;
}

void Edge::setStart(Point start) {
    this->start = start;
}

const Vector& Edge::getDirection() const {
    return direction;
}

void Edge::setDirection(Vector direction) {
    this->direction = direction;
}

bool Edge::operator==(const Edge &that) {
    
    if(this->getDirection() == that.getDirection() && this->getStart() == that.getStart())
        return true;
    
    return (this->getStart() + this->getDirection()) == that.getStart() && (that.getStart() + that.getDirection()) == this->getStart();
}

Edge& Edge::operator=(const Edge &e) {
        
        start = e.start;
        direction = e.direction;
        return *this;
    }  
