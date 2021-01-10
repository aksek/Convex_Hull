#include <stdexcept>

#include"Point.hpp"
#include"Vector.hpp"

Point::Point() : x{0}, y{0}, z{0} {}
Point::Point(int x_coordinate, int y_coordinate, int z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
int Point::X() const {return x;}
int Point::Y() const {return y;}
int Point::Z() const {return z;}

bool Point::under(Plane &plane) {
    return plane.A() * x + plane.B() * y + plane.C() * z + plane.D() < 0;
}
bool Point::over(Plane &plane) {
    return plane.A() * x + plane.B() * y + plane.C() * z + plane.D() > 0;
}
bool Point::on(Plane &plane) {
    return plane.A() * x + plane.B() * y + plane.C() * z + plane.D() == 0;
}
bool Point::operator==(const Point &that) const {
    if (this->x != that.X() || this->y != that.Y() || this->z != that.Z() ) return false;
    else return true;
}
bool Point::inside(Point *A, Point *B, Point *C, Plane &plane) {

    if (!this->on(plane)) return false;
    
    Vector v0 = *C - *A;
    Vector v1 = *B - *A;
    Vector v2 = *this - *A;

    int dot00 = v0.dot(v0);
    int dot01 = v0.dot(v1);
    int dot02 = v0.dot(v2);
    int dot11 = v1.dot(v1);
    int dot12 = v1.dot(v2);

    double denom = (dot00 * dot11 - dot01 * dot01);
    double alpha = (dot11 * dot02 - dot01 * dot12) / denom;
    double betha = (dot00 * dot12 - dot01 * dot02) / denom;
    double gamma = 1 - alpha - betha;

    return alpha >= 0.0f && betha >= 0.0f && gamma >= 0.0f;
}
Vector Point::operator-(const Point &that) const {
    int u = this->x - that.X();
    int v = this->y - that.Y();
    int w = this->z - that.Z();
    return Vector(u, v, w);
}
std::ostream &operator<<(std::ostream &os, const Point &P) {
    return os << '(' << P.X() << ", " << P.Y() << ", " << P.Z() << ')';
}

Point& Point::operator+(Vector &that) {
    this->x = this->x + that.X();
    this->y = this->y + that.Y();
    this->z = this->z + that.Z();
    return *this;
}