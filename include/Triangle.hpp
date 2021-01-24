#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<iostream>
#include"Point.hpp"
#include "Edge.hpp"

class Triangle {
private:
    unsigned int a, b, c; 
public:
    Triangle();
    Triangle(unsigned a_index, unsigned b_index, unsigned c_index);
    unsigned A() const;
    unsigned B() const;
    unsigned C() const;

    bool operator==(const Triangle &that) const;

    Vector normal(std::vector<Point> &points);
    std::vector<Edge> edges(std::vector<Point> &points);
};
bool operator<(const Triangle &l, const Triangle &r);
std::ostream &operator<<(std::ostream &os, const Triangle &T);
struct triangle_hash;

#endif //TRIANGLE_H