#include "Edge.hpp"

Point& Edge::getStart() {
    return start;
}

void Edge::setStart(Point start) {
    this->start = start;
}

Vector& Edge::getDirection() {
    return direction;
}

void Edge::setDirection(Vector direction) {
    this->direction = direction;
}

bool Edge::operator==(Edge &that) {
    
    if(this->getDirection() == that.getDirection() && this->getStart() == that.getStart())
        return true;
    
    return (this->getStart() + this->getDirection()) == that.getStart() || (that.getStart() + that.getDirection()) == this->getStart();
}