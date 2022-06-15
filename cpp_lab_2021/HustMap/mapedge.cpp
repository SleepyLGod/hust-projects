#include "mapedge.h"

MapEdge::MapEdge() {
}

void MapEdge::add_next_(MapPoint *to, double distance) {
    next_ = new MapEdge;
    next_->to_ = to;
    next_->edge_distance_ = distance;
}

MapEdge*& MapEdge::get_next_() {
    return next_;
}

MapPoint*& MapEdge::get_to_() {
    return to_;
}

double& MapEdge::get_edge_distance_() {
    return edge_distance_;
}
