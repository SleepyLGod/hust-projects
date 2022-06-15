#pragma once
#include <algorithm>
#include <math.h>
class myPoint;

class myEdge
{
	myPoint* to = nullptr;
	myEdge* next = nullptr;
	double distance = 0.0;

public:
	void addNext(myPoint* to, double distance = 1.0);
	myEdge*& getNext();
	myPoint*& getTo();
	double& getDistance();
};

class myPoint
{
	int x = 0, y = 0;
	int index = 0;
	myEdge* directEdgeFirst = nullptr, * everyEdgeFirst = nullptr;

public:	
	myPoint() {}
	myPoint(int x, int y, int index) :x(x), y(y), index(index) {}
	std::pair<int, int> getPosition();
	int getIndex();
	myEdge* getDirectEdgeFirst();
	myEdge* getEveryEdgeFirst();
	void setPosition(int x, int y);
	void setIndex(int index);
	void addDirectEdge(myPoint* p, double distance);
	void addEveryEdge(myPoint* p);
};

double calculateDistance(myPoint a, myPoint b);