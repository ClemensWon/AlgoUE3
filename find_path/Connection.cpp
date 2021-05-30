#include "Connection.h"

Connection::Connection(Station* nextStation, std::string line, int timeCost) {
	this->nextStation = nextStation;
	this->line = line;
	this->timeCost = timeCost;
}

Station* Connection::GetNextStation() const {
	return this->nextStation;
}

std::string Connection::GetLine() const {
	return this->line;
}

int Connection::GetTimeCost() const {
	return this->timeCost;
}