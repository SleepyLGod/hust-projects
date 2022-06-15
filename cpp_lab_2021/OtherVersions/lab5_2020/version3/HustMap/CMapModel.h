#pragma once
#include <afx.h>
#include <vector>
class CMapModel :
    public CObject
{
private:
    CString m_sMapFilePath = _T("");
    CString m_sLocationFilePath = _T("");
    CString m_sEdgeFilePath = _T("");
    CString m_sOrgFilePath = _T("");
    CString m_sLocOrgFilePath = _T("");
    std::vector<CPoint>Location;
    double Edge[100][100];
public:
    DECLARE_SERIAL(CMapModel)
    CMapModel();
    virtual ~CMapModel();
public:
    virtual void Serialize(CArchive& ar);
public:
    std::vector<CString>Organization;
    std::vector<std::vector<int>>Locorg;

    int GetLocationNum() { return Location.size(); }
    CString GetMapFilePath();
    CString GetLoacationFilePath();
    CString GetEdgeFilePath();
    CString GetOrgFilePath();
    CString GetLocOrgFilePath();
    CPoint GetLocation(int i);
    double GetEdge(int x, int y);

    void SetMapFilePath(CString path);
    void SetLocationFilePath(CString path);
    void SetEdgeFilePath(CString path);
    void SetOrgFilePath(CString path);
    void SetLocOrgFilePath(CString path);
    void PushLocation(CPoint point);
    void PushOrganization(CString name);
    void PushEdge(int a, int b,double edge);

    CPoint FindPositionByOrg(CString name);
    std::vector<CPoint> FindShortestPath(CPoint start, CPoint end);
    std::vector<CString>GetOrganizations(CPoint point);
};


