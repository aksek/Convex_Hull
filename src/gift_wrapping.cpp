#include "gift_wrapping.hpp"

std::vector<Triangle> gift_wrapping::solve(std::vector<Point> &points) {

    std::list<Edge> E;
    std::vector<Triangle> F;
    std::vector<Triangle> Q;
    data_converter c;
    std::string cmd = "python3 ./src/visualize.py";
   
    Triangle first_face = find_one_face(points);
    Q.push_back(first_face);
    for(Edge e : first_face.edges(points))
        E.push_back(e);
    
    while(Q.empty() != true) {

        Triangle temp_face = Q[Q.size() - 1];
        Q.pop_back();
        std::vector<Edge> A;
        for(Edge e : temp_face.edges(points))
            A.push_back(e);

        std::vector<Edge> A_and_E;

        for(Edge e0 : A) {

            if(std::find(E.begin(), E.end(), e0) != E.end()) {

                A_and_E.push_back(e0);
            }
            
        }

        for(Edge e0 : A_and_E) {

            Triangle new_face = find_next_face(points, temp_face, e0);
            std::vector<Edge> B;
            for(Edge e1 : new_face.edges(points))
                B.push_back(e1);
                    
            for(Edge e1 : B) {

                add_edge(E, e1);
            }

            Q.push_back(new_face);
        }
        F.push_back(temp_face);
        //c.save(points, F);
        //::popen(cmd.c_str(), "r");
    }

    return F;
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
                        Triangle temp_face(A, B, C);
                        return temp_face;
                    }
                    else if (all_over) {
                        Triangle temp_face(A, B, C);
                        return temp_face;
                    }
                }
            }
        }
    }
    
}

Triangle gift_wrapping::find_next_face(std::vector<Point> &points, Triangle face, Edge e) {

    Vector normal0(face.normal(points));
    Vector a0(normal0 * e.getDirection());
    double smallest_angle = 1;
    int first_point = 0;
    int second_point = 0;
    int third_point = 0;
    double mag0;
    double mag1;
    Vector temp0;
    Vector temp1;
    double dot;

    if(points[face.A()] == e.getStart())
        first_point = face.A();
    else if(points[face.B()] == e.getStart())
        first_point = face.B();
    else if(points[face.C()] == e.getStart())
        first_point = face.C();
    
    if(points[face.A()] == e.getStart() + e.getDirection())
        second_point = face.A();
    if(points[face.B()] == e.getStart() + e.getDirection())
        second_point = face.B();
    if(points[face.C()] == e.getStart() + e.getDirection())
        second_point = face.C();

    for(long unsigned i = 0; i < points.size(); ++i) {

        if(i != face.A() && i != face.B() && i!= face.C()) {
            
            Triangle face1(second_point, first_point, i);
            Vector normal1(face1.normal(points));
            Vector a1(e.getDirection() * normal1);
            double angle = a0.dot(a1) / a0.magnitude() / a1.magnitude();
            if(angle < smallest_angle) {

                smallest_angle = angle;
                third_point = i;
                mag0 = a0.magnitude();
                mag1 = a1.magnitude();
                temp0 = a0;
                temp1 = a1;
                dot = a0.dot(a1);
            }
        }
    }

    return Triangle(second_point, first_point, third_point);
}

void gift_wrapping::add_edge(std::list<Edge> &E, Edge e) {

    auto it = std::find(E.begin(), E.end(), e);

    if(it != E.end())
        E.erase(it);
    else 
        E.push_back(e);
}