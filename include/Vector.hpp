// Kosek, Convex_Hull

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>
#include "comparator.hpp"

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
    double dot_x_y(const Vector &that) const; 
    double length();
    double magnitude();
    double magnitude_x_y();
    Vector(const Vector &v) {x = v.x; y = v.y; z = v.z;} 
    Vector& operator = (const Vector &v);
};
std::ostream &operator<<(std::ostream &os, const Vector &P);


#endif //VECTOR_H
