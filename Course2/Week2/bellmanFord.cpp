/* Alternative solution to the assignment with Bellman-Ford algorithm. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

#define edges pair<int, int>
#define status pair<int, int>

void bellmanFord(map<edges, int> &graph, map<int, status> &result) {  
    bool update;
    int array[10] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};

    for (auto i = 0; i < result.size()-1; i++) {
        update = false;

        for (auto j : graph)
            if (result[j.first.first].second != INT_MAX && result[j.first.first].second + j.second < result[j.first.second].second) {
                result[j.first.second].first = j.first.first;
                result[j.first.second].second = result[j.first.first].second + j.second;
                update = true;
            }      
        if (!update) break;
    }

    if (update) {
        for (auto i : graph) {
            if (result[i.first.first].second != INT_MAX && result[i.first.first].second + i.second < result[i.first.second].second) {
                cout << "Negative cycle detected!!";
                return;
            }
        }
    }
    for (auto i = 0; i < 10; i++) cout << result[array[i]].second << ',';

    cout << '\b';
}

int main() {
    map<edges, int> graph;
    string data;
    ifstream file("dijkstraData.txt");

    while (getline(file, data)) {
        int source, destination, length;
        char comma;
        istringstream iss(data);

        iss >> source;

        while (iss >> destination >> comma >> length) {
            graph.insert(pair(edges(source, destination), length));
        }
    }
    
    map<int, status> result;
    for (auto i = 1; i <= 200; i++) result.insert(pair(i, status(-1, INT_MAX)));
    result[1].second = 0;

    bellmanFord(graph, result);
    
    return 0;
}