#include "Station.h"

Station::Station(std::string name) {
	this->name = name;
	this->visited = false;
}

void Station::AddStop(Station* station, int timeCost) {
	this->nextStops.push_back(std::tuple<Station*, int>(station, timeCost));
}