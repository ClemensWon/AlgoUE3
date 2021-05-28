#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <tuple>

class Station
{
private:
	std::vector<std::tuple<Station*, int>> nextStops;
	
	bool visited;

public:
	std::string name;

	Station(std::string name);

	// verbindungsstellen!! 
	void AddStop(Station* station, int timeCost);


};

