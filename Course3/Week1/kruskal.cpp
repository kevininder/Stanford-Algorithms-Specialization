/* Alternative solution to the assignment3 with Kruskal's algorithm. */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>
#include <numeric>

using namespace std;

#define edge tuple<int, int, int>
#define UF pair<int, int>

int findParent(map<int, UF> &status, int i) {
    if (i == status[i].first) return i;
    else return findParent(status, status[i].first);
}

void unionByRank(map<int, UF> &status, int u, int v) {
    if (status[u].second > status[v].second) status[v].first = status[u].first;
    else if (status[u].second < status[v].second) status[u].first = status[v].first;
    else {
        status[v].first = status[u].first;
        status[u].second++;
    }
}

void kruskal(vector<edge> &G, map<int, UF> &status) {
    int i{};
    vector<int> result;
    
    sort(G.begin(), G.end(), [](auto a, auto b){return get<2>(a) < get<2>(b);});

    while (result.size() != status.size()-1) {
        int uSet = findParent(status, get<0>(G[i]));
        int vSet = findParent(status, get<1>(G[i]));

        if (uSet != vSet) {
            result.push_back(get<2>(G[i]));
            unionByRank(status, uSet, vSet);
        }
        i++;
    }

    cout << accumulate(result.begin(), result.end(), 0);
}

int main() {
    int vertices, edges, source, destination, weight;
    vector<edge> G;
    map<int, UF> status;
    ifstream file("edges.txt");

    file >> vertices >> edges;

    while (file >> source >> destination >> weight) {
        G.push_back(edge(source, destination, weight));
    }
    
    for (auto i = 1; i <= vertices; i++) status.insert(pair(i, UF(i, 0)));  
    
    kruskal(G, status);
    
    return 0;
}