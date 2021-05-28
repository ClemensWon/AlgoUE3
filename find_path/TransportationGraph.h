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

public:
	void CreateFromFile(std::string path);
};



