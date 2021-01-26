// Kosek, Convex_Hull

#ifndef POINT_H
#define POINT_H

#include<iostream>
#include "comparator.hpp"

class Vector;
class Plane;

class Point{
private:
    double x, y, z;
public:
    Point();
    Point(double x_coordinate, double y_coordinate, double z_coordinate);
    double X() const;
    double Y() const;
    double Z() const;
    bool on_outer_side(const Point A, const Point B, const Point C) const;   //A, B, C represent a triangle, whose outer side is the one where the points are seen in this order clockwise
    bool on_inner_side(Point A, Point B, Point C) const;
    bool under(Plane &plane) const;
    bool over(Plane &plane) const;
    bool on(Plane &plane) const;
    bool under(double A, double B, double C) const;     // line parameters
    bool over(double A, double B, double C) const;     // line parameters
    bool inside(Point *A, Point *B, Point *C, Plane &plane) const;

    bool operator==(const Point &that) const;
    Vector operator-(const Point &that) const;
    Point operator+(const Vector &that) const;
    Point(const Point &p) {x = p.x; y = p.y; z = p.z;}
    Point& operator = (const Point &p);
};
std::ostream &operator<<(std::ostream &os, const Point &P);


#endif //POINT_H
