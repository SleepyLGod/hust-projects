#include "busMap.h"
#include <iostream>
#include <set>
using namespace std;

busMap::busMap(string busStopsFile, string busLinesFile, string orgnizationsFile)
{
	//initialize bus stops points
    ifstream fp(busStopsFile);
	if (!fp.is_open())
		throw("File open error!");
	fp >> busStopsNumber;
	busStops = new myPoint * [busStopsNumber + 1];
	path = new int[busStopsNumber + 1];
	for (int i = 1, a, b; i <= busStopsNumber; i++)
	{
		fp >> a >> b;
		busStops[i] = new myPoint(a, b, i);
	}
    fp.close();

	//initialize bus lines
	fp.open(busLinesFile);
	if (!fp.is_open())
		throw("File open error!");
	fp >> busLinesNumber;
	busLines = new int*[busLinesNumber + 1];
	eachBusLineNumber = new int[busLinesNumber + 1];
	for (int i = 1; i <= busLinesNumber; i++)
	{
		fp >> eachBusLineNumber[i];
		busLines[i] = new int[eachBusLineNumber[i] + 1];
	}
	for (int i = 1; i <= busLinesNumber; i++)
		for (int j = 1; j <= eachBusLineNumber[i]; j++)
			fp >> busLines[i][j];

	//initailize edges of points on bus lines
	for (int i = 1; i <= busLinesNumber; i++)
		for (int j = 1; j <= eachBusLineNumber[i]; j++)
			for (int k = j + 1; k <= eachBusLineNumber[i]; k++)
			{
				busStops[busLines[i][j]]->addEveryEdge(busStops[busLines[i][k]]);
				busStops[busLines[i][k]]->addEveryEdge(busStops[busLines[i][j]]);
			}
	for (int i = 1; i <= busLinesNumber; i++)
		for (int j = 1; j <= eachBusLineNumber[i] - 1; j++)
		{
			double __dis = calculateDistance(*busStops[busLines[i][j]], *busStops[busLines[i][j + 1]]);
			busStops[busLines[i][j]]->addDirectEdge(busStops[busLines[i][j + 1]], __dis);
			busStops[busLines[i][j + 1]]->addDirectEdge(busStops[busLines[i][j]], __dis);
		}
    path[0]=0;
    fp.close();

    //initialize organiztions
    fp.open(orgnizationsFile);
    if(!fp.is_open())
        throw("File open error!");
    string __temp;
    while(fp>>__temp)
    {
        organizationsNumber++;
        organizationNames[organizationsNumber]=__temp;
        fp>>organizationPos[organizationsNumber].first;
        fp.get();
        fp>>organizationPos[organizationsNumber].second;
    }
    fp.close();

}

busMap::~busMap()
{
	for (int i = 1; i <= eachBusLineNumber[i]; i++)
		delete[] busLines[i];
	delete[] eachBusLineNumber;
	delete[] busLines;
	delete[] busStops;
    delete[] path;
}

void busMap::showStopsAndLines()
{
	cout << "stops : " << busStopsNumber << endl;
	for (int i = 1; i <= busStopsNumber; i++)
		cout << busStops[i]->getPosition().first << ' ' << busStops[i]->getPosition().second << endl;
	cout << "lines : " << busLinesNumber << endl;
	for (int i = 1; i <= busLinesNumber; i++)
	{
		cout << eachBusLineNumber[i] << " : ";
		for (int j = 1; j <= eachBusLineNumber[i]; j++)
			cout << busLines[i][j] << ' ';
		cout << endl;
	}
	cout << "map : " << endl;
	for (int i = 1; i <= busStopsNumber; i++)
	{
		cout << busStops[i]->getIndex() << " directEdge : ";
		myEdge* p = busStops[i]->getDirectEdgeFirst();
		while (p)
		{
			cout << p->getTo()->getIndex() << " : " << p->getDistance() << " ; ";
			p = p->getNext();
		}
		cout << endl;

		cout << busStops[i]->getIndex() << " everyEdge : ";
		p = busStops[i]->getEveryEdgeFirst();
		while (p)
		{
			cout << p->getTo()->getIndex() << ' ';
			p = p->getNext();
		}
		cout << endl;
	}
}

int* busMap::findDirectPath(int startIndex, int endIndex)
{
	int* dis = new int[busStopsNumber + 1];
	for (int i = 1; i <= busStopsNumber; i++)
		dis[i] = 0x3f3f3f3f;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	//first integer is distance, second is index
	dis[startIndex] = 0;
	pq.push(make_pair(0, startIndex));
	path[startIndex] = 0;
	while (!pq.empty())
	{
		int disnow = pq.top().first, indnow = pq.top().second;
		pq.pop();
		if (dis[indnow] != disnow)
			continue;
		for (myEdge* ep = busStops[indnow]->getDirectEdgeFirst(); ep; ep = ep->getNext())
		{
			int idx = ep->getTo()->getIndex();
			if (dis[idx] > dis[indnow] + ep->getDistance())
			{
				dis[idx] = dis[indnow] + ep->getDistance();
				pq.push(make_pair(dis[idx], idx));
				path[idx] = indnow;
			}
		}
	}
    delete[] dis;
	return path;
}

int* busMap::findEveryPath(int startIndex, int endIndex)
{
    int* pathCopy = new int[busStopsNumber + 1];
	int* dis = new int[busStopsNumber + 1];
	for (int i = 1; i <= busStopsNumber; i++)
		dis[i] = 0x3f3f3f3f;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	//first integer is distance, second is index
	dis[startIndex] = 0;
	pq.push(make_pair(0, startIndex));
    pathCopy[startIndex] = 0;
	while (!pq.empty())
	{
		int disnow = pq.top().first, indnow = pq.top().second;
		pq.pop();
		if (dis[indnow] != disnow)
			continue;
		for (myEdge* ep = busStops[indnow]->getEveryEdgeFirst(); ep; ep = ep->getNext())
		{
			int idx = ep->getTo()->getIndex();
			if (dis[idx] > dis[indnow] + ep->getDistance())
			{
				dis[idx] = dis[indnow] + ep->getDistance();
				pq.push(make_pair(dis[idx], idx));
                pathCopy[idx] = indnow;
			}
		}
	}
    delete[] dis;
    set<int> busLinesSet[busLinesNumber+1];
    for (int i = 1; i <= busLinesNumber; i++)
        for (int j = 1; j <= eachBusLineNumber[i]; j++)
            busLinesSet[i].insert(busLines[i][j]);
    int pointIndex = endIndex;
    while (pathCopy[pointIndex])
    {
        for (int i = 1; i <= busLinesNumber; i++)
        {
            if (busLinesSet[i].count(pathCopy[pointIndex]) && busLinesSet[i].count(pointIndex))
            {
                int __start = 1, __end = 1;
                while (busLines[i][__start] != pathCopy[pointIndex])
                    __start++;
                while (busLines[i][__end] != pointIndex)
                    __end++;
                if (__start < __end)
                    for (int j = __end; j > __start; j--)
                        path[busLines[i][j]] = busLines[i][j - 1];
                else
                    for (int j = __end; j < __start; j++)
                        path[busLines[i][j]] = busLines[i][j + 1];
            }
        }
        pointIndex = pathCopy[pointIndex];
    }
    path[startIndex] = 0;
    delete[] pathCopy;
	return path;
}
