#include"Plane.hpp"

Plane::Plane() {
    Plane(0, 0, 0, 0);
}
Plane::Plane(int a_coefficient, int b_coefficient, int c_coefficient, int d_coefficient) {
    a = a_coefficient;
    b = b_coefficient;
    c = c_coefficient;
    d = d_coefficient;
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