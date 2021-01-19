#ifndef PLANE_H
#define PLANE_H

// #include "Point.hpp"
class Point;

class Plane {
private:
    double a, b, c, d;
public:
    Plane();
    Plane(double a_coefficient, double b_coefficient, double c_coefficient, double d_coefficient);
    Plane(const Point &A, const Point &B, const Point &C);
    double A() const;
    double B() const;
    double C() const;
    double D() const;
    double distance(const Point &P) const;
};

#endif //PLANE_H