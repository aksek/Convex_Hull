#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<iostream>
#include"Point.hpp"

class Triangle {
private:
    Point *a, *b, *c;        // pointers to Points
public:
    Triangle(Point *a_pointer, Point *b_pointer, Point *c_pointer);
    Point* A() const;
    Point* B() const;
    Point* C() const;
    bool operator==(const Triangle &that) const;
};
std::ostream &operator<<(std::ostream &os, const Triangle &T);
struct triangle_hash;

#endif //TRIANGLE_H