#ifndef PLANE_H
#define PLANE_H

class Plane {
private:
    int a, b, c, d;
public:
    Plane();
    Plane(int a_coefficient, int b_coefficient, int c_coefficient, int d_coefficient);
    int A() const;
    int B() const;
    int C() const;
    int D() const;
};

#endif //PLANE_H