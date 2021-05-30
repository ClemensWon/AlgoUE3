#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <tuple>

class Station
{
private:
	std::vector<std::tuple<Station*, int, std::string>> nextStops;
	std::tuple<Station*, int, std::string> parentConnection;
	int timeFromStart;
	
	bool visited;

public:
	

	std::string name;

	Station(std::string name);

	// verbindungsstellen!! 
	void AddStop(Station* station, int timeCost, std::string line);

	std::vector<std::tuple<Station*, int, std::string>> GetStops() const;

	void SetVisited(bool visited);

	bool GetVisited() const;

	int GetTimeFromStart() const;

	void SetTimeFromStart(int timeFromStart);

	std::tuple<Station*, int, std::string> GetParentConnection() const;

	void SetParentConnection(std::tuple<Station*, int, std::string>);

};

