#ifndef CONFLICT_GRAPH_H
#define CONFLICT_GRAPH_H

#include<vector>
#include<unordered_map>
#include<list>

#include"Point.hpp"
#include"Triangle.hpp"

class Conflict_graph {
public:
    std::unordered_map<int, std::list<Triangle> > conflicts;        // a graph that keeps information about all Triangles that are visible from the Point of a given index
    void init();
};

#endif //CONFLICT_GRAPH_H