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
#include <chrono>

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
			if (stations.at(index)->GetName() == field) {
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
				if (stations.at(index)->GetName() == field) {
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
}


void TransportationGraph::FindPath(std::string startStationName, std::string endStationName) {
	Station* startStation = nullptr;
	Station* endStation = nullptr;
	for (int index = 0; index < stations.size(); index++) {

		if (stations.at(index)->GetName() == startStationName) {
			startStation = stations.at(index);
			stations.at(index)->SetTimeFromStart(0);
			continue;
		}
		if (stations.at(index)->GetName() == endStationName) {
			endStation = stations.at(index);
		}

	}
	if (startStation == nullptr || endStation == nullptr) {
		throw std::invalid_argument("invalid start or end station");
	}

	std::cout << "* Start Station: " << startStation->GetName() << std::endl;
	std::cout << "* End Station: " << endStation->GetName() << std::endl;
	// station // wegminuten ||
	auto startTime = std::chrono::steady_clock::now();
	dijkstra(startStation, endStation);

	Print(endStation);
	auto endTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << std::endl  << "SearchTime: " << elapsed << std::endl;
}




Station* TransportationGraph::dijkstra(Station* currStation, Station* endStation) {

	//Lambda funktion 
	auto compare = [](const Station* a, Station* b) -> bool {
		return (a->GetTimeFromStart() < b->GetTimeFromStart());
	};


	while (true) {
		if (currStation == endStation) {
			return currStation;
		}
		for (int neighborIndex = 0; neighborIndex < currStation->GetStops().size(); neighborIndex++) {
			if (currStation->GetStops().at(neighborIndex)->GetNextStation()->GetVisited()) {
				continue;
			}
			if (currStation->GetStops().at(neighborIndex)->GetTimeCost() + currStation->GetTimeFromStart() < currStation->GetStops().at(neighborIndex)->GetNextStation()->GetTimeFromStart()) {
				currStation->GetStops().at(neighborIndex)->GetNextStation()->SetTimeFromStart(currStation->GetStops().at(neighborIndex)->GetTimeCost() + currStation->GetTimeFromStart());
				currStation->GetStops().at(neighborIndex)->GetNextStation()->SetParentConnection(new Connection(currStation, currStation->GetStops().at(neighborIndex)->GetLine(), currStation->GetStops().at(neighborIndex)->GetTimeCost()));
			}
		}
			// 1. element finden, welches noch nicht bescucht wurde und den kleinesten weg hat. 
		std::sort(stations.begin(), stations.end(), compare);
		currStation->SetVisited(true);
		for (int index = 0; index < stations.size(); index++) {
			if (!stations.at(index)->GetVisited()) {
				return dijkstra(stations.at(index), endStation);				
			}
		}	
	}
	
}

void TransportationGraph::Print(Station* currStation) {
	
	std::cout << "\n\n";
	std::cout << "Traveling Time: " << currStation->GetTimeFromStart();
	std::cout << "\n\n";
	std::cout <<"[" << currStation->GetName() <<"]" << std::endl;
	std::string lastLine = currStation->GetParentConnection()->GetLine();
	while (currStation->GetParentConnection() != nullptr) {
		
		if (lastLine == currStation->GetParentConnection()->GetLine()) {
			std::cout << "^ Line " << currStation->GetParentConnection()->GetLine() << " Time " << currStation->GetParentConnection()->GetTimeCost() << " ^" << std::endl;
		}
		else {
			std::cout << "^Line " << currStation->GetParentConnection()->GetLine() << " Time " << currStation->GetParentConnection()->GetTimeCost() << " ^ !Last Stop of this Line! " << std::endl;
		}
		std::cout <<"["  << currStation->GetParentConnection()->GetNextStation()->GetName() << "]"<<std::endl;
		lastLine = currStation->GetParentConnection()->GetLine();
		currStation = currStation->GetParentConnection()->GetNextStation();
	}
}

TransportationGraph::~TransportationGraph() {
	stations.clear();
}


