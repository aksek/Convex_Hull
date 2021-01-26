// Kowalski, Convex_Hull

#include "gift_wrapping.hpp"
#include "Plane.hpp"

std::vector<Triangle> gift_wrapping::solve(std::vector<Point> &points) {

    std::list<Edge> E;
    std::vector<Triangle> F;
    std::vector<Triangle> Q;
   
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
    }

    return F;
}

Triangle gift_wrapping::find_one_face(std::vector<Point> &points) {

    unsigned first_point = 0;
    unsigned second_point = 0;
    unsigned third_point = 0;

    for(unsigned i = 0; i < points.size(); ++i) {
        
        if(points[first_point].Y() > points[i].Y()) {

            first_point = i;
        }
    }

    Vector v0(1, 0, 0);
    Vector v1(0, 0, 0);
    double angle = 0;
    double smallest_angle = 1;
    double smallest_magnitude = std::numeric_limits<double>::max();
    double magnitude = 0;

    for(unsigned i = 0; i < points.size(); ++i) {
        
        v1 = points[i] - points[first_point];
        magnitude = v1.magnitude_x_y();
        angle = v0.dot_x_y(v1) / v0.magnitude_x_y() / magnitude;
        
        if(comparator::cmpfi(angle, smallest_angle)) {

            
            if(magnitude < smallest_magnitude) {

                smallest_magnitude = magnitude;
                smallest_angle = angle;
                second_point = i;
            }
         } else if(angle < smallest_angle) {

            smallest_magnitude = magnitude;
            smallest_angle = angle;
            second_point = i;
        }
    }

    bool is_all_on_inner_side = true;

    for(unsigned j = 0; j < points.size(); ++j) {
    
        is_all_on_inner_side = true;
        
        for(unsigned i = 0; i < points.size(); ++i) {

            if( i != second_point && i != first_point && j != first_point && j != second_point && i != j) {

                if(!points[i].on_inner_side(points[second_point], points[first_point], points[j])) {
                
                    is_all_on_inner_side = false;
                }
            }
        }

        if(is_all_on_inner_side && j != first_point && j != second_point) {

            third_point = j;
            
        }
    }

    return Triangle(second_point, first_point, third_point);
}

Triangle gift_wrapping::find_next_face(std::vector<Point> &points, Triangle face, Edge e) {

    Vector normal0(face.normal(points));
    Vector a0(normal0 * e.getDirection());
    double smallest_angle = 1;

    double smallest_i_angle = 1;
    unsigned first_point = 0;
    unsigned second_point = 0;
    unsigned third_point = 0;

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


    for(unsigned i = 0; i < points.size(); ++i) {

        if(i != face.A() && i != face.B() && i!= face.C()) {
            
            Triangle face1(second_point, first_point, i);
            Vector normal1(face1.normal(points));
            Vector a1(e.getDirection() * normal1);
            double angle = a0.dot(a1) / a0.magnitude() / a1.magnitude();

            double i_angle = (points[first_point] - points[i]).dot(points[second_point] - points[i]) / (points[first_point] - points[i]).magnitude() / (points[second_point] - points[i]).magnitude();
            
            if(comparator::cmpfi(angle, smallest_angle)) {

                if(i_angle < smallest_i_angle) {
                    
                    third_point = i;
                    smallest_angle = angle;
                    smallest_i_angle = i_angle;
                }

            } else if(angle < smallest_angle) {

                smallest_angle = angle;
                third_point = i;
                smallest_i_angle = i_angle;
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
