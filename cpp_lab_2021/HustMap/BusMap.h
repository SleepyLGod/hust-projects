#ifndef BusMap_H
#define BusMap_H
#include <string>
#include <fstream>
#include <queue>
#include "mappoint.h"

using namespace std;

class BusMap {

private:
    int map_len_ = 0;
    int map_wid_ = 0;
    int bus_stop_cnt_ = 0;                  // 公交车站点数量
    int bus_line_cnt_ = 0;                  // 公交车线路数量
    int organizations_cnt_ = 0;             // 机构或单位数量
    string organization_names_[100];        // 机构或单位名称
    pair<int,int> organization_pos_[100];   // 组织名
    int* each_bus_line_num_ = nullptr;
    int** bus_lines_ = nullptr;
    MapPoint** bus_stops_ = nullptr;
    int* path_ = nullptr;

public:
    // initialize:
    BusMap(string bus_stops_File, string bus_lines_File, string orgnizations_file);

    // getters:
    int get_bus_line_cnt_() {
        return bus_line_cnt_;
    }

    int** get_bus_lines_() {
        return bus_lines_;
    }

    int* get_each_bus_line_num_() {
        return each_bus_line_num_;
    }

    int get_bus_stop_cnt_() {
        return bus_stop_cnt_;
    }

    MapPoint** get_bus_stops_() {
        return bus_stops_;
    }

    int get_organizations_cnt_() {
        return organizations_cnt_;
    }

    string* get_organization_names_() {
        return organization_names_;
    }

    pair<int,int>* get_organization_pos_() {
        return organization_pos_;
    }

    void showStopsAndLines();

    int* findDirectPath(int start_index, int end_index);

    int* findEveryPath(int start_index, int end_index);

    ~BusMap();
};

#endif // BusMap_H
