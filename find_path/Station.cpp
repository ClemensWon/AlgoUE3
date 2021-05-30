#include "Station.h"

Station::Station(std::string name) {
	this->name = name;
	this->visited = false;
	this->parentConnection = std::make_tuple(nullptr, 0, "");
	this->timeFromStart = 99999;
}



void Station::AddStop(Station* station, int timeCost, std::string line) {
	
	this->nextStops.push_back(std::tuple<Station*, int, std::string>(station, timeCost, line));
}

std::vector<std::tuple<Station*, int, std::string>> Station::GetStops() const {
	return this->nextStops;
}

void Station::SetVisited(bool visited) {
	this->visited = visited;
}

bool Station::GetVisited() const {
	return this->visited;
}

int Station::GetTimeFromStart() const {
	return this->timeFromStart;
}

void Station::SetTimeFromStart(int timeFromStart) {
	this->timeFromStart = timeFromStart;
}

std::tuple<Station*, int, std::string> Station::GetParentConnection() const {
	return this->parentConnection;
}

void Station::SetParentConnection(std::tuple<Station*, int, std::string> parentConnection) {
	this->parentConnection = parentConnection;
}