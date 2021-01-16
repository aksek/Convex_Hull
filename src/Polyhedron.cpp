#include<vector>

#include<boost/functional/hash.hpp>

#include "Polyhedron.hpp"

#include"Vertex.hpp"
#include"Face.hpp"
#include"Triangle.hpp"

using namespace std;

// struct vertex_ptr_hash {
//     size_t operator()(const Vertex *V) const {
//         boost::hash<std::vector<int> > vector_hash;
//         std::vector<int> coors;
//         coors.push_back(V->point->X());
//         coors.push_back(V->point->Y());
//         coors.push_back(V->point->Z());
//         return vector_hash(coors);
//     }
// };

void Polyhedron::push_face_correct_side(Vertex* V, Vertex* A, Vertex* B, Vertex* C) {
    Face *face;
    vector<Vertex *> vertices;
    vertices.push_back(A);
    if ((*V->point).on_inner_side(*A->point, *B->point, *C->point)) {
        vertices.push_back(B);
        vertices.push_back(C);
        face = new Face(Triangle(A->index, B->index, C->index), vertices);
        face_graph.push_back(face);

    } else {
        vertices.push_back(C);
        vertices.push_back(B);
        face = new Face(Triangle(A->index, C->index, B->index), vertices);
        face_graph.push_back(face);
    }
    A->faces.push_back(face_graph.back());
    B->faces.push_back(face_graph.back());
    C->faces.push_back(face_graph.back());
}

Polyhedron::Polyhedron(Vertex* A, Vertex* B, Vertex* C, Vertex* D) {
    vertex_graph.push_back(A);
    vertex_graph.push_back(B);
    vertex_graph.push_back(C);
    vertex_graph.push_back(D);

    push_face_correct_side(D, A, B, C);
    push_face_correct_side(A, D, B, C);
    push_face_correct_side(B, A, D, C);
    push_face_correct_side(C, A, B, D);

    min_x = INT_MAX, min_y = INT_MAX, min_z = INT_MAX;
    max_x = INT_MIN, max_y = INT_MIN, max_z = INT_MIN;
    Point cur;
    for (int i = 0; i < vertex_graph.size(); i++) {
        cur = *vertex_graph[i]->point;

        if (cur.X() < min_x) min_x = cur.X();
        if (cur.Y() < min_y) min_y = cur.Y();
        if (cur.Z() < min_z) min_z = cur.Z();

        if (cur.X() > max_x) max_x = cur.X();
        if (cur.Y() > max_y) max_y = cur.Y();
        if (cur.Z() > max_z) max_z = cur.Z();
    }

}
Polyhedron::~Polyhedron() {
    for (int i = 0; i < vertex_graph.size(); i++) {
        delete vertex_graph[i];
    }
    for (int i = 0; i < face_graph.size(); i++) {
        delete face_graph[i];
    }
}

bool Polyhedron::contains(Point P, vector<Point> &points) {
        if (P.X() < min_x || P.X() > max_x) return false;
        if (P.Y() < min_y || P.Y() > max_y) return false;
        if (P.Z() < min_z || P.Z() > max_z) return false;
        
        Point A, B, C;
        for (int i = 0; i < face_graph.size(); i++) {
            Triangle T = face_graph[i]->triangle;
            A = points[T.A()];
            B = points[T.B()];
            C = points[T.C()];

            if (P.on_outer_side(A, B, C)) return false;
        }
        return true;
    }


void Polyhedron::add_vertex(Vertex V) {
    // vertex_graph.push_back(V);
}

void Polyhedron::get_triangles(std::vector<Triangle> &triangles) {
    triangles.clear();
    for (int i = 0; i < face_graph.size(); i++) {
        triangles.push_back(face_graph[i]->triangle);
    }
}