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
        c.save(points, F);
        //::popen(cmd.c_str(), "r");
    }

    return F;
}

Triangle gift_wrapping::find_one_face(std::vector<Point> &points) {

    unsigned first_point = 0;
    unsigned second_point = 0;
    unsigned third_point = 0;

    for(unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[first_point].X() < points[i].X()) {

            first_point = i;
        }
        
        if(points[first_point].Y() > points[i].Y()) {

            first_point = i;
        }
    }

    for(unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[second_point].X() < points[i].X() && i != first_point) {

            second_point = i;
        }
        
        if(points[second_point].Y() > points[i].Y() && i != first_point) {

            second_point = i;
        }
    }

    for(unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[third_point].X() < points[i].X() && i != first_point && i != second_point) {

            third_point = i;
        }
        
        if(points[third_point].Y() > points[i].Y() && i != first_point && i != second_point) {

            third_point = i;
        }
    }

    return Triangle(second_point, first_point, third_point);
}

Triangle gift_wrapping::find_next_face(std::vector<Point> &points, Triangle face, Edge e) {

    Vector normal0(face.normal(points));
    Vector a0(normal0 * e.getDirection());
    double smallest_angle = 1;
    int first_point = 0;
    int second_point = 0;
    int third_point = 0;

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
            if(angle < smallest_angle) {

                smallest_angle = angle;
                third_point = i;
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