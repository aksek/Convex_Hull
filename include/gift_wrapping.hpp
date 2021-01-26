// Kowalski, Convex_Hull

#pragma once
#include <vector>
#include "Triangle.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Vector.hpp"
#include "Edge.hpp"
#include "data_converter.hpp"
#include <list>
#include "comparator.hpp"
#include"Plane.hpp"

class gift_wrapping {

public:
    gift_wrapping() = default;
    ~gift_wrapping() = default;

    std::vector<Triangle> solve(std::vector<Point> &points);
    Triangle find_one_face(std::vector<Point> &points);
    Triangle find_next_face(std::vector<Point> &points, Triangle face, Edge e);
    void add_edge(std::list<Edge> &E, Edge e);
};
