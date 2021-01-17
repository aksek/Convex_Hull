#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include<vector>
#include<unordered_map>
#include<unordered_set>

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
    std::unordered_set<Face *> face_graph;
    std::unordered_set<Vertex *> vertex_graph;
    std::unordered_map<int, std::unordered_set<Face *> > conflict_graph;

    Polyhedron(Vertex* A, Vertex* B, Vertex* C, Vertex* D);
    ~Polyhedron();
    Face *push_face_correct_side(Vertex* V, Vertex* A, Vertex* B, Vertex* C);

    bool contains(Point P);
    void add_vertex(Vertex *V, std::vector<Point> &points);
    void get_triangles(std::vector<Triangle> &triangles);
    void init_conflict_graph(std::vector<Point> &points);
};

#endif //POLYHEDRON_H