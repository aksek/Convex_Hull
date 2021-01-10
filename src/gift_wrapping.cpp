#include "gift_wrapping.hpp"

std::vector<Triangle> gift_wrapping::solve(std::vector<Point> &points) {

    std::vector<Edge> E;
    std::vector<Triangle> F;
    std::vector<Triangle> Q;
    std::vector<Edge> A;
   
    Triangle first_face = find_one_face(points);
    Q.push_back(first_face);
    for(Edge e : first_face.edges(points))
        E.push_back(e);
    
    while(Q.empty() != true) {

        Triangle temp = Q[Q.size() - 1];
        Q.pop_back();
        for(Edge e : temp.edges(points))
            A.push_back(e);
        for(Edge e : E) {

            for(Edge e1 : A) {
                
                if(e == e1) {

                    
                }
            }
        }
    }
}

Triangle gift_wrapping::find_one_face(std::vector<Point> &points) {
    std::vector<Triangle> convex_hull;
    bool all_under;      // the point is under a triangle if the point is on the triangle's inner side
    bool all_over;       // likewise, outer side
    bool point_inside;   // if a point exists inside the triangle, the triangle will be omitted - the gap will be filled with the smaller triangles instead
    Vector AB, AC, normal;
    Plane plane;
    int k;
    for(int A = 0; A < points.size() - 2; A++) {

        for (int B = A + 1; B < points.size() - 1; B++) {
            AB = points[B] - points[A];

            for (int C = B + 1; C < points.size(); C++) {

                AC = points[C] - points[A];
                normal = AB * AC;                    // coordinates of the normal vector == coefficients of the plane
                k = -(normal.X() * points[A].X() + normal.Y() * points[A].Y() + normal.Z() * points[A].Z()); //last coefficient
                plane = Plane(normal.X(), normal.Y(), normal.Z(), k);

                all_under = true, all_over = true;
                point_inside = false;
                for(int i = 0; i < points.size(); i++) {
                    if (i == A || i == B || i == C) continue;
                    if (points[i].inside(&points[A], &points[B], &points[C], plane)) {
                        point_inside = true;
                        continue;
                    }
                    if (normal.Z() < 0) {
                        if (points[i].under(plane)) all_over = false;       // not all points are over the triangle
                        else if (points[i].over(plane)) all_under = false;                                                            // not all points are under the triangle
                    } else if (normal.Z() > 0) {
                        if (points[i].under(plane)) all_under = false;       // not all points are under the triangle
                        else if (points[i].over(plane)) all_over = false;     
                    }  else {
                        if (normal.Y() < 0) {
                            if (points[i].under(plane)) all_over = false;
                            else if (points[i].over(plane)) all_under = false;
                        } else if (normal.Y() > 0) {
                            if (points[i].under(plane)) all_under = false;
                            else if (points[i].over(plane)) all_over = false;
                        } else if (normal.X() < 0) {
                            if (points[i].X() < points[A].X()) all_over = false;
                            else if (points[i].X() > points[A].X()) all_under = false;
                        } else if (normal.X() > 0) {
                            if (points[i].X() < points[A].X()) all_under = false;
                            else if (points[i].X() > points[A].X()) all_over = false;
                        } else {
                            all_under = false;
                            all_over = false;
                        }
                    }                                    
                }
                if (!point_inside) {
                    if (all_under) {
                        Triangle temp(A, B, C);
                        return temp;
                    }
                    else if (all_over) {
                        Triangle temp(A, B, C);
                        return temp;
                    }
                }
            }
        }
    }
    
}

Triangle gift_wrapping::find_next_face(std::vector<Point> &points, Triangle face, Edge e) {


}