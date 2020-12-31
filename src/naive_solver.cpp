#include<vector>
#include<unordered_set>

#include"naive_solver.hpp"

#include"Triangle.hpp"
#include"Point.hpp"
#include"Vector.hpp"

using namespace std;

vector<Triangle> Naive_solver::solve(vector<Point> &points) {
    vector<Triangle> convex_hull;
    bool all_under;      // the point is under a triangle if the point is on the triangle's inner side
    bool all_over;       // likewise, outer side
    Vector AB, AC, normal;
    int k;
    for(int A = 0; A < points.size() - 2; A++) {

        for (int B = A + 1; B < points.size() - 1; B++) {
            AB = points[B] - points[A];

            for (int C = B + 1; C < points.size(); C++) {

                AC = points[C] - points[A];
                normal = AC * AB;                    // coordinates of the normal vector == coefficients of the plane
                k = -(normal.X() * points[A].X() + normal.Y() * points[A].Y() + normal.Z() * points[A].Z()); //last coefficient

                all_under = true, all_over = true;
                for(int i = 0; i < points.size(); i++) {
                    if (i == A || i == B || i == C) continue;

                    if (normal.Z() < 0) {
                        if (points[i].under(normal.X(), normal.Y(), normal.Z(), k)) all_over = false;       // not all points are over the triangle
                        else all_under = false;                                                            // not all points are under the triangle
                    } else if (normal.Z() > 0) {
                        if (points[i].under(normal.X(), normal.Y(), normal.Z(), k)) all_under = false;       // not all points are under the triangle
                        else all_over = false;     
                    }  // else if sprowadza się do płaszczyzny                                     
                }
                if (all_under) convex_hull.push_back(Triangle(&points[A], &points[B], &points[C]));
                if (all_over) convex_hull.push_back(Triangle(&points[A], &points[C], &points[B]));
            }
        }
    }
    return convex_hull;
}