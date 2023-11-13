#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Graph {
    friend ostream &operator<<(ostream &out, const Graph &graph) {
        auto it{graph.adjList.begin()};

        while (it != graph.adjList.end()) {
            out << it->first << "-> ";
            for (auto i : graph.adjList.at(it->first))
                out << i << ' ';
            out << endl;
            it++;
        }

        return out;
    }
    public:
        map<int, bool> visited;
        queue<int> Q;
        stack<int> S;

        Graph(int V) : V(V){}
        void addEdges(int src, int dest);
        void setStatus();
        int getV() const{return V;}
        void BFS(int s);
        void DFS(int s);
        void topoSort(int s);
        virtual ~Graph(){}
    private:
        int V{};
        map<int, list<int>> adjList;
};

void Graph::addEdges(int src, int dest) {
    adjList[src].push_back(dest); 
}

void Graph::setStatus() {
    visited.clear();
    for (auto i = 0; i < V; i++) visited.insert(pair(i, false));
}

void Graph::BFS(int s) {
    visited[s] = true;
    Q.push(s);

    while (!Q.empty()) {
        cout << Q.front();
        
        for (auto i : adjList[Q.front()])
            if (!visited[i]) {
                visited[i] = true;
                Q.push(i);
            }
        Q.pop();
    }
}

void Graph::DFS(int s) {
    visited[s] = true;
    cout << s;
    for (auto i : adjList[s]) if (!visited[i]) DFS(i);
}

void Graph::topoSort(int s) {
    visited[s] = true;
    for (auto i : adjList[s]) if (!visited[i]) topoSort(i);
    S.push(s);
}

int main() {
    int source, destination;
    Graph graph(6);
    ifstream file("graphTraversal.txt");

    while (file >> source >> destination) {
        graph.addEdges(source, destination);
    }

    cout << graph;

    graph.setStatus();
    graph.BFS(5);

    cout << endl;

    graph.setStatus();
    graph.DFS(5);

    cout << endl;

    graph.setStatus();
    for (auto i = 0; i < 6; i++) if (!graph.visited[i]) graph.topoSort(i);
    
    while (!graph.S.empty()) {
        cout << graph.S.top();
        graph.S.pop();
    }

    return 0;
}