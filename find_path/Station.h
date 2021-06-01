#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include "Connection.h"

class Station
{
private:
	std::vector<Connection*> nextStops;
	Connection* parentConnection;
	int timeFromStart;

	std::string name;
	
	bool visited;


public:
	

	Station(std::string name);

	~Station();

	// verbindungsstellen!! 
	void AddStop(Station* station, int timeCost, std::string line);

	std::vector<Connection*> GetStops() const;

	void SetVisited(bool visited);

	bool GetVisited() const;

	int GetTimeFromStart() const;

	void SetTimeFromStart(int timeFromStart);

	Connection* GetParentConnection() const;

	void SetParentConnection(Connection* parentConnection);

	std::string GetName() const;

};

