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

Vector Triangle::normal(std::vector<Point> &points) { 

    Vector temp1 = points[this->C()] - points[this->A()];
    Vector temp2 = points[this->B()] - points[this->A()];
    
    return temp2 * temp1;
    
}

std::list<Edge> Triangle::edges(std::vector<Point> &points) {

    Edge temp;
    std::list<Edge> edges;

    temp.setStart(points[this->a]);
    temp.setDirection(points[this->b] - points[this->a]);
    temp.setEnd(points[this->b]);

    edges.push_back(temp);

    temp.setStart(points[this->b]);
    temp.setDirection(points[this->c] - points[this->b]);
    temp.setEnd(points[this->c]);

    edges.push_back(temp);

    temp.setStart(points[this->c]);
    temp.setDirection(points[this->a] - points[this->c]);
    temp.setEnd(points[this->a]);

    edges.push_back(temp);
    
    return edges;
}

double Triangle::surface(std::vector<Point> &points) {

    double a0, b0, c0;
    a0 = (points[a] - points[b]).magnitude();
    b0 = (points[b] - points[c]).magnitude();
    c0 = (points[c] - points[a]).magnitude();
    double p = (a0 + b0 + c0) / 2;
    return std::sqrt(p * (p - a0) * (p - b0) * (p - c0));
}