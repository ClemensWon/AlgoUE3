#pragma once
#include <vector>
#include "Station.h"
#include <fstream> 
#include <sstream> 
#include<algorithm>
#include <queue>

class TransportationGraph
{

	std::vector<Station*> stations;

	void Print(Station* currStation);

public:
	void CreateFromFile(std::string path);

	void CreateTestGraph(int nodeCount, int edgeCount, int costLimit);

	void FindPath(std::string startStationName, std::string endStationName);

	Station* dijkstra(Station* currStation, Station* endStation);

	~TransportationGraph();
};



