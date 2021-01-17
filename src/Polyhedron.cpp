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

Face * Polyhedron::push_face_correct_side(Vertex* V, Vertex* A, Vertex* B, Vertex* C) {
    Face *face;
    vector<Vertex *> vertices;
    vertices.push_back(A);
    if ((*V->point).on_inner_side(*A->point, *B->point, *C->point)) {
        vertices.push_back(B);
        vertices.push_back(C);
        face = new Face(Triangle(A->index, B->index, C->index), vertices);

    } else {
        vertices.push_back(C);
        vertices.push_back(B);
        face = new Face(Triangle(A->index, C->index, B->index), vertices);
    }
    face_graph.insert(face);
    A->faces.insert(face);
    B->faces.insert(face);
    C->faces.insert(face);

    return face;
}

Polyhedron::Polyhedron(Vertex* A, Vertex* B, Vertex* C, Vertex* D) {
    vertex_graph.insert(A);
    vertex_graph.insert(B);
    vertex_graph.insert(C);
    vertex_graph.insert(D);

    push_face_correct_side(D, A, B, C);
    push_face_correct_side(A, D, B, C);
    push_face_correct_side(B, A, D, C);
    push_face_correct_side(C, A, B, D);

    min_x = INT_MAX, min_y = INT_MAX, min_z = INT_MAX;
    max_x = INT_MIN, max_y = INT_MIN, max_z = INT_MIN;
    Point cur;
    for (auto it = vertex_graph.begin(); it != vertex_graph.end(); it++) {
        // cur = *vertex_graph[i]->point;
        cur = *(*it)->point;

        if (cur.X() < min_x) min_x = cur.X();
        if (cur.Y() < min_y) min_y = cur.Y();
        if (cur.Z() < min_z) min_z = cur.Z();

        if (cur.X() > max_x) max_x = cur.X();
        if (cur.Y() > max_y) max_y = cur.Y();
        if (cur.Z() > max_z) max_z = cur.Z();
    }

}
Polyhedron::~Polyhedron() {
    for (auto it = vertex_graph.begin(); it != vertex_graph.end(); it++) {
        delete *it;
    }
    for (auto it = face_graph.begin(); it != face_graph.end(); it++) {
        delete *it;
    }
}

bool Polyhedron::contains(Point P) {
    if (P.X() < min_x || P.X() > max_x) return false;
    if (P.Y() < min_y || P.Y() > max_y) return false;
    if (P.Z() < min_z || P.Z() > max_z) return false;
    
    Point A, B, C;
    for (auto it = face_graph.begin(); it != face_graph.end(); it++) {
        
        Face *F = *it;
        A = *F->vertices[0]->point;
        B = *F->vertices[0]->point;
        C = *F->vertices[0]->point;
        if (P.on_outer_side(A, B, C)) return false;
    }
    return true;
}


void Polyhedron::add_vertex(Vertex *V, vector<Point> &points) {
    // delete conflicting faces and save their vertices
    unordered_set<Vertex *> border_vertices;
    unordered_set<int> potential_conflicts;
    unordered_set<Face *> conflicting_faces = conflict_graph[V->index];
    if (conflicting_faces.empty()) return;

    // for (int i = 0; i < conflicting_faces.size(); i++) {
    for (auto face_iter = conflicting_faces.begin(); face_iter != conflicting_faces.end(); face_iter++) {

        for (int j = 0; j < (*face_iter)->vertices.size(); j++){

            (*face_iter)->vertices[j]->faces.erase(*face_iter);
            border_vertices.insert((*face_iter)->vertices[j]);
        }
        for (auto it = (*face_iter)->conflicting_points.begin(); it != (*face_iter)->conflicting_points.end(); it++) {
            potential_conflicts.insert(*it);
            conflict_graph[*it].erase((*face_iter));
        }
        face_graph.erase(*face_iter);
        delete (*face_iter);
    }

    // all vertices that have no faces are not a part of the border of the hole
    unordered_set<Vertex *>::iterator temp;
    for (auto it = border_vertices.begin(); it != border_vertices.end(); ) {
        if ((*it)->faces.empty()) {
            temp = it++;
            border_vertices.erase(temp);
        } else it++;
    }
    // put the vertices in order
    vector<Vertex *> ordered_border_vertices;
    ordered_border_vertices.push_back(*border_vertices.begin());
    border_vertices.erase(border_vertices.begin());
    bool found_next = false;
    
    Vertex *current = nullptr;

    while(!border_vertices.empty()) {
        Vertex *last = current;
        current = ordered_border_vertices.back();

        unordered_map<Vertex *, int> occurences;        // to make sure that the inserted vertex belongs to only one face

        for (auto it = current->faces.begin(); it != current->faces.end(); it++) {

            for (auto jt = (*it)->vertices.begin(); jt != (*it)->vertices.end(); jt++) {

                if (*jt == current || *jt == last) continue;
                if (!border_vertices.count(*jt))  continue;

                if (!occurences.count(*jt)) occurences.insert(make_pair(*jt, 1));
                else occurences[*jt]++;
            }
        }
        for (auto it = occurences.begin(); it != occurences.end(); it++) {
            if (it->second == 1) {
                ordered_border_vertices.push_back(it->first);
                border_vertices.erase(it->first);
                break;
            }
        }
    }
    // create new faces
    Face *new_face;
    Face *neighbour_face;
    int second, reference;
    for (int i = 0; i < ordered_border_vertices.size(); i++) {
        second = (i + 1) % ordered_border_vertices.size();
        reference = (i + 2) % ordered_border_vertices.size();

        new_face = push_face_correct_side(ordered_border_vertices[reference], V, ordered_border_vertices[i], ordered_border_vertices[second]);
        V->faces.insert(new_face);

        // update conflicts

        // find the neighbour face
        neighbour_face = nullptr;
        for (auto it = ordered_border_vertices[i]->faces.begin(); it != ordered_border_vertices[i]->faces.end() && neighbour_face == nullptr; it++) {
            bool found_second = false, found_another = false;
            for (auto jt = (*it)->vertices.begin(); jt != (*it)->vertices.end() && neighbour_face == nullptr; jt++) {
                if (*jt == ordered_border_vertices[second]) {
                    found_second = true;
                }
                if (*jt != ordered_border_vertices[i] && *jt != ordered_border_vertices[second] && *jt != V) {
                    found_another = true;
                }
            }
            if (found_second && found_another) {
                neighbour_face = *it;
            }
        }
        // points of the new face's vertices
        const Point A = *(new_face->vertices[0]->point);
        const Point B = *(new_face->vertices[1]->point);
        const Point C = *(new_face->vertices[2]->point);
        // add all conflicting points of the neighbour face that conflict with the new face to the new face's conflicts
        for (auto it = neighbour_face->conflicting_points.begin(); it != neighbour_face->conflicting_points.end(); it++) {
            if (points[*it].on_outer_side(A, B, C)) {
                new_face->conflicting_points.insert(*it);
                conflict_graph[*it].insert(new_face);
            }
        }
        // add all points that conflicted with the erased faces that conflict with the new face to the new face's conflicts
        for (auto it = potential_conflicts.begin(); it != potential_conflicts.end(); it++) {
            if (points[*it].on_outer_side(A, B, C)) {
                new_face->conflicting_points.insert(*it);
                conflict_graph[*it].insert(new_face);
            }
        }
    }
    vertex_graph.insert(V);
}

void Polyhedron::get_triangles(std::vector<Triangle> &triangles) {
    triangles.clear();
    for (auto it = face_graph.begin(); it != face_graph.end(); it++) {
        triangles.push_back((*it)->triangle);
    }
}

void Polyhedron::init_conflict_graph(vector<Point> &points) {
    unordered_set<Face *> temp;
    Face *face;
    for (int i = 0; i < points.size(); i++) {
        conflict_graph.insert(make_pair(i, temp));
        for (auto it = face_graph.begin(); it != face_graph.end(); it++) {
            face = *it;
            if (points[i].on_outer_side(*face->vertices[0]->point, *face->vertices[1]->point, *face->vertices[2]->point)) {
                conflict_graph[i].insert(face);
                face->conflicting_points.insert(i);
            }
        }
    }
}