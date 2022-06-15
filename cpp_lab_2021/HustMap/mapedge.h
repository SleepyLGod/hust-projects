#ifndef MAPEDGE_H
#define MAPEDGE_H
#include "mappoint.h"
class MapPoint;

class MapEdge {

    MapPoint* to_ = nullptr;
    MapEdge* next_ = nullptr;
    double edge_distance_ = 0.0;

public:
    MapEdge();

    // setters:
    void add_next_(MapPoint* to, double distance = 1.0);

    // getters:
    MapEdge*& get_next_();

    MapPoint*& get_to_();

    double& get_edge_distance_();

};

#endif // MAPEDGE_H
