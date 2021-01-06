#include<vector>
#include<unordered_map>

#include<boost/functional/hash.hpp>

#include"quickhull_solver.hpp"
#include"Triangle.hpp"
#include"Point.hpp"
#include"Plane.hpp"

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

vector<Triangle> quickhull(int A, int B, int C, vector<Point> &points, unordered_map<Point, int, point_hash> &remaining) {
    vector<Triangle> convex_hull;

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
        distance = planeABC.distance(*it->first);
        if (distance > max) {
            max = distance;
            maxIndex = (*it->second);
        }
    }
    // 3.4. Punkt D należy do otoczki wypukłej
    // 3.5. Znaleźć zbiory S1, S2, S3 leżące odpowiednio na zewnątrz (względem wielościanu) płaszczyzn
    // ABD, BCD, CAD. Punkty leżące na zewnątrz więcej niż jednej płaszczyzny mogą być dodane do
    // dowolnego zbioru. Pozostałe punkty nie mogą należeć do otoczki wypukłej i są odrzucane
    // 3.6. Wywołać rekurencyjnie quickhull(A, B, D, S1), quickhull(B, C, D, S2), quickhull(C, A, D, S3)
}

vector<Triangle> solve(vector<Point> &points) {
    unordered_map<Point, int, point_hash> remaining;
    for (int i = 0; i < points.size(); i++) {
        Point test = points[i];
        remaining.emplace(test, i);
    }
    // 1. Znaleźć w zbiorze punktów 3 punkty skrajne
    // 2. Podzielić zbiór na dwa podzbiory S1 i S2, znajdujące się nad i pod płaszczyzną ABC
    // 3. Wywołać quickhull(A, B, C, S1) i quickhull(C, B, A, S2) (argumenty: A, B, C, P)
}