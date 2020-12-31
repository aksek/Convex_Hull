#include"Point.hpp"

Point::Point() : x{0}, y{0}, z{0} {}
Point::Point(int x_coordinate, int y_coordinate, int z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
int Point::X() const {return x;}
int Point::Y() const {return y;}
int Point::Z() const {return z;}

bool Point::operator==(const Point &that) const {
    if (this->x != that.X() || this->y != that.Y() || this->z != that.Z() ) return false;
    else return true;
}
std::ostream &operator<<(std::ostream &os, const Point &P) {
    return os << '(' << P.X() << ", " << P.Y() << ", " << P.Z() << ')';
}