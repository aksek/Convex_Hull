#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<iostream>
#include"Point.hpp"

class Triangle {
private:
    int a, b, c;        // pointers to Points
public:
    Triangle(int a_index, int b_index, int c_index);
    int A() const;
    int B() const;
    int C() const;

    bool operator==(const Triangle &that) const;
};
std::ostream &operator<<(std::ostream &os, const Triangle &T);
struct triangle_hash;

#endif //TRIANGLE_H