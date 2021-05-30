#include "Station.h"

Station::Station(std::string name) {
	this->name = name;
	this->visited = false;
	this->parentConnection = nullptr;
	this->timeFromStart = 99999;
}



void Station::AddStop(Station* station, int timeCost, std::string line) {
	
	this->nextStops.push_back(new Connection(station, line, timeCost));
}

std::vector<Connection*> Station::GetStops() const {
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

Connection* Station::GetParentConnection() const {
	return this->parentConnection;
}

void Station::SetParentConnection(Connection* parentConnection) {
	this->parentConnection = parentConnection;
}

std::string Station::GetName() const {
	return this->name;
}