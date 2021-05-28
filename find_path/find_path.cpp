// find_path.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "TransportationGraph.h"
#include <string>
#include <functional>
#include <queue>


int main()
{
    TransportationGraph* transportGraph = new TransportationGraph();
    transportGraph->CreateFromFile("ADS_Programmieraufgabe3_WienerVerkehrsNetz.txt");
}

