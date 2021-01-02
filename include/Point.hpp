#ifndef POINT_H
#define POINT_H

#include<iostream>
#include"Vector.hpp"
#include"Plane.hpp"

class Point{
private:
    int x, y, z;
public:
    Point();
    Point(int x_coordinate, int y_coordinate, int z_coordinate);
    int X() const;
    int Y() const;
    int Z() const;
    bool under(Plane &plane);
    bool over(Plane &plane);
    bool on(Plane &plane);
    bool inside(Point *A, Point *B, Point *C, Plane &plane);

    bool operator==(const Point &that) const;
    Vector operator-(const Point &that) const;
};
std::ostream &operator<<(std::ostream &os, const Point &P);

#endif //POINT_H