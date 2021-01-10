#ifndef PLANE_H
#define PLANE_H

// #include "Point.hpp"
class Point;

class Plane {
private:
    int a, b, c, d;
public:
    Plane();
    Plane(int a_coefficient, int b_coefficient, int c_coefficient, int d_coefficient);
    Plane(Point &A, Point &B, Point &C);
    int A() const;
    int B() const;
    int C() const;
    int D() const;
    double distance(const Point &P) const;
};

#endif //PLANE_H