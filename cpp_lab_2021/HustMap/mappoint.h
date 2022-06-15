#ifndef MAPPOINT_H
#define MAPPOINT_H
#include <iostream>
#include <algorithm>
#include <math.h>
#include "mapedge.h"
class MapEdge;

class MapPoint {

private:
    int point_x_ = 0;
    int point_y_ = 0;
    int point_index_ = 0;
    MapEdge* direct_edge_first_ = nullptr;
    MapEdge* every_edge_first_ = nullptr;

public:
    MapPoint();

    MapPoint(int point_x_, int point_y_, int point_index_) :point_x_(point_x_), point_y_(point_y_), point_index_(point_index_) {};

    // getters:
    int get_point_index_();

    MapEdge* get_direct_edge_first_();

    MapEdge* get_every_edge_first_();

    std::pair<int, int> get_point_pos();

    // setters:
    void set_point_pos_(int x, int y);

    void set_point_index_(int index);

    void add_direct_Edge_(MapPoint* p, double distance);

    void add_every_edge_(MapPoint* p);

};

double calculateDistance(MapPoint a, MapPoint b);

#endif // MAPPOINT_H
