#include<vector>

#include<boost/functional/hash.hpp>

#include"Triangle.hpp"

using namespace std;

Triangle::Triangle(int a_index, int b_index, int c_index) {
    a = a_index;
    b = b_index;
    c = c_index;
}
int Triangle::A() const {return a;}
int Triangle::B() const {return b;}
int Triangle::C() const {return c;}

bool Triangle::operator==(const Triangle &that) const {
    if (this->a != that.A() || this->b != that.B() || this->c != that.C() ) return false;
    else return true;
}
bool operator<(const Triangle &l, const Triangle &r) {      // completely arbitrary, exists for std::list<Triangle>'s sake
    return l.A() < r.A();
}
std::ostream &operator<<(std::ostream &os, const Triangle &T) {
    return os << '(' << T.A() << ", " << T.B() << ", " << T.C() << ')';
}

struct triangle_hash {
    size_t operator()(const Triangle &T) const {
        boost::hash<std::vector<int> > vector_hash;
        vector<int> indices;
        indices.push_back(T.A());
        indices.push_back(T.B());
        indices.push_back(T.C());
        return vector_hash(indices);
    }
};