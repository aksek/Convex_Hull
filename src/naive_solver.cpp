#include<vector>
#include<unordered_set>

#include"Triangle.hpp"
#include"Point.hpp"
#include"Vector.hpp"

using namespace std;

unordered_set<Triangle, Triangle::hash> solve(vector<Point> &points) {
    unordered_set<Triangle, Triangle::hash> convex_hull;
    Triangle current;
    bool all_under;      // the point is under a triangle if the point is on the triangle's inner side
    bool all_over;       // likewise, outer side
    Vector AB, AC, normal;
    int k;
    for(int A = 0; A < points.size() - 2; A++) {

        for (int B = 1; B < points.size() - 1; B++) {
            AB = points[B] - points[A];

            for (int C = 2; C < points.size(); C++) {
                AC = points[C] - points[A];
                normal = AC * AB;                    // coordinates of the normal vector == coefficients of the plane
                k = -(normal.X() * points[A].X() + normal.Y() * points[A].Y() + normal.Z() * points[A].Z()); //last coefficient

                all_under = true, all_over = true;
                for(int i = 0; i < points.size(); i++) {
                    if (points[i].under(normal.X(), normal.Y(), normal.Z(), k)) all_over = false;       // not all points are over the triangle
                    else all_under = false;                                                             // not all points are under the triangle
                }
                if (all_under) convex_hull.emplace(Triangle(A, B, C));
                if (all_over) convex_hull.emplace(Triangle(A, C, B));
            }
        }
    }
    return convex_hull;
}