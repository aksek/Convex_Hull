#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

class Vector{
private:
    double x, y, z;
public:
    Vector();
    Vector(double x_coordinate, double y_coordinate, double z_coordinate);
    double X() const;
    double Y() const;
    double Z() const;
    bool operator==(const Vector &that) const;
    Vector operator*(const Vector &that) const;     //cross product
    double dot(const Vector &that) const;        //dot product
    double length();
};
std::ostream &operator<<(std::ostream &os, const Vector &P);

#endif //VECTOR_H