#include<vector>
#include<unordered_map>

#include<boost/functional/hash.hpp>

#include"quickhull_solver.hpp"
#include"Triangle.hpp"
#include"Point.hpp"
#include"Plane.hpp"
#include"Vector.hpp"

using namespace std;

struct point_hash {
    size_t operator()(const Point &P) const {
        boost::hash<std::vector<int> > vector_hash;
        vector<int> coors;
        coors.push_back(P.X());
        coors.push_back(P.Y());
        coors.push_back(P.Z());
        return vector_hash(coors);
    }
};

list<Triangle> quickhull(int A, int B, int C, vector<Point> &points, unordered_map<Point, int, point_hash> &remaining) {
    list<Triangle> convex_hull;

    // 3.1. Jeżeli P jest pusty - koniec
    if (points.empty()) return convex_hull;

    // 3.2. Jeżeli P ma jeden element, ten punkt należy do otoczki - koniec
    if (points.size() == 1) {
        convex_hull.push_back(Triangle(A, B,(remaining.begin())->second));
        convex_hull.push_back(Triangle(B, C,(remaining.begin())->second));
        convex_hull.push_back(Triangle(C, A,(remaining.begin())->second));
        return convex_hull;
    }
    // 3.3. Znaleźć w P punkt D najbardziej oddalony od płaszczyzny ABC.
    Plane planeABC(points[A], points[B], points[C]);
    double max = 0;
    int maxIndex;
    double distance;
    for (auto it = remaining.begin(); it != remaining.end(); it++) {
        distance = planeABC.distance(it->first);
        if (distance > max) {
            max = distance;
            maxIndex = (it->second);
        }
    }
    Point D = points[maxIndex];
    // 3.4. Punkt D należy do otoczki wypukłej
    // 3.5. Znaleźć zbiory S1, S2, S3 leżące odpowiednio na zewnątrz (względem wielościanu) płaszczyzn
    // ABD, BCD, CAD. Punkty leżące na zewnątrz więcej niż jednej płaszczyzny mogą być dodane do
    // dowolnego zbioru. Pozostałe punkty nie mogą należeć do otoczki wypukłej i są odrzucane
    unordered_map<Point, int, point_hash> S_ABD, S_BCD, S_CAD;
    Point P;
    for (auto it = remaining.begin(); it != remaining.end(); it++) {
        P = it->first;
        if ((P).on_outer_side(points[A], points[B], D)) S_ABD.insert(*it);
        else if ((P).on_outer_side(points[B], points[C], D)) S_BCD.insert(*it);
        else if ((P).on_outer_side(points[C], points[A], D)) S_CAD.insert(*it);
    }
    // 3.6. Wywołać rekurencyjnie quickhull(A, B, D, S1), quickhull(B, C, D, S2), quickhull(C, A, D, S3)
    convex_hull.merge(quickhull(A, B, maxIndex, points, S_ABD));
    convex_hull.merge(quickhull(B, C, maxIndex, points, S_BCD));
    convex_hull.merge(quickhull(C, A, maxIndex, points, S_CAD));
    return convex_hull;
}

vector<Triangle> solve(vector<Point> &points) {
    // 1. Znaleźć w zbiorze punktów 3 punkty skrajne
    int max_index_x = 0, min_index_x = 0;
    int max_x = INT_MAX, min_x = INT_MIN;
    unordered_map<Point, int, point_hash> remaining;
    for (int i = 0; i < points.size(); i++) {
        Point cur = points[i];
        remaining.emplace(cur, i);
        if (cur.X() > max_x) {
            max_x = cur.X();
            max_index_x = i;
        }
        if (cur.X() < min_x) {
            min_x = cur.X();
            min_index_x = i;
        }
    }
    Point max_x_point = points[max_index_x];
    Point min_x_point = points[min_index_x];

    int max_dist_index;
    double max_distance = 0;
    double distance_numerator, distance_denominator, distance;
    for (int i = 0; i < points.size(); i++) {
        distance_numerator = ((max_x_point - min_x_point) * (min_x_point - points[i])).length();
        distance_denominator = (max_x_point - min_x_point).length();
        distance = distance_numerator / distance_denominator;
        if (distance > max_distance) {
            max_distance = 0;
            max_dist_index = i;
        }
    }
    Point max_dist_point = points[max_dist_index];
    // 2. Podzielić zbiór na dwa podzbiory S1 i S2, znajdujące się nad i pod płaszczyzną ABC
    Plane max_plane(max_x_point, min_x_point, max_dist_point);
    unordered_map<Point, int, point_hash> upper, lower;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].over(max_plane)) upper.emplace(points[i], i);
        else if (points[i].under(max_plane)) lower.emplace(points[i], i);
    }
    // 3. Wywołać quickhull(A, B, C, S1) i quickhull(C, B, A, S2) (argumenty: A, B, C, P)
    list<Triangle> convex_hull = quickhull(max_index_x, min_index_x, max_dist_index, points, upper);
    convex_hull.merge(quickhull(max_index_x, max_dist_index, min_index_x, points, lower));
    vector<Triangle> convex_hull_vector;
    convex_hull_vector.assign(convex_hull.begin(), convex_hull.end());
    return convex_hull_vector;
}