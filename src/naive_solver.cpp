#include<vector>
#include<unordered_set>

#include"Triangle.hpp"
#include"Point.hpp"
#include"Vector.hpp"
#include"naive_solver.hpp"

using namespace std;

vector<Triangle> Naive_solver::solve(vector<Point> &points) {
    vector<Triangle> convex_hull;
    bool all_under;      // the point is under a triangle if the point is on the triangle's inner side
    bool all_over;       // likewise, outer side
    Vector AB, AC, normal;
    int k;
    Point current_point;
    for(int A = 0; A < points.size() - 2; A++) {

        for (int B = A + 1; B < points.size() - 1; B++) {
            AB = points[B] - points[A];

            for (int C = B + 1; C < points.size(); C++) {
                AC = points[C] - points[A];
                normal = AC * AB;                    // coordinates of the normal vector == coefficients of the plane
                k = -(normal.X() * points[A].X() + normal.Y() * points[A].Y() + normal.Z() * points[A].Z()); //last coefficient

                all_under = true, all_over = true;
                for(int i = 0; i < points.size(); i++) {
                    current_point = points[i];
                    if (i == A || i == B || i == C) continue;

                    if (current_point.under(normal.X(), normal.Y(), normal.Z(), k)) {                       // not all points are over the triangle
                        all_over = false;
                        cout << i << ": " << current_point << " under " << A << ' ' << B << ' ' << C << endl;
                    } else {                                                                            // not all points are under the triangle
                        all_under = false;
                        cout << i << ": " << current_point << " over " << A << ' ' << B << ' ' << C << endl;  
                    }                                                             
                }
                if (all_under) convex_hull.push_back(Triangle(A, B, C));
                else if (all_over) convex_hull.push_back(Triangle(A, C, B));
            }
        }
    }
    return convex_hull;
}