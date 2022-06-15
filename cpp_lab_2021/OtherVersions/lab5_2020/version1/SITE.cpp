#include <string.h>
#include <math.h>
#include "SITE.h"
#include<cstdio>
#include<iostream>

extern const char organization[33][100];
extern const int location[25][2];
extern int eage[64][2];
extern const int locorg[25][2];
const int maxSize = 1000;
const int INF = 100000000;
int n, m, s;
double G[maxSize][maxSize];
double d[maxSize];
bool vis[maxSize] = { false };
//pre[v]数组表示从起点到顶点v的最短路径上v的前一个顶点
int pre[maxSize];
using namespace std;

void Dijstra(int s) {
    fill(d, d + maxSize, INF);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        double min = INF;
        for (int j = 0; j < n; j++) {
            if (vis[j] == false && d[j] < min) {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        vis[u] = true;
        for (int v = 0; v < n; v++) {
            if (vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v]) {
                d[v] = d[u] + G[u][v];
                pre[v] = u;
            }
        }
    }
}

//输出源点到顶点v的最短路径
void shortPath(int s, int v) {
    if (s == v) {
        //相等的时候说明已经找到了第一个节点可以层层返回进行输出
        cout << s << " ";
        return;
    }
    shortPath(s, pre[v]);
    cout << v << " ";
}


SITE::SITE(){
    for(int i=0;i<32;i++){
        eage[i+32][0] = eage[i][1];
        eage[i+32][1] = eage[i][0];
    }

    for(int i=0;i<site_num;i++){
        info[i].location[0] = location[i][0];
        info[i].location[1] = location[i][1];
        if(locorg[i][1]!=-1){
            info[i].organization_num = 2;
            strcpy(info[i].organization[0],organization[locorg[i][0]]);
            strcpy(info[i].organization[1],organization[locorg[i][1]]);
            info[i].organization_no[0] = locorg[i][0];
            info[i].organization_no[1] = locorg[i][1];
        }else{
            info[i].organization_num = 1;
            strcpy(info[i].organization[0],organization[locorg[i][0]]);
            info[i].organization_no[0] = locorg[i][0];
        }
    }
    for(int i=0;i<site_num;i++){
        for(int j=0;j<64;j++){
            if(i==eage[j][0]){
                info[i].accessible_site[info[i].accessible_site_num++] = eage[j][1];
                info[i].accessible_site_distance[eage[j][1]] = sqrt(pow((info[i].location[0]-info[eage[j][1]].location[0]),2)+pow((info[i].location[1]-info[eage[j][1]].location[1]),2));
            }
        }
    }

    for (int i = 0; i < n; ++i) pre[i] = i;
    fill(G[0], G[0] + maxSize * maxSize, INF);
    n = 25;
    m = 32;
    for (int i = 0; i < 25; i++) {
            for (int j = 0; j < info[i].accessible_site_num; j++) {
                G[i][info[i].accessible_site[j]] = info[i].accessible_site_distance[j];
            }
        }
    s = 0;
    Dijstra(s);
    for (int i = 0; i < n; i++) {
        cout << d[i] << " ";
    }
    //	cout << endl;
        //使用递归的方法来输出其中的最短路径
        //输入v顶点
//    cin >> v;
    //	cout << s << " " << v << endl;
//    shortPath(s, v);
};



