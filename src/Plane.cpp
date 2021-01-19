#include<math.h>

#include"Plane.hpp"
#include"Vector.hpp"
#include"Point.hpp"

Plane::Plane() {
    Plane(0, 0, 0, 0);
}
Plane::Plane(double a_coefficient, double b_coefficient, double c_coefficient, double d_coefficient) {
    a = a_coefficient;
    b = b_coefficient;
    c = c_coefficient;
    d = d_coefficient;
}
Plane::Plane(const Point &A, const Point &B, const Point &C) {
    Vector AB = B - A;
    Vector AC = C - A;
    Vector normal = AB * AC;                    // coordinates of the normal vector == coefficients of the plane
    double k = -(normal.X() * A.X() + normal.Y() * A.Y() + normal.Z() * A.Z()); //last coefficient
    // Plane(normal.X(), normal.Y(), normal.Z(), k);
    a = normal.X();
    b = normal.Y();
    c = normal.Z();
    d = k;
}
double Plane::A() const {
    return a;
}
double Plane::B() const {
    return b;
}
double Plane::C() const {
    return c;
}
double Plane::D() const {
    return d;
}
double Plane::distance(const Point &P) const {
    double numerator = abs(a * P.X() + b * P.Y() + c * P.Z() + d);
    double denominator = sqrt(a * a + b * b + c * c);
    return numerator / denominator;
}