#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<iostream>
#include"Point.hpp"
#include "Edge.hpp"
#include <list>

class Triangle {
private:
    int a, b, c;        // pointers to Points
public:
    Triangle(int a_index, int b_index, int c_index);
    int A() const;
    int B() const;
    int C() const;

    bool operator==(const Triangle &that) const;

    Vector normal(std::vector<Point> &points);
    std::list<Edge> edges(std::vector<Point> &points);
    double surface(std::vector<Point> &points);
};
std::ostream &operator<<(std::ostream &os, const Triangle &T);
struct triangle_hash;

#endif //TRIANGLE_H