#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<iostream>
#include"Point.hpp"
#include "Edge.hpp"

class Triangle {
private:
    int a, b, c;        // pointers to Points
public:
    Triangle();
    Triangle(int a_index, int b_index, int c_index);
    int A() const;
    int B() const;
    int C() const;

    bool operator==(const Triangle &that) const;

    Vector normal(std::vector<Point> &points);
    std::vector<Edge> edges(std::vector<Point> &points);
};
bool operator<(const Triangle &l, const Triangle &r);
std::ostream &operator<<(std::ostream &os, const Triangle &T);
struct triangle_hash;

#endif //TRIANGLE_H