#include "TransportationGraph.h"
#include <iostream>
#include <string>
#include <functional>
#include <queue>


void TransportationGraph::CreateFromFile(std::string path) {
    std::ifstream fileReader;
    std::string line;
    std::string field;
    fileReader.open(path);
    while (!fileReader.eof())
    {
        getline(fileReader, line);
        std::stringstream iss(line);

        getline(iss, field, ':');
        std::string line = field;
        getline(iss, field, '"');
        getline(iss, field, '"');       

        Station* newStation = new Station(field);
        std::cout << "before while loop " << field << std::endl;
        stations.push_back(newStation);
        while (!iss.eof()) {
            getline(iss, field, '"');
            if (field == "") {
                break;
            }
            field = field.at(1);
            std::cout << "cost: " << field << std::endl;
            //kosten herholen 
            int timeCost = stoi(field);
            getline(iss, field, '"');
            std::cout << "stations: " << field << std::endl;
            Station* newStation = new Station(field);
            stations.back()->AddStop(newStation, timeCost);
            newStation->AddStop(stations.back(), timeCost);
            stations.push_back(newStation);
        }
    }
    for (int index = 0; index < stations.size(); index++) {
        std::cout << stations.at(index)->name << std::endl;
    }
}






/*
// Pseudo 
void dijkstra(int s) {
// station // wegminuten ||
    std::priority_queue<Station, int> searchStations;
  //priority_queue    <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  for (int i=0; i<N; i++) dist[i] = INF;
  dist[s] = 0;
  pq.push(make_pair(0, s));
  while (!pq.empty()) {
    pair<int, int> front = pq.top();
    pq.pop();
    int w = front.first, u = front.second;
    if (w > dist[u]) continue;
    for (int i=0; i<adj[u].size(); i++) {
      pair<int, int> v = adj[u][i];
      if (dist[v.first] > dist[u] + v.second) {
        dist[v.first] = dist[u] + v.second;
        pq.push(make_pair(dist[v.first], v.first));
      }
    }
  }
}



*/

/*
public List<int> GetRateLine(string justALine)
{
    const string reg = @"^\d{1,}.+\[(.*)\s[\-]\d{1,}].+GET.*HTTP.*\d{3}[\s](\d{1,})[\s](\d{1,})$";
    Match match = Regex.Match(justALine, reg,
                                RegexOptions.IgnoreCase);

    // Here we check the Match instance.
    if (match.Success)
    {
        // Finally, we get the Group value and display it.

        string theRate = match.Groups[3].Value;
        Ratestorage.Add(Convert.ToInt32(theRate));
    }
    else
    {
        Ratestorage.Add(0);
    }
    return Ratestorage;
}

//---------------------------------


*/






