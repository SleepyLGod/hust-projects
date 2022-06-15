#include "mappoint.h"

MapPoint::MapPoint() {
}

void MapPoint::add_direct_Edge_(MapPoint* p, double distance) {
    if (!direct_edge_first_) {
        direct_edge_first_ = new MapEdge;
        direct_edge_first_->get_to_() = p;
        direct_edge_first_->get_edge_distance_() = distance;
        return;
    }
    MapEdge* ep = direct_edge_first_;
    while (ep->get_next_()) {
        ep = ep->get_next_();
    }
    ep->add_next_(p, distance);
}

void MapPoint::add_every_edge_(MapPoint* p) {
    if (!every_edge_first_) {
        every_edge_first_ = new MapEdge;
        every_edge_first_->get_to_() = p;
        return;
    }
    MapEdge* ep = every_edge_first_;
    while (ep->get_next_()) {
        ep = ep->get_next_();
    }
    ep->add_next_(p);
}

void MapPoint::set_point_pos_(int x, int y) {
    this->point_x_ = x;
    this->point_y_ = y;
}

void MapPoint::set_point_index_(int index) {
    this->point_index_ = index;
}

std::pair<int, int> MapPoint::get_point_pos() {
    return std::make_pair(point_x_, point_y_);
}

int MapPoint::get_point_index_() {
    return point_index_;
}

MapEdge* MapPoint::get_direct_edge_first_() {
    return direct_edge_first_;
}

MapEdge* MapPoint::get_every_edge_first_() {
    return every_edge_first_;
}

double calculateDistance(MapPoint a, MapPoint b) {
    return sqrt((a.get_point_pos().first - b.get_point_pos().first) * (a.get_point_pos().first - b.get_point_pos().first)
        + (a.get_point_pos().second - b.get_point_pos().second) * (a.get_point_pos().second - b.get_point_pos().second));
}
