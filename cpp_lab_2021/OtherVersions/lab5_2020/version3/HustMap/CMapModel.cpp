#include <vector>
#include "pch.h"
#include "CMapModel.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


IMPLEMENT_SERIAL(CMapModel, CObject, VERSIONABLE_SCHEMA | 2)

CMapModel::CMapModel() { 
    for (int i = 0; i < 100; i++)   
        for (int j = 0; j < 100; j++)
        {
            if (i == j)    Edge[i][j] = 0;
            else Edge[i][j] = 1000;
        }
}
CMapModel::~CMapModel() {}

void CMapModel::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << this->m_sMapFilePath << this->m_sLocationFilePath << this->m_sEdgeFilePath << this->m_sOrgFilePath;

	}
	else {
		ar >> this->m_sMapFilePath >> this->m_sLocationFilePath >> this->m_sEdgeFilePath >> this->m_sOrgFilePath;
	}

}

CString CMapModel::GetMapFilePath() { return this->m_sMapFilePath; }
CString CMapModel::GetLoacationFilePath() { return this->m_sLocationFilePath; }
CString CMapModel::GetEdgeFilePath() { return this->m_sEdgeFilePath; }
CString CMapModel::GetOrgFilePath() { return this->m_sOrgFilePath; }
CString CMapModel::GetLocOrgFilePath() { return this->m_sLocOrgFilePath; }
void CMapModel::SetMapFilePath(CString path) { this->m_sMapFilePath = path; }
void CMapModel::SetLocationFilePath(CString path) {this->m_sLocationFilePath = path;}
void CMapModel::SetEdgeFilePath(CString path) { this->m_sEdgeFilePath = path; }
void CMapModel::SetOrgFilePath(CString path) { this->m_sOrgFilePath = path; }
void CMapModel::SetLocOrgFilePath(CString path) { this->m_sLocOrgFilePath = path; }
void CMapModel::PushLocation(CPoint point) {this->Location.push_back(point);}
CPoint CMapModel::GetLocation(int i) { return	this->Location[i]; }
void CMapModel::PushOrganization(CString name) { this->Organization.push_back(name); }
void CMapModel::PushEdge(int x, int y,double edge){this->Edge[x][y] = edge;this->Edge[y][x] = edge;}
double CMapModel::GetEdge(int x, int y) { return this->Edge[x][y]; }


CPoint CMapModel::FindPositionByOrg(CString name)
{
    int i = 0;
    int j = 0;
	for (i = 0; i < this->Organization.size(); i++)
	{
		if (this->Organization[i] == name)	break;
	}
    if (i == Organization.size())  return CPoint(0, 0);
	for (j = 0; j < this->Location.size(); j++)
	{
		if (Locorg[j][0] == i || Locorg[j][1] == i)	break;
	}
	return this->Location[j];
}

std::vector<CPoint> CMapModel::FindShortestPath(CPoint start, CPoint end)
{
    vector<CPoint>ShortestWay;
    if (start == CPoint(0, 0) || end == CPoint(0, 0))    return ShortestWay;
    const int maxnum = 100;
    const double maxint = 1000;
    int u=0, v=0;
    for (int i=0; i < this->Location.size(); i++) {
        if (Location[i] == start)  v = i;
        if (Location[i] == end)    u = i;
    }

    // 各数组都从下标1开始
    double dist[maxnum];     // 表示当前点到源点的最短路径长度
    int prev[maxnum] = {0};     // 记录当前点的前一个结点
    int n = Location.size();            // 图的结点数和路径数

    bool s[maxnum];    // 判断是否已存入该点到S集合中
    for (int i = 0; i < n; ++i){
        dist[i] = Edge[v][i];
        s[i] = 0;     // 初始都未用过该点
        if (dist[i]>500)
            prev[i] = 0;
        else
            prev[i] = v;
    }
    dist[v] = 0;
    s[v] = 1;

    // 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
    // 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
         // 注意是从第二个节点开始，第一个为源点
    for (int i = 1; i < n; ++i)
    {
        double tmp = maxint;
        int u = v;
        // 找出当前未使用的点j的dist[j]最小值
        for (int j = 0; j < n; ++j)
            if ((!s[j]) && dist[j] < tmp)
            {
                u = j;              // u保存当前邻接点中距离最小的点的号码
                tmp = dist[j];
            }
        s[u] = 1;    // 表示u点已存入S集合中

        // 更新dist
        for (int j = 0; j < n; ++j)
            if ((!s[j]) && Edge[u][j] < maxint)
            {
                double newdist = dist[u] + Edge[u][j];
                if (newdist < dist[j])
                {
                    dist[j] = newdist;
                    prev[j] = u;
                }
            }
    }
    int que[maxnum];
    int tot = 1;
    que[tot] = u;
    tot++;
    int tmp = prev[u];
    while (tmp != v)
    {
        que[tot] = tmp;
        tot++;
        tmp = prev[tmp];
    }
    que[tot] = v;
    for (int i = tot; i >= 1; --i)
        ShortestWay.push_back(Location[que[i]]);
    return ShortestWay;
}

std::vector<CString> CMapModel::GetOrganizations(CPoint point) {
    vector<CString> orgs;
    for (int i = 0; i < Location.size(); i++)
    {
        if (abs(point.x-Location[i].x)<4&&abs(point.y-Location[i].y)<4&&this->GetOrgFilePath()!=_T(""))
        {
            CString pos;
            pos.Format(_T("%d,%d"), Location[i].x, Location[i].y);
            orgs.push_back(pos);
            orgs.push_back(Organization[Locorg[i][0]]);
            if (Locorg[i][1] != -1)    orgs.push_back(Organization[Locorg[i][1]]);
            break;
        }
    }
    return orgs;
}