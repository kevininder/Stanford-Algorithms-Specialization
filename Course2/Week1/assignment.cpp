/* Implementation of Kosaraju's algorithm. */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <functional>

using namespace std;

class Graph {
    public:
        stack<int> order;
        map<int, bool> visited;

        Graph(int V) : V(V){}
        void addEdges(int src, int dest);
        void setStatus();
        void DFS1(int s);
        void DFS2(int s, int &count);
        void findSCCs();
        virtual ~Graph(){}
    private:
        int V{};
        map<int, list<int>> adjList, trans;
};

void Graph::addEdges(int src, int dest) {
    adjList[src].push_back(dest);
    trans[dest].push_back(src);
}

void Graph::setStatus() {
    visited.clear();
    for (auto i = 1; i <= V; i++) visited.insert(pair(i, false));
}

void Graph::DFS1(int s) {
    visited[s] = true;
    for (auto i : adjList[s]) if (!visited[i]) DFS1(i);
    order.push(s);
}

void Graph::DFS2(int s, int &count) {
    visited[s] = true;

    for (auto i : trans[s])
        if (!visited[i]) {
            DFS2(i, count);
            count++;
        }
}

void Graph::findSCCs() {
    int count;
    vector<int> result;

    setStatus();
    for (auto i = 1; i <= V; i++) if (!visited[i]) DFS1(i);

    setStatus();

    while (!order.empty()) {
        if (!visited[order.top()]) {
            count = 1;
            DFS2(order.top(), count);
            result.push_back(count);
        }
        order.pop();
    }

    sort(result.begin(), result.end(), greater<int>());
    for (auto i = 0; i < 5; i++) cout << result[i] << ',';

    cout << '\b';
}

int main() {
    int source, destination;
    Graph graph(875714);
    ifstream file("SCC.txt");

    while (file >> source >> destination) {
        graph.addEdges(source, destination);
    }

    graph.findSCCs();

    return 0;
}