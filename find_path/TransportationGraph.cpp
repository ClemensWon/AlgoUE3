#include "TransportationGraph.h"
#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>

/// <summary>
/// creates graph from input file
/// </summary>
/// <param name="path">path to the input file</param>
void TransportationGraph::CreateFromFile(std::string path) {
	//filereader for accessing the input file
	std::ifstream fileReader;
	//one line of the input file
	std::string line;
	//name of the current line
	std::string connectionName;
	//one field of the input file
	std::string field;
	Station* newStation = nullptr;
	try {
		//opens file stream
		fileReader.open(path);
	}
	catch(std::exception ex) {
		//throws exception if file could not be found
		throw std::invalid_argument("could not find input file");
	}
	while (!fileReader.eof())
	{
		bool isNewStation = true;
		getline(fileReader, line);
		std::stringstream iss(line);

		getline(iss, field, ':');
		//get the name of the current connection line
		std::string connectionName = field;
		getline(iss, field, '"');
		getline(iss, field, '"');
		//checks if the station is already in the graph
		for (int index = 0; index < stations.size(); index++) {
			if (stations.at(index)->GetName() == field) {
				newStation = stations.at(index);
				isNewStation = false;
			}
		}
		//creates new station
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
			//gets time cost of connection
			int timeCost = stoi(field);
			getline(iss, field, '"');
			//checks if the station is already in the graph
			isNewStation = true;
			for (int index = 0; index < stations.size(); index++) {
				if (stations.at(index)->GetName() == field) {
					newStation = stations.at(index);
					isNewStation = false;
				}
			}
			//creates new station
			if (isNewStation) {
				newStation = new Station(field);
				stations.push_back(newStation);
			}
			//creates connection between two stations
			lastStation->AddStop(newStation, timeCost, connectionName);
			newStation->AddStop(lastStation, timeCost, connectionName);
			lastStation = newStation;
			
		}
	}
}

/// <summary>
/// randomly generates a graph
/// </summary>
/// <param name="nodeCount">the amount nodes created</param>
/// <param name="edgeCount">the amount of edges created</param>
/// <param name="costLimit">the range of costs on edges</param>
void TransportationGraph::CreateTestGraph(int nodeCount, int edgeCount, int costLimit) {
	int lineCounter = 0;
	//creates nodes
	for (int counter = 0; counter < nodeCount; counter++) {
		Station* newStation = new Station(std::to_string(counter));
		stations.push_back(newStation);
		//connects every edge to one neighbor so it is save to assume that every node is part of the graph
		if (counter != 0) {
			stations.at(counter - 1)->AddStop(stations.at(counter), (rand() % costLimit) + 1, "U" + std::to_string(lineCounter));
		}
	}
	//connects the last station to the first station
	stations.at(nodeCount - 1)->AddStop(stations.at(0), (rand() % costLimit)+1, "U" + std::to_string(lineCounter));
	lineCounter++;
	for (int counter = 0; counter < nodeCount; counter++) {
		int randomIndex1 = rand() % nodeCount;
		int randomIndex2 = rand() % nodeCount;
		//creates connection between nodes
		stations.at(randomIndex1)->AddStop(stations.at(randomIndex2), (rand() % costLimit) + 1, "U"+std::to_string(lineCounter));
		//randomly changes the line connections belong to
		if (rand() % 10 == 0) {
			lineCounter++;
		}
	}
}



/// <summary>
/// makes preparations for the recursive dijkstra function
/// </summary>
/// <param name="startStationName">the name of the start station</param>
/// <param name="endStationName">the name of the end station</param>
void TransportationGraph::FindPath(std::string startStationName, std::string endStationName) {
	Station* startStation = nullptr;
	Station* endStation = nullptr;
	for (int index = 0; index < stations.size(); index++) {
		//finds start station
		if (stations.at(index)->GetName() == startStationName) {
			startStation = stations.at(index);
			stations.at(index)->SetTimeFromStart(0);
			continue;
		}
		//finds end station
		if (stations.at(index)->GetName() == endStationName) {
			endStation = stations.at(index);
		}

	}
	//throws exception if no start or end station was found
	if (startStation == nullptr || endStation == nullptr) {
		throw std::invalid_argument("invalid start or end station");
	}

	std::cout << "* Start Station: " << startStation->GetName() << std::endl;
	std::cout << "* End Station: " << endStation->GetName() << std::endl;
	//saves start time for runtime meassuring
	auto startTime = std::chrono::steady_clock::now();
	//starts the search
	Station* result = dijkstra(startStation, endStation);
	//returns if no connection between start and end connection is found
	if (result == NULL) {
		std::cout << "could not find a way between start and end station";
		return;
	}
	//saves end time for runtime meassuring
	auto endTime = std::chrono::steady_clock::now();
	//prints the shortest path
	Print(endStation);
	//calculates and prints the runtime
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	std::cout << std::endl  << "SearchTime: " << elapsed << std::endl;
}




Station* TransportationGraph::dijkstra(Station* currStation, Station* endStation) {

	//Lambda funktion 
	auto compare = [](const Station* a, Station* b) -> bool {
		return (a->GetTimeFromStart() < b->GetTimeFromStart());
	};

	//end condition for recursion checks if endsation is reached
	if (currStation == endStation) {
		//returns the endStation
		return currStation;
	}
	//checks if path to neighbours can be updated
	for (int neighborIndex = 0; neighborIndex < currStation->GetStops().size(); neighborIndex++) {
		//skips already visited nodes
		if (currStation->GetStops().at(neighborIndex)->GetNextStation()->GetVisited()) {
			continue;
		}
		//checks if the paths from the current node is faster than the already known paths
		if (currStation->GetStops().at(neighborIndex)->GetTimeCost() + currStation->GetTimeFromStart() < currStation->GetStops().at(neighborIndex)->GetNextStation()->GetTimeFromStart()) {
			//updates the new best paths time cost
			currStation->GetStops().at(neighborIndex)->GetNextStation()->SetTimeFromStart(currStation->GetStops().at(neighborIndex)->GetTimeCost() + currStation->GetTimeFromStart());
			//sets a parent node for finding the path to the start
			currStation->GetStops().at(neighborIndex)->GetNextStation()->SetParentConnection(new Connection(currStation, currStation->GetStops().at(neighborIndex)->GetLine(), currStation->GetStops().at(neighborIndex)->GetTimeCost()));
		}
	}
	//sorts vector
	std::sort(stations.begin(), stations.end(), compare);
	//sets the current note to visited
	currStation->SetVisited(true);
	// 1. element finden, welches noch nicht bescucht wurde und den kleinesten weg hat. 
	for (int index = 0; index < stations.size(); index++) {
		if (!stations.at(index)->GetVisited()) {
			//returns if all of the known neighbors have been searched
			if (stations.at(index)->GetTimeFromStart() == 99999) {
				return NULL;
			}
			//rekursiver Aufruf von Dijkstra mit neuem Knoten. 
			return dijkstra(stations.at(index), endStation);
		}
	}
	
}

/// <summary>
/// prints all stations and connection from last to first
/// </summary>
/// <param name="currStation">the end station</param>
void TransportationGraph::Print(Station* currStation) {
	
	//prints the complete traveling time
	std::cout << "\n\n";
	std::cout << "Traveling Time: " << currStation->GetTimeFromStart();
	std::cout << "\n\n";
	//prints the last station
	std::cout <<"[" << currStation->GetName() <<"]" << std::endl;
	std::string lastLine = currStation->GetParentConnection()->GetLine();
	while (currStation->GetParentConnection() != nullptr) {
		//prints connection
		if (lastLine == currStation->GetParentConnection()->GetLine()) {
			std::cout << "^ Line " << currStation->GetParentConnection()->GetLine() << " Time " << currStation->GetParentConnection()->GetTimeCost() << " ^" << std::endl;
		}
		else {
			std::cout << "^Line " << currStation->GetParentConnection()->GetLine() << " Time " << currStation->GetParentConnection()->GetTimeCost() << " ^ !Last Stop of this Line! " << std::endl;
		}
		//prints station
		std::cout <<"["  << currStation->GetParentConnection()->GetNextStation()->GetName() << "]"<<std::endl;
		lastLine = currStation->GetParentConnection()->GetLine();
		currStation = currStation->GetParentConnection()->GetNextStation();
	}
}

TransportationGraph::~TransportationGraph() {
	stations.clear();
}


