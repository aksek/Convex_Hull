// Kosek, Convex_Hull

#include<vector>
#include<unordered_map>

#include<boost/functional/hash.hpp>

#include "incremental_solver.hpp"

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

vector<Triangle> Incremental_solver::solve(vector<Point> &points) {
    unordered_map<Point, int, point_hash> random_order_points;
    for (unsigned i = 0; i < points.size(); i++) {
        random_order_points.insert(make_pair(points[i], i));
    }

    // initial simplex
    auto it = random_order_points.begin();
    Vertex* A = new Vertex(&it->first, it->second);
    it++;
    Vertex* B = new Vertex(&it->first, it->second);
    Vector AB = *(B->point) - *(A->point);
    do {
        it++;
    } while ((AB * (it->first - *(B->point))).length() == 0);        // the points are collinear

    Vertex* C = new Vertex(&it->first, it->second);
    Plane ABC(*(A->point), *(B->point), *(C->point));
    do {
        it++;
    } while ((it->first).on(ABC));   // the points are coplanar

    Vertex* D = new Vertex(&it->first, it->second);

    Polyhedron convex_hull(A, B, C, D);

    convex_hull.init_conflict_graph(points);

    Vertex* current;
    for (auto it = random_order_points.begin(); it != random_order_points.end(); it++) {

        current = new Vertex(&it->first, it->second);
        convex_hull.add_vertex(current, points);
    }

    vector<Triangle> result;
    convex_hull.get_triangles(result);
    return result;
}
