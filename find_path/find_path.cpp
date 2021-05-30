// find_path.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "TransportationGraph.h"
#include <string>
#include <functional>
#include <queue>
#include <stdexcept>
#include <cstdlib>


int main(int argc, char* argv[])
{
    /*if (argc != 4) {
        throw std::invalid_argument("wrong number of arguments");
        return 1;
    }
    
    TransportationGraph* transportGraph = new TransportationGraph();
    transportGraph->CreateFromFile(argv[1]);
    transportGraph->dijkstra(argv[2], argv[3]);
    delete transportGraph;
    */
    TransportationGraph* transportGraph = new TransportationGraph();
    transportGraph->CreateFromFile("ADS.txt");
    transportGraph->dijkstra("Praterstern", "Floridsdorf");
}

