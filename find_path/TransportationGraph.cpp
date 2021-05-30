#include "TransportationGraph.h"
#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <string_view>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstdlib>

void TransportationGraph::CreateFromFile(std::string path) {
	std::ifstream fileReader;
	std::string line;
	std::string connectionName;
	std::string field;
	Station* newStation = nullptr;
	try {
		fileReader.open(path);
	}
	catch(std::exception ex) {
		throw std::invalid_argument("could not find input file");
	}
	while (!fileReader.eof())
	{
		bool isNewStation = true;
		getline(fileReader, line);
		std::stringstream iss(line);

		getline(iss, field, ':');
		std::string connectionName = field;
		getline(iss, field, '"');
		getline(iss, field, '"');
		for (int index = 0; index < stations.size(); index++) {
			if (stations.at(index)->name == field) {
				newStation = stations.at(index);
				isNewStation = false;
			}
		}
		if (isNewStation) {
			newStation = new Station(field);
			stations.push_back(newStation);
		}
		Station* lastStation = newStation;
		while (!iss.eof()) {
			getline(iss, field, '"');
			if (field == "") {
				break;
			}
			field = field.at(1);
			//kosten herholen 
			int timeCost = stoi(field);
			getline(iss, field, '"');
			isNewStation = true;
			for (int index = 0; index < stations.size(); index++) {
				if (stations.at(index)->name == field) {
					newStation = stations.at(index);
					isNewStation = false;
				}
			}
			if (isNewStation) {
				newStation = new Station(field);
				stations.push_back(newStation);
			}
			lastStation->AddStop(newStation, timeCost, connectionName);
			newStation->AddStop(lastStation, timeCost, connectionName);
			lastStation = newStation;
			
		}
	}
	/*for (int index = 0; index < stations.size(); index++) {
		std::cout << stations.at(index)->name << std::endl;
	}*/
}







void TransportationGraph::dijkstra(std::string startStationName, std::string endStationName) {

	//Lambda funktion 
	auto compare = [](const Station* a, Station* b) -> bool {
		return (a->GetTimeFromStart() < b->GetTimeFromStart());
	};

	std::stack<Station*> parents;
	Station* startStation = nullptr;
	Station* endStation = nullptr;
	//std::vector<std::tuple<Station*, int>> searchStations;
	for (int index = 0; index < stations.size(); index++) {
		
		if (stations.at(index)->name == startStationName) {
			startStation = stations.at(index);
			stations.at(index)->SetTimeFromStart(0);
			continue;
		}
		if (stations.at(index)->name == endStationName) {
			endStation = stations.at(index);
		}
		
	}
	if (startStation == nullptr || endStation == nullptr) {
		throw std::invalid_argument("invalid start or end station");
	}
	
	std::cout << "* Start Station: " << startStation->name << std::endl;
	std::cout << "* End Station: " << endStation->name << std::endl;
	// station // wegminuten ||

	
	int minTime = 99999;
	Station* currStation = startStation;
	int timeBehind = 0;
	while (true) {
		if (currStation == endStation) {
			break;
		}
		parents.push(currStation);
		for (int neighborIndex = 0; neighborIndex < currStation->GetStops().size(); neighborIndex++) {
			if (std::get<0>(currStation->GetStops().at(neighborIndex))->GetVisited()) {
				continue;
			}
			for (int searchIndex = 0; searchIndex < stations.size(); searchIndex++) {
				if (std::get<0>(currStation->GetStops().at(neighborIndex)) == stations.at(searchIndex)
					&& std::get<1>(currStation->GetStops().at(neighborIndex)) + currStation->GetTimeFromStart() < stations.at(searchIndex)->GetTimeFromStart()) {
					stations.at(searchIndex)->SetTimeFromStart(std::get<1>(currStation->GetStops().at(neighborIndex)) + currStation->GetTimeFromStart());
					stations.at(searchIndex)->SetParentConnection(std::make_tuple(currStation, std::get<1>(currStation->GetStops().at(neighborIndex)), std::get<2>(currStation->GetStops().at(neighborIndex))));
				}
			}
		}
			// 1. element finden, welches noch nicht bescucht wurde und den kleinesten weg hat. 
		std::sort(stations.begin(), stations.end(), compare);
		currStation->SetVisited(true);
		for (int index = 0; index < stations.size(); index++) {
			if (!stations.at(index)->GetVisited()) {
				currStation = stations.at(index);
				break;
			}
		}	
	}

	Print(currStation);

	 /*std::cout << "*****************************************\n";
	std::cout << "* time from start: " << currStation->GetTimeFromStart() << std::endl << std::endl;
	while (std::get<0>(currStation->GetParentConnection())!= nullptr) {
		std::cout << std::get<0>(currStation->GetParentConnection())->name << " : " << std::get<1>(currStation->GetParentConnection())<< ":" << std::get<2>(currStation->GetParentConnection()) <<std::endl;
		currStation = std::get<0>(currStation->GetParentConnection());
		 std::cout << "*****************************************\n";
	}
	*/
}

void TransportationGraph::Print(Station* currStation) {
	
	std::cout << "\n\n";
	std::cout << "Traveling Time: " << currStation->GetTimeFromStart();
	std::cout << "\n\n";
	std::cout <<"[" << currStation->name <<"]" << std::endl;
	std::string lastLine = std::get<2>(currStation->GetParentConnection());
	while (std::get<0>(currStation->GetParentConnection()) != nullptr) {
		
		if (lastLine == std::get<2>(currStation->GetParentConnection())) {
			std::cout << "^ Line " << std::get<2>(currStation->GetParentConnection()) << " Time " << std::get<1>(currStation->GetParentConnection()) << " ^" << std::endl;
		}
		else {
			std::cout << "^Line " << std::get<2>(currStation->GetParentConnection()) << " Time " << std::get<1>(currStation->GetParentConnection()) << " ^ !Last Stop of this Line! " << std::endl;
		}
		std::cout <<"["  <<std::get<0>(currStation->GetParentConnection())->name << "]"<<std::endl;
		lastLine = std::get<2>(currStation->GetParentConnection());
		currStation = std::get<0>(currStation->GetParentConnection());
	}
	//std::cout << std::get<0>(currStation->GetParentConnection())->name;
}

TransportationGraph::~TransportationGraph() {
	stations.clear();
}


