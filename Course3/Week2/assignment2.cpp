/* Clustering algorithm with bit manipulation. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
    public:
        int n{}, b{};

        Graph(int n, int b) : n(n), b(b){}
        void setGraph(vector<string> &V);
        void setStatus();
        int findParent(int i);
        void unionByRank(int u, int v, int &count);
        int clustering(vector<string> &V);
        virtual ~Graph(){}
    private:
        vector<int> parent, rank;
        unordered_map<string, int> M;
};

void Graph::setGraph(vector<string> &V) {
    for (auto i = 0; i < V.size(); i++) M.emplace(V[i], i);
}

void Graph::setStatus() {
    for (auto i = 0; i < n; i++) {
        parent.push_back(i);
        rank.push_back(0);
    } 
}

int Graph::findParent(int i) {
    if (i == parent[i]) return i;
    else return findParent(parent[i]);
}

void Graph::unionByRank(int uSet, int vSet, int &count) {
    int u = findParent(uSet);
    int v = findParent(vSet);

    if (u != v) {
        if (rank[u] > rank[v]) parent[v] = parent[u];
        else if (rank[u] < rank[v]) parent[u] = parent[v];
        else {
            parent[v] = parent[u];
            rank[u]++;
        }
        count--;
    }
}

int Graph::clustering(vector<string> &V) {
    int count{n};

    setStatus();

    for (auto i = 0; i < n; i++) {
        if (M.find(V[i]) != M.end() && M[V[i]] != i) unionByRank(i, M[V[i]], count);

        for (auto j = 0; j < b; j++) {
            string str1 = V[i];
            str1[j] ^= 1;

            if (M.find(str1) != M.end()) unionByRank(i, M[str1], count);

            for (auto k = j+1; k < b; k++) {
                string str2 = str1;
                str2[k] ^= 1;

                if (M.find(str2) != M.end()) unionByRank(i, M[str2], count);
            }
        }
    }
    
    return count;
}

int main() {
    int number, bits;
    string data;
    vector<string> V;
    ifstream file("clustering_big.txt");
    
    file >> number >> bits;

    Graph graph(number, bits);

    while (getline(file, data)) {
        string node, b;
        istringstream iss(data);

        if (!data.length()) continue;

        while (iss >> b) {
            node += b;
        }

        V.push_back(node);
    }

    graph.setGraph(V);

    cout << graph.clustering(V);

    return 0;
}
