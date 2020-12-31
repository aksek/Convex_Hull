#include<vector>

#include<boost/functional/hash.hpp>

#include"Triangle.hpp"

using namespace std;

Triangle::Triangle(Point *a_pointer, Point *b_pointer, Point *c_pointer) {
    a = a_pointer;
    b = b_pointer;
    c = c_pointer;
}
Point* Triangle::A() const {return a;}
Point* Triangle::B() const {return b;}
Point* Triangle::C() const {return c;}

bool Triangle::operator==(const Triangle &that) const {
    if (this->a != that.A() || this->b != that.B() || this->c != that.C() ) return false;
    else return true;
}
std::ostream &operator<<(std::ostream &os, const Triangle &T) {
    return os << '(' << *T.A() << ", " << *T.B() << ", " << *T.C() << ')';
}

struct triangle_hash {
    size_t operator()(const Triangle &T) const {
        boost::hash<std::vector<int> > vector_hash;
        vector<int> indices;
        indices.push_back(T.A()->X());
        indices.push_back(T.A()->Y());
        indices.push_back(T.A()->Z());
        indices.push_back(T.B()->X());
        indices.push_back(T.B()->Y());
        indices.push_back(T.B()->Z());
        indices.push_back(T.C()->X());
        indices.push_back(T.C()->Y());
        indices.push_back(T.C()->Z());
        return vector_hash(indices);
    }
};