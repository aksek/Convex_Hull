#include"Point.hpp"
#include"Vector.hpp"

Point::Point() : x{0}, y{0}, z{0} {}
Point::Point(int x_coordinate, int y_coordinate, int z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
int Point::X() const {return x;}
int Point::Y() const {return y;}
int Point::Z() const {return z;}

bool Point::under(int a, int b, int c, int d) {         // a b c d - coefficients of a plane
    return a * x + b * y + c * z + d < 0;
}
bool Point::over(int a, int b, int c, int d) {         // a b c d - coefficients of a plane
    return a * x + b * y + c * z + d > 0;
}
bool Point::under(int a, int b, int c) {                // a b c - line coefficients
    return a * x + b * y + c < 0;
}
bool Point::over(int a, int b, int c) {                // a b c - line coefficients
    return a * x + b * y + c > 0;
}
bool Point::operator==(const Point &that) const {
    if (this->x != that.X() || this->y != that.Y() || this->z != that.Z() ) return false;
    else return true;
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