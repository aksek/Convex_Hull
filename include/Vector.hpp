#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

class Vector{
private:
    int x, y, z;
public:
    Vector();
    Vector(int x_coordinate, int y_coordinate, int z_coordinate);
    int X() const;
    int Y() const;
    int Z() const;
    bool operator==(const Vector &that) const;
    Vector operator*(const Vector &that) const;     //cross product
};
std::ostream &operator<<(std::ostream &os, const Vector &P);

#endif //VECTOR_H