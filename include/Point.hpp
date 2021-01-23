#ifndef POINT_H
#define POINT_H

#include<iostream>
#include"Vector.hpp"
#include"Plane.hpp"
#include"Vector.hpp"
#include "comparator.hpp"

class Point{
private:
    double x, y, z;
public:
    Point();
    Point(double x_coordinate, double y_coordinate, double z_coordinate);
    double X() const;
    double Y() const;
    double Z() const;
    bool under(Plane &plane);
    bool over(Plane &plane);
    bool on(Plane &plane);
    bool inside(Point *A, Point *B, Point *C, Plane &plane);

    bool operator==(const Point &that) const;
    Vector operator-(const Point &that) const;
    Point operator+(const Vector &that) const;
    Point(const Point &p) {x = p.x; y = p.y; z = p.z;}
    Point& operator = (const Point &p) {
        
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
};
std::ostream &operator<<(std::ostream &os, const Point &P);

#endif //POINT_H