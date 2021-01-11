#include"Vector.hpp"

Vector::Vector() : x{0}, y{0}, z{0} {}
Vector::Vector(int x_coordinate, int y_coordinate, int z_coordinate) : x{x_coordinate}, y{y_coordinate}, z{z_coordinate} {}
int Vector::X() const {return x;}
int Vector::Y() const {return y;}
int Vector::Z() const {return z;}

Vector Vector::operator*(const Vector &that) const {
    int u = this->y * that.Z() - this->z * that.Y();
    int v = this->z * that.X() - this->x * that.Z();
    int w = this->x * that.Y() - this->y * that.X();
    return Vector(u, v, w);
}  
int Vector::dot(const Vector &that) const {
    int u = this->x * that.X();
    int v = this->y * that.Y();
    int w = this->z * that.Z();
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