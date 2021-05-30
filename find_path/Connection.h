#pragma once

#include<string>

class Station;

class Connection
{
private:
	Station* nextStation;
	std::string line;
	int timeCost;

public:
	Connection(Station* nextStation, std::string line, int timeCost);

	Station* GetNextStation() const;

	std::string GetLine() const;

	int GetTimeCost() const;
};


