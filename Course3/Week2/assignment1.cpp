/* Implementation of clustering algorithm. */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define edge pair<int, int>

class Graph {
    public:
        vector<pair<int, edge>> G;
        
        Graph(int V);
        int findParent(int i);
        void unionByRank(int u, int v);
        void clustering(int k);
        virtual ~Graph(){}
    private:
        int V;
        vector<int> parent, rank;
};

Graph::Graph(int V) {
    for (auto i = 0; i < V; i++) {
        parent.push_back(i);
        rank.push_back(0);
    }
}

int Graph::findParent(int i) {
    if (i == parent[i]) return i;
    else return findParent(parent[i]);
}

void Graph::unionByRank(int u, int v) {
    if (rank[u] > rank[v]) parent[v] = parent[u];
    else if (rank[u] < rank[v]) parent[u] = parent[v];
    else {
        parent[v] = parent[u];
        rank[u]++;
    }
}

void Graph::clustering(int k) {
    int i{}, count{}, uSet, vSet;

    sort(G.begin(), G.end());
    
    while (k != count) {
        uSet = findParent(G[i].second.first);
        vSet = findParent(G[i].second.second);
        if (uSet != vSet) unionByRank(uSet, vSet);
        i++;
        count = 0;

        for (auto j = 0; j < G.size(); j++) {
            if (j == parent[j]) count++;
        }
    }
    
    while (1) {
        uSet = findParent(G[i].second.first);
        vSet = findParent(G[i].second.second);
        if (uSet != vSet) break;
        i++;
    }
    
    cout << G[i].first;
}

int main() {
    int vertices, source, destination, weight;
    ifstream file("clustering1.txt");

    file >> vertices;

    Graph graph(vertices);

    while (file >> source >> destination >> weight) {
        graph.G.push_back(make_pair(weight, edge(source, destination)));
    }
    
    graph.clustering(4);

    return 0;
}