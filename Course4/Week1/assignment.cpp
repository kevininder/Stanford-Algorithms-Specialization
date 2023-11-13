/* Implementation of Floyd-Warshall algorithm.
   Note to self, array is way faster than vector in this regard.
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

#define type priority_queue<int, vector<int>, greater<>>
#define V 1000

int findShortestPath(int graph[][V], type &minValue) {
    for (auto k = 0; k < V; k++) {
        for (auto i = 0; i < V; i++) {
            for (auto j = 0; j < V; j++) {
                if (graph[i][k] == INT_MAX || graph[k][j] == INT_MAX) continue;
                else if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    minValue.push(graph[i][j]);
                }
            }
        }
    }

    for (auto i = 0; i < V; i++) if (graph[i][i] < 0) return INT_MIN;
    return minValue.top();
}

int main() {
    int count{};
    string fileName[3] = {"g1.txt", "g2.txt", "g3.txt"};
    vector<int> result;
    
    for (auto i = 0; i < 3; i++) {
        int vertices, edges, source, destination, length, graph[V][V];
        type minValue;
        ifstream file(fileName[i]);

        fill(*graph, *graph + V*V, INT_MAX);
        for (auto j = 0; j < vertices; j++) graph[j][j] = 0;

        file >> vertices >> edges;

        while (file >> source >> destination >> length) {
            graph[source-1][destination-1] = length;
        }
        
        result.push_back(findShortestPath(graph, minValue));
        file.close();
    }

    for (auto i : result) if (i == INT_MIN) count++;

    if (count < 3) {
        for (auto i : result) if (i != INT_MIN) cout << i << ',';
    }
    else cout << "NULL "; 

    cout << '\b';
    
    return 0;
}