/* Implementation of Dijkstra's algorithm. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

int findMin(vector<tuple<int, bool>> &result) {
    int min{INT_MAX}, index;

    for (auto i = 0; i < result.size(); i++) {
        if (!get<1>(result[i]) && get<0>(result[i]) <= min) {
            min = get<0>(result[i]);
            index = i;
        }
    }
    
    return index;
}

int main() {
    int vertex{200}, edges[vertex][vertex], array[10] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
    string data;
    memset(edges, 0, sizeof edges);
    vector<tuple<int, bool>> result(vertex, make_tuple(INT_MAX, false));
    get<0>(result[0]) = 0;
    ifstream file("dijkstraData.txt");

    while (getline(file, data)) {
        int source, destination, length;
        char comma;
        istringstream iss(data);

        iss >> source;

        while (iss >> destination >> comma >> length) {
            edges[source-1][destination-1] = length;
        }
    }

    for (auto i = 0; i < vertex-1; i++) {
        int index = findMin(result);
        
        get<1>(result[index]) = true;
        
        for (auto j = 0; j < vertex; j++) {
            if (edges[index][j] 
            && !get<1>(result[j])
            && get<0>(result[index]) + edges[index][j] < get<0>(result[j])) get<0>(result[j]) = get<0>(result[index]) + edges[index][j];
        }
    }
    
    for (auto i = 0; i < 10; i++) {
        cout << get<0>(result[array[i]-1]) << ',';
    }

    cout << "\b";
    
    return 0;
}