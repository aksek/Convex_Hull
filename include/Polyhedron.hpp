#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include<vector>
#include<unordered_map>

class Face;
class Vertex;
class Point;
class Triangle;

struct vertex_ptr_hash;

class Polyhedron {
public:
    int min_x, max_x;
    int min_y, max_y;
    int min_z, max_z;
    std::vector<Face *> face_graph;
    std::vector<Vertex *> vertex_graph;
    std::unordered_map<Vertex *, std::vector<Face *> > conflict_graph;

    Polyhedron(Vertex* A, Vertex* B, Vertex* C, Vertex* D);
    ~Polyhedron();
    void push_face_correct_side(Vertex* V, Vertex* A, Vertex* B, Vertex* C);

    bool contains(Point P, std::vector<Point> &points);
    void add_vertex(Vertex V);
    void get_triangles(std::vector<Triangle> &triangles);
};

#endif //POLYHEDRON_H