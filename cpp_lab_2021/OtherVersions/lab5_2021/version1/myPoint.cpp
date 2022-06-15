#include "myPoint.h"

void myEdge::addNext(myPoint* to, double distance)
{
	next = new myEdge;
	next->to = to;
	next->distance = distance;
}

myEdge*& myEdge::getNext()
{
	return next;
}

myPoint*& myEdge::getTo()
{
	return to;
}

double& myEdge::getDistance()
{
	return distance;
}

void myPoint::addDirectEdge(myPoint* p, double distance)
{
	if (!directEdgeFirst)
	{
		directEdgeFirst = new myEdge;
		directEdgeFirst->getTo() = p;
		directEdgeFirst->getDistance() = distance;
		return;
	}
	myEdge* ep = directEdgeFirst;
	while (ep->getNext())
		ep = ep->getNext();
	ep->addNext(p, distance);
}

void myPoint::addEveryEdge(myPoint* p)
{
	if (!everyEdgeFirst)
	{
		everyEdgeFirst = new myEdge;
		everyEdgeFirst->getTo() = p;
		return;
	}
	myEdge* ep = everyEdgeFirst;
	while (ep->getNext())
		ep = ep->getNext();
	ep->addNext(p);
}

void myPoint::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void myPoint::setIndex(int index)
{
	this->index = index;
}

std::pair<int, int> myPoint::getPosition()
{
	return std::make_pair(x, y);
}

int myPoint::getIndex()
{
	return index;
}

myEdge* myPoint::getDirectEdgeFirst()
{
	return directEdgeFirst;
}

myEdge* myPoint::getEveryEdgeFirst()
{
	return everyEdgeFirst;
}

double calculateDistance(myPoint a, myPoint b)
{
	return sqrt((a.getPosition().first - b.getPosition().first) * (a.getPosition().first - b.getPosition().first)
		+ (a.getPosition().second - b.getPosition().second) * (a.getPosition().second - b.getPosition().second));
}