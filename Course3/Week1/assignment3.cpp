/* Implementation of Prim's algorithm. */

#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <cstring>

using namespace std;

int findMin(vector<tuple<int, int, bool>> &edge) {
    int index, min{INT_MAX};

    for (auto i = 0; i < edge.size(); i++) {
        if (!get<2>(edge[i]) && get<1>(edge[i]) <= min) {
            min = get<1>(edge[i]);
            index = i;
        }
    }

    return index;
}

int main() {
    int vertices, edges, source, destination, weight, result{};
    ifstream file("edges.txt");

    file >> vertices >> edges;

    vector<tuple<int, int, bool>> edge(vertices, make_tuple(-1, INT_MAX, false));
    get<1>(edge[0]) = 0;
    int graph[vertices][vertices];
    memset(graph, 0, sizeof graph);

    while (file >> source >> destination >> weight) {
        graph[source-1][destination-1] = weight;
        graph[destination-1][source-1] = weight;
    }

    for (auto i = 0; i < vertices-1; i++) {
        int index = findMin(edge);
        
        get<2>(edge[index]) = true;
        
        for (auto j = 0; j < vertices; j++) {
            if (graph[index][j] && graph[index][j] < get<1>(edge[j]) && !get<2>(edge[j])) {
                get<1>(edge[j]) = graph[index][j];
                get<0>(edge[j]) = index;
            }
        } 
    }

    for (auto i = 1; i < vertices; i++) {
        result += graph[i][get<0>(edge[i])];
    }

    cout << result;
    
    return 0;
}