/* Implementation of Karger's algorithm with concept of union-find data structure. */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define edge pair<int, int>

class Graph {
    friend ostream &operator<<(ostream &out, const Graph &graph) {
        for (auto i : graph.G)
            out << i.first << ' ' << i.second << endl;

        return out;
    }
    public:
        int V;
        vector<edge> G;

        Graph(int V) : V(V){}
        int E() const{
            return G.size();
        }
        void setStatus();
        int findParent(int i);
        void unionByRank(int u, int v);
        virtual ~Graph(){}
    private:
        vector<int> parent, rank;
};

void Graph::setStatus() {
    parent.clear();
    rank.clear();

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

int findMinCut(Graph &graph) {
    int count{graph.V}, total{};

    graph.setStatus();

    while (count > 2) {
        int uSet, vSet, mod;

        mod = rand() % graph.E();
        uSet = graph.findParent(graph.G[mod].first-1);
        vSet = graph.findParent(graph.G[mod].second-1);

        if (uSet != vSet) {
            graph.unionByRank(uSet, vSet);
            count--;
        }
    }
    
    for (auto i = 0; i < graph.E(); i++) {
        int uSet = graph.findParent(graph.G[i].first-1);
        int vSet = graph.findParent(graph.G[i].second-1);

        if (uSet != vSet) total++;
    }
    
    return total;
}

int main() {
    int source, destination, iteration{200};
    Graph graph(200);
    vector<int> result;
    string data;
    ifstream file("kargerMinCut.txt");

    srand(time(0));

    while (getline(file, data)) {
        istringstream iss(data);
        
        iss >> source;

        while (iss >> destination) {
            if (destination > source) graph.G.push_back(make_pair(source, destination));
        }
    }

    while (iteration--) {
        result.push_back(findMinCut(graph));
    }
    
    cout << *min_element(result.begin(), result.end());

    return 0;
}