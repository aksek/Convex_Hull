#include "gift_wrapping.hpp"

std::vector<Triangle> gift_wrapping::solve(std::vector<Point> &points) {

    std::list<Edge> E;
    std::vector<Triangle> F;
    std::list<Triangle> Q;
    data_converter c;
    std::unordered_set<int> is_not_used;
    std::unordered_set<int> is_on_boundary;
    std::string cmd = "python3 ./src/visualize.py";

    for(unsigned int i = 0; i < points.size(); ++i) {

        is_not_used.insert(i);
    }
   
    Triangle first_face = find_one_face(points);
    Q.push_back(first_face);
    for(Edge e : first_face.edges(points))
        E.push_back(e);
    
    while(Q.empty() != true) {

        is_on_boundary = get_points_form_edges(E, points);

        Triangle temp_face = Q.front();
        Q.pop_front();
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

            Triangle new_face = find_next_face(points, temp_face, e0, is_not_used, is_on_boundary);
            std::vector<Edge> B;
            for(Edge e1 : new_face.edges(points))
                B.push_back(e1);
                    
            for(Edge e1 : B) {

                add_edge(E, e1);
            }

            is_not_used.erase(new_face.A());
            is_not_used.erase(new_face.B());
            is_not_used.erase(new_face.C());
            Q.push_back(new_face);
        }
        F.push_back(temp_face);
        c.save(points, Q);
        //::popen(cmd.c_str(), "r");
    }

    return F;
}

Triangle gift_wrapping::find_one_face(std::vector<Point> &points) {

    int first_point = 0;
    int second_point = 0;
    int third_point = 0;

    for(long unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[first_point].X() < points[i].X()) {

            first_point = i;
        }
        
        if(points[first_point].Y() > points[i].Y()) {

            first_point = i;
        }
    }

    for(long unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[second_point].X() < points[i].X() && i != first_point) {

            second_point = i;
        }
        
        if(points[second_point].Y() > points[i].Y() && i != first_point) {

            second_point = i;
        }
    }

    for(long unsigned i = 0; i < points.size(); ++i) {

        if(comparator::cmpfi(points[first_point].Y(), points[i].Y()) && points[third_point].X() < points[i].X() && i != first_point && i != second_point) {

            third_point = i;
        }
        
        if(points[third_point].Y() > points[i].Y() && i != first_point && i != second_point) {

            third_point = i;
        }
    }

    return Triangle(second_point, first_point, third_point);
}

Triangle gift_wrapping::find_next_face(std::vector<Point> &points, Triangle face, Edge e, std::unordered_set<int> is_not_used, std::unordered_set<int> is_on_boundary) {

    Vector normal0(face.normal(points));
    Vector a0(normal0 * e.getDirection());
    double smallest_angle = 1;
    //double smallest_distance = std::numeric_limits<double>::max();
    int first_point = 0;
    int second_point = 0;
    int third_point = 0;
    double mag0;
    double mag1;
    Vector temp0;
    Vector temp1;
    double dot;
    //Point middle;
    double smallest_i_angle = 1;
    //double smallest_surface = std::numeric_limits<double>::max();

    if(points[face.A()] == e.getStart())
        first_point = face.A();
    else if(points[face.B()] == e.getStart())
        first_point = face.B();
    else if(points[face.C()] == e.getStart())
        first_point = face.C();
    
    if(points[face.A()] == e.getEnd())
        second_point = face.A();
    if(points[face.B()] == e.getEnd())
        second_point = face.B();
    if(points[face.C()] == e.getEnd())
        second_point = face.C();

    //middle = Point((points[first_point].X() + points[second_point].X()) / 2, (points[first_point].Y() + points[second_point].Y()) / 2, (points[first_point].Z() + points[second_point].Z()) / 2);

    for(long unsigned i = 0; i < points.size(); ++i) {

        if(i != face.A() && i != face.B() && i != face.C() && (is_not_used.find(i) != is_not_used.end() || is_on_boundary.find(i) != is_on_boundary.end() )) {
            
            Triangle face1(second_point, first_point, i);
            Vector normal1(face1.normal(points));
            Vector a1(e.getDirection() * normal1);
            double angle = a0.dot(a1) / a0.magnitude() / a1.magnitude();
            double i_angle = (points[first_point] - points[i]).dot(points[second_point] - points[i]) / (points[first_point] - points[i]).magnitude() / (points[second_point] - points[i]).magnitude();
            //double distance = (middle - points[i]).magnitude();
            //double surface = face1.surface(points);

            if(points[i].X() == 57 && points[i].Y() == 0 && points[i].Z() == 10) {
                
                i = i;
            }

            if(points[i].X() == 62 && points[i].Y() == 0 && points[i].Z() == 15) {
                
                i = i;
            }
            
            if(comparator::cmpfi(angle, smallest_angle)) {

                if(/*distance < smallest_distance*/ i_angle < smallest_i_angle /*surface < smallest_surface*/) {
                    third_point = i;
                    smallest_angle = angle;
                    smallest_i_angle = i_angle;
                    //smallest_distance = distance;
                    //smallest_surface = surface;
                }

            } else if(angle < smallest_angle) {

                smallest_angle = angle;
                third_point = i;
                mag0 = a0.magnitude();
                mag1 = a1.magnitude();
                temp0 = a0;
                temp1 = a1;
                dot = a0.dot(a1);
                smallest_i_angle = i_angle;
                //smallest_distance = distance;
                //smallest_surface = surface;
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

std::unordered_set<int> gift_wrapping::get_points_form_edges(std::list<Edge> &E, std::vector<Point> &points) {

    std::unordered_set<int> out;

    for(Edge e : E) {

        for(unsigned int i = 0; i < points.size(); ++i) {

            if(points[i] == e.getStart() || points[i] == e.getEnd()){

                out.insert(i);
            }
        }
    }

    return out;
}