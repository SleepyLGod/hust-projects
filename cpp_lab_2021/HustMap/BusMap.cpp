#include "BusMap.h"
#include <iostream>
#include <fstream>
#include <set>
#include <QApplication>
#include <QDebug>
// QDebug config:
#define cout qDebug()<<"["<<__FILE__":"<<__LINE__<<"]"

// initializer:
BusMap::BusMap(string bus_stops_File, string bus_lines_File, string orgnizations_file) {
    ifstream fp(bus_stops_File);
    // bus stops points:
    if (!fp.is_open()) {
        throw("File open error!");
        //cout << "where is the stop file?" << endl;
    }
    fp >> bus_stop_cnt_;
    bus_stops_ = new MapPoint * [bus_stop_cnt_ + 1];
    path_ = new int[bus_stop_cnt_ + 1];
    for (int i = 1, a, b; i <= bus_stop_cnt_; ++i) {
        fp >> a >> b;
        bus_stops_[i] = new MapPoint(a, b, i);
    }
    fp.close();

    // bus lines:
    fp.open(bus_lines_File);
    if (!fp.is_open()) {
        throw("File open error!");
       // cout << "where is the line file?" << endl;
    }
    fp >> bus_line_cnt_;
    bus_lines_ = new int*[bus_line_cnt_ + 1];
    each_bus_line_num_ = new int[bus_line_cnt_ + 1];
    for (int i = 1; i <= bus_line_cnt_; ++i) {
        fp >> each_bus_line_num_[i];
        bus_lines_[i] = new int[each_bus_line_num_[i] + 1];
    }
    for (int i = 1; i <= bus_line_cnt_; ++i) {
        for (int j = 1; j <= each_bus_line_num_[i]; ++j) {
            fp >> bus_lines_[i][j];
        }
    }

    // edges of points on bus lines:
    for (int i = 1; i <= bus_line_cnt_; ++i) {
        for (int j = 1; j <= each_bus_line_num_[i]; ++j) {
            for (int k = j + 1; k <= each_bus_line_num_[i]; ++k) {
                bus_stops_[bus_lines_[i][j]]->add_every_edge_(bus_stops_[bus_lines_[i][k]]);
                bus_stops_[bus_lines_[i][k]]->add_every_edge_(bus_stops_[bus_lines_[i][j]]);
            }
        }
    }
    for (int i = 1; i <= bus_line_cnt_; ++i) {
        for (int j = 1; j <= each_bus_line_num_[i] - 1; ++j) {
            double dis = calculateDistance(*bus_stops_[bus_lines_[i][j]], *bus_stops_[bus_lines_[i][j + 1]]);
            bus_stops_[bus_lines_[i][j]]->add_direct_Edge_(bus_stops_[bus_lines_[i][j + 1]], dis);
            bus_stops_[bus_lines_[i][j + 1]]->add_direct_Edge_(bus_stops_[bus_lines_[i][j]], dis);
        }
    }
    path_[0] = 0;
    fp.close();

    // organiztions:
    fp.open(orgnizations_file);
    if(!fp.is_open()) {
        throw("File open error!");
       // cout << "where is the organization file?" <<endl;
    }
    string temp;
    while(fp >> temp) {
        organization_names_[++organizations_cnt_] = temp;
        fp >> organization_pos_[organizations_cnt_].first;
        fp.get();
        fp >> organization_pos_[organizations_cnt_].second;
    }
    fp.close();

}

void BusMap::showStopsAndLines() {
    cout << "stops : " << bus_stop_cnt_ << endl;
    for (int i = 1; i <= bus_stop_cnt_; i++) {
        cout << bus_stops_[i]->get_point_pos().first << ' ' << bus_stops_[i]->get_point_pos().second << endl;
    }
    cout << "lines : " << bus_line_cnt_ << endl;
    for (int i = 1; i <= bus_line_cnt_; i++) {
        cout << each_bus_line_num_[i] << " : ";
        for (int j = 1; j <= each_bus_line_num_[i]; j++) {
            cout << bus_lines_[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "map : " << endl;
    for (int i = 1; i <= bus_stop_cnt_; i++) {
        cout << bus_stops_[i]->get_point_index_() << " directEdge : ";
        MapEdge* p = bus_stops_[i]->get_direct_edge_first_();
        while (p) {
            cout << p->get_to_()->get_point_index_() << " : " << p->get_edge_distance_() << " ; ";
            p = p->get_next_();
        }
        cout << endl;
        cout << bus_stops_[i]->get_point_index_() << " everyEdge : ";
        p = bus_stops_[i]->get_every_edge_first_();
        while (p) {
            cout << p->get_to_()->get_point_index_() << ' ';
            p = p->get_next_();
        }
        cout << endl;
    }
}

// utils:
int* BusMap::findDirectPath(int start_index, int end_index) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myQueue;
    int* dis = new int[bus_stop_cnt_ + 1];
    for (int i = 1; i <= bus_stop_cnt_; i++) {
        dis[i] = 0x3f3f3f3f;
    }
    // first : distance
    // second : index
    dis[start_index] = 0;
    myQueue.push(make_pair(0, start_index));
    path_[start_index] = 0;
    while (!myQueue.empty()) {
        int dis_now = myQueue.top().first;
        int ind_now = myQueue.top().second;
        myQueue.pop();
        if (dis[ind_now] != dis_now) {
            continue;
        }
        for (MapEdge* ep = bus_stops_[ind_now]->get_direct_edge_first_(); ep; ep = ep->get_next_()) {
            int idx = ep->get_to_()->get_point_index_();
            if (dis[idx] > dis[ind_now] + ep->get_edge_distance_()) {
                dis[idx] = dis[ind_now] + ep->get_edge_distance_();
                myQueue.push(make_pair(dis[idx], idx));
                path_[idx] = ind_now;
            }
        }
    }
    delete[] dis;
    return path_;
}

int* BusMap::findEveryPath(int start_index, int end_index)
{
    int* pathCopy = new int[bus_stop_cnt_ + 1];
    int* dis = new int[bus_stop_cnt_ + 1];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myQueue;
    for (int i = 1; i <= bus_stop_cnt_; ++i) {
        dis[i] = 0x3f3f3f3f;
    }
    //first integer is distance, second is index
    dis[start_index] = 0;
    myQueue.push(make_pair(0, start_index));
    pathCopy[start_index] = 0;
    while (!myQueue.empty()) {
        int dis_now = myQueue.top().first;
        int ind_now = myQueue.top().second;
        myQueue.pop();
        if (dis[ind_now] != dis_now) {
            continue;
        }
        for (MapEdge* ep = bus_stops_[ind_now]->get_every_edge_first_(); ep; ep = ep->get_next_()) {
            int idx = ep->get_to_()->get_point_index_();
            if (dis[idx] > dis[ind_now] + ep->get_edge_distance_()) {
                dis[idx] = dis[ind_now] + ep->get_edge_distance_();
                myQueue.push(make_pair(dis[idx], idx));
                pathCopy[idx] = ind_now;
            }
        }
    }
    delete[] dis;

    set<int> *bus_lines_set = new set<int>[bus_line_cnt_+1];
    for (int i = 1; i <= bus_line_cnt_; ++i) {
        for (int j = 1; j <= each_bus_line_num_[i]; ++j) {
            bus_lines_set[i].insert(bus_lines_[i][j]);
        }
    }
    int pointIndex = end_index;
    while (pathCopy[pointIndex]) {
        for (int i = 1; i <= bus_line_cnt_; ++i) {
            if (bus_lines_set[i].count(pathCopy[pointIndex]) && bus_lines_set[i].count(pointIndex)) {
                int start = 1;
                int end = 1;
                while (bus_lines_[i][start] != pathCopy[pointIndex]) {
                    ++start;
                }
                while (bus_lines_[i][end] != pointIndex) {
                    ++end;
                }
                if (start < end) {
                    for (int j = end; j > start; --j) {
                        path_[bus_lines_[i][j]] = bus_lines_[i][j - 1];
                    }
                } else {
                    for (int j = end; j < start; ++j) {
                        path_[bus_lines_[i][j]] = bus_lines_[i][j + 1];
                    }
                }
            }
        }
        pointIndex = pathCopy[pointIndex];
    }
    path_[start_index] = 0;
    delete[] pathCopy;
    return path_;
}

BusMap::~BusMap() {
    for (int i = 1; i <= each_bus_line_num_[i]; ++i) {
        delete[] bus_lines_[i];
    }
    delete[] each_bus_line_num_;
    delete[] bus_lines_;
    delete[] bus_stops_;
    delete[] path_;
}
