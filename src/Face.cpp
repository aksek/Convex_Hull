// Kosek, Convex_Hull

#include"Face.hpp"

#include"Triangle.hpp"
#include"Vertex.hpp"

Face::Face(Triangle T, std::vector<Vertex *> V) {
    triangle = Triangle(T.A(), T.B(), T.C());
    vertices = V;
}
