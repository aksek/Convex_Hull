// Kosek, Convex_Hull

#include <stdexcept>

#include"Point.hpp"
#include"Vector.hpp"
#include"Plane.hpp"

Point::Point() : x{0}, y{0}, z{0} {}
Point::Point(double x_coordinate, double y_coordinate, double z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
double Point::X() const {return x;}
double Point::Y() const {return y;}
double Point::Z() const {return z;}

bool Point::on_outer_side(const Point A, const Point B, const Point C) const {
    Plane plane(A, B, C);
    Vector AB = B - A;
    Vector AC = C - A;
    Vector normal = AC * AB;        //points outwards
    if(normal.Z() > 0) {
        if (this->over(plane)) return true;
    } else if (normal.Z() < 0) {
        if (this->under(plane)) return true;
    } else {        // Z == 0 => the triangle is vertical and the plane is treated as a line 
        if (normal.Y() > 0) {
            if (this->over(plane.A(), plane.B(), plane.D())) return true;
        } else if (normal.Y() < 0) {
            if (this->under(plane.A(), plane.B(), plane.D())) return true;
        } else {    // Y == 0 => the triangle is perpendicular to the X axis
            if (normal.X() > 0) {
                if (this->X() > A.X()) return true;
            } else if (normal.X() < 0) {
                if (this->X() < A.X()) return true;
            }
        }
    }
    return false;
}
bool Point::on_inner_side(Point A, Point B, Point C) const {
    Plane plane(A, B, C);
    return !this->on_outer_side(A, B, C) && !this->on(plane);
}

bool Point::under(Plane &plane) const {
    return z < (-plane.A() * x - plane.B() * y - plane.D()) / plane.C();
}
bool Point::over(Plane &plane) const {
    return z > (-plane.A() * x - plane.B() * y - plane.D()) / plane.C();
}
bool Point::on(Plane &plane) const {
    return plane.A() * x + plane.B() * y + plane.C() * z + plane.D() == 0;
}
bool Point::under(double A, double B, double C) const {     // line
    return y < (- A * x - C) / B;
}
bool Point::over(double A, double B, double C) const {     // line
    return y > (- A * x - C) / B;
}
bool Point::operator==(const Point &that) const {
    if (!comparator::cmpfi(x, that.X()) || !comparator::cmpfi(y, that.Y()) || !comparator::cmpfi(z, that.Z()) ) return false;
    else return true;
}
bool Point::inside(Point *A, Point *B, Point *C, Plane &plane) const {

    if (!this->on(plane)) return false;
    
    Vector v0 = *C - *A;
    Vector v1 = *B - *A;
    Vector v2 = *this - *A;

    double dot00 = v0.dot(v0);
    double dot01 = v0.dot(v1);
    double dot02 = v0.dot(v2);
    double dot11 = v1.dot(v1);
    double dot12 = v1.dot(v2);

    double denom = (dot00 * dot11 - dot01 * dot01);
    double alpha = (dot11 * dot02 - dot01 * dot12) / denom;
    double betha = (dot00 * dot12 - dot01 * dot02) / denom;
    double gamma = 1 - alpha - betha;

    return alpha >= 0.0f && betha >= 0.0f && gamma >= 0.0f;
}
Vector Point::operator-(const Point &that) const {
    double u = this->x - that.X();
    double v = this->y - that.Y();
    double w = this->z - that.Z();
    return Vector(u, v, w);
}
std::ostream &operator<<(std::ostream &os, const Point &P) {
    return os << '(' << P.X() << ", " << P.Y() << ", " << P.Z() << ')';
}

Point Point::operator+(const Vector &that) const {
    double x = this->x + that.X();
    double y = this->y + that.Y();
    double z = this->z + that.Z();
    return Point(x, y, z);
}
Point& Point::operator= (const Point &p) { 
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}
