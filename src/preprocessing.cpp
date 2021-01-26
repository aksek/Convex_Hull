// Kosek, Convex_Hull

#include<unordered_set>
#include<vector>

#include<boost/functional/hash.hpp>

#include"preprocessing.hpp"

using namespace std;

struct point_hash {
    size_t operator()(const Point &P) const {
        boost::hash<std::vector<int> > vector_hash;
        vector<int> coors;
        coors.push_back(P.X());
        coors.push_back(P.Y());
        coors.push_back(P.Z());
        return vector_hash(coors);
    }
};

void Preprocessing::voxelize(vector<Point> &points, int d) {
    unordered_set<Point, point_hash> voxelized_points;
    for (unsigned i = 0; i < points.size(); i++) {
        double voxel_x = points[i].X() - fmod(points[i].X(), d);
        double voxel_y = points[i].Y() - fmod(points[i].Y(), d);
        double voxel_z = points[i].Z() - fmod(points[i].Z(), d);
        voxelized_points.emplace(Point(voxel_x, voxel_y, voxel_z));
    }
    points.assign(voxelized_points.begin(), voxelized_points.end());
}
