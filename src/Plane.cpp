#include<math.h>

#include"Plane.hpp"
#include"Vector.hpp"
#include"Point.hpp"

Plane::Plane() {
    Plane(0, 0, 0, 0);
}
Plane::Plane(int a_coefficient, int b_coefficient, int c_coefficient, int d_coefficient) {
    a = a_coefficient;
    b = b_coefficient;
    c = c_coefficient;
    d = d_coefficient;
}
Plane::Plane(Point &A, Point &B, Point &C) {
    Vector AB = B - A;
    Vector AC = C - A;
    Vector normal = AB * AC;                    // coordinates of the normal vector == coefficients of the plane
    int k = -(normal.X() * A.X() + normal.Y() * A.Y() + normal.Z() * A.Z()); //last coefficient
    Plane(normal.X(), normal.Y(), normal.Z(), k);
}
int Plane::A() const {
    return a;
}
int Plane::B() const {
    return b;
}
int Plane::C() const {
    return c;
}
int Plane::D() const {
    return d;
}
double Plane::distance(const Point &P) const {
    int numerator = abs(a * P.X() + b * P.Y() + c * P.Z() + d);
    double denominator = sqrt(a * a + b * b + c * c);
    return (double)numerator / denominator;
}