// Kosek, Convex_Hull

#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include <math.h>

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
    double magnitude();
    Vector(const Vector &v) {x = v.x; y = v.y; z = v.z;} 
    Vector& operator = (const Vector &v) {
        
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }  
};
std::ostream &operator<<(std::ostream &os, const Vector &P);

#endif //VECTOR_H
