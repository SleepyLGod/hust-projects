#pragma once
#include <string>
#include <fstream>
#include <queue>
#include "myPoint.h"
using namespace std;

class busMap
{
    int mapLong = 0, mapWidth = 0, busStopsNumber = 0, busLinesNumber = 0, organizationsNumber = 0;
	int* eachBusLineNumber = nullptr;
	int** busLines = nullptr;
	myPoint** busStops = nullptr;
    string organizationNames[100];
    pair<int,int> organizationPos[100];
	int* path = nullptr;

public:
    busMap(string busStopsFile, string busLinesFile, string orgnizationsFile);
	void showStopsAndLines();
	int* findDirectPath(int startIndex, int endIndex);
	int* findEveryPath(int startIndex, int endIndex);
    int getBusLinesNumber()
    {
        return busLinesNumber;
    }
    int** getBusLines()
    {
        return busLines;
    }
    int* getEachBusLineNumber()
    {
        return eachBusLineNumber;
    }
    int getBusStopsNumber()
    {
        return busStopsNumber;
    }
    myPoint** getBusStops()
    {
        return busStops;
    }
    int getOrganizationsNumber()
    {
        return organizationsNumber;
    }
    string* getOrganizationNames()
    {
        return organizationNames;
    }
    pair<int,int>* getOrganizationPos()
    {
        return organizationPos;
    }
	~busMap();
};
