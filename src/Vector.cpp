#include"Vector.hpp"

Vector::Vector() : x{0}, y{0}, z{0} {}
Vector::Vector(double x_coordinate, double y_coordinate, double z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
double Vector::X() const {return x;}
double Vector::Y() const {return y;}
double Vector::Z() const {return z;}

Vector Vector::operator*(const Vector &that) const {
    double u = this->y * that.Z() - this->z * that.Y();
    double v = this->z * that.X() - this->x * that.Z();
    double w = this->x * that.Y() - this->y * that.X();
    return Vector(u, v, w);
}  
double Vector::dot(const Vector &that) const {
    double u = this->x * that.X();
    double v = this->y * that.Y();
    double w = this->z * that.Z();
    return u + v + w;
}
bool Vector::operator==(const Vector &that) const {
    if (this->x != that.X() || this->y != that.Y() || this->z != that.Z() ) return false;
    else return true;
}
std::ostream &operator<<(std::ostream &os, const Vector &V) {
    return os << '(' << V.X() << ", " << V.Y() << ", " << V.Z() << ')';
}

double Vector::magnitude() {

    double temp = pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
    
    return sqrt(temp);
}