// Kosek, Convex_Hull

#include<vector>
#include<unordered_map>

#include<boost/functional/hash.hpp>

#include "quickhull_solver.hpp"

#include "Triangle.hpp"
#include "Polyhedron.hpp"
#include "Vector.hpp"
#include "Plane.hpp"
#include "Vertex.hpp"

using namespace std;

struct point_hash {
    size_t operator()(const Point &P) const {
        boost::hash<std::vector<int> > vector_hash;
        std::vector<int> coors;
        coors.push_back(P.X());
        coors.push_back(P.Y());
        coors.push_back(P.Z());
        return vector_hash(coors);
    }
};

vector<Triangle> Quickhull_solver::solve(vector<Point> &points) {
    Point max_x_point, min_x_point;
    unsigned max_x_index, min_x_index;
    double max_x = -INFINITY, min_x = INFINITY;
    for (unsigned i = 0; i < points.size(); i++) {
        if (points[i].X() > max_x) {
            max_x = points[i].X();
            max_x_point = points[i];
            max_x_index = i;
        }
        if (points[i].X() < min_x) {
            min_x = points[i].X();
            min_x_point = points[i];
            min_x_index = i;
        }
    }

    // initial simplex
    Vertex* A = new Vertex(&max_x_point, max_x_index);
    
    Vertex* B = new Vertex(&min_x_point, min_x_index);

    Vector AB = *(B->point) - *(A->point);
    double max_dist_lin = 0;
    Point max_dist_lin_point;
    unsigned max_dist_lin_index;
    double distance;
    for (unsigned i = 0; i < points.size(); i++) {
        Vector CA = *(A->point) - (points[i]);
        distance = (CA * AB).length() / AB.length();
        if (distance > max_dist_lin && i != max_x_index && i != min_x_index) {
            max_dist_lin = distance;
            max_dist_lin_point = points[i];
            max_dist_lin_index = i;
        }
    }
    Vertex* C = new Vertex(&max_dist_lin_point, max_dist_lin_index);

    Plane ABC(*(A->point), *(B->point), *(C->point));

    double max_dist_plan = 0;
    Point max_dist_plan_point;
    unsigned max_dist_plan_index;
    for (unsigned i = 0; i < points.size(); i++) {
        distance = ABC.distance(points[i]);
        if (distance > max_dist_plan && i != max_x_index && i != min_x_index && i != max_dist_lin_index) {
            max_dist_plan = distance;
            max_dist_plan_point = points[i];
            max_dist_plan_index = i;
        }
    }
    Vertex* D = new Vertex(&max_dist_plan_point, max_dist_plan_index);

    Polyhedron convex_hull(A, B, C, D);

    convex_hull.init_conflict_graph(points);

    // Vertex* current;
    // for (int i = 0; i < points.size(); i++) {
    //     // if (convex_hull.contains(it->first)) continue;

    //     current = new Vertex(&points[i], i);
    //     convex_hull.add_vertex(current, points);
    // }

    double max_dist;
    int max_dist_index;
    Vertex* current;
    bool modified = true;
    while(modified) {
        modified = false;
        for (auto it = convex_hull.face_graph.begin(); it != convex_hull.face_graph.end() && !modified; it++) {
            if (!(*it)->conflicting_points.empty()) {

                Plane face_plane(*((*it)->vertices[0]->point), *((*it)->vertices[1]->point), *((*it)->vertices[2]->point));

                max_dist = 0;
                for (auto jt = (*it)->conflicting_points.begin(); jt != (*it)->conflicting_points.end(); jt++) {
                    distance = face_plane.distance(points[*jt]);
                    if (distance > max_dist) {
                        max_dist = distance;
                        max_dist_index = *jt;
                    }
                }
                current = new Vertex(&points[max_dist_index], max_dist_index);
                convex_hull.add_vertex(current, points);
                
                modified = true;
            }
        }
    }


    vector<Triangle> result;
    convex_hull.get_triangles(result);
    return result;
}
