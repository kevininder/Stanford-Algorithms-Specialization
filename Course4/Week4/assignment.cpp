/* Iconic 2SAT problem with concept of CNF, implication graph and Kosaraju's algorithm. 
   Note to self, normal array is way faster than map in this regard.
   But in order to tackle all six graphs at the same time, only map seems to work.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include <list>

using namespace std;

#define MAX 2000001

class Graph {
    public:
        map<int, bool> visited;
        stack<int> order;

        Graph(int V) : V(V){}
        void addEdges(int src, int dest);
        void setStatus();
        void DFS1(int s);
        void DFS2(int s, int &count, int SCCs[]);
        int is2SAT();
        virtual ~Graph(){}
    public:
        int V{};
        map<int, list<int>> G, tG;
};

void Graph::addEdges(int src, int dest) {
    G[src].push_back(dest);
    tG[dest].push_back(src);
}

void Graph::setStatus() {
    visited.clear();
    for (auto i = 1; i <= 2*V; i++) visited.insert(pair(i, false));  
}

void Graph::DFS1(int s) {
    visited[s] = true;
    for (auto i : G[s]) if (!visited[i]) DFS1(i);
    order.push(s);
}

void Graph::DFS2(int s, int &count, int SCCs[]) {
    visited[s] = true;
    for (auto i : tG[s]) if (!visited[i]) DFS2(i, count, SCCs);
    SCCs[s] = count;
}

int Graph::is2SAT() {
    int count{}, SCCs[MAX];

    setStatus();
    for (auto i = 1; i <= 2*V; i++) if (!visited[i]) DFS1(i);
    
    setStatus();

    while (!order.empty()) {
        if (!visited[order.top()]) {
            count++;
            DFS2(order.top(), count, SCCs);
        }
        order.pop();
    }
    
    for (auto i = 1; i <= V; i++) if (SCCs[i] == SCCs[i+V]) return 0;
    return 1;
}

int main() {
    string fileName[6] = {"2sat1.txt", "2sat2.txt", "2sat3.txt", "2sat4.txt", "2sat5.txt", "2sat6.txt"};
    vector<int> result;

    for (auto i = 0; i < 6; i++) {
        int number, value1, value2;
        ifstream file(fileName[i]);

        file >> number;

        Graph graph(number);

        while (file >> value1 >> value2) {
            if (value1 > 0 && value2 > 0) {
                graph.addEdges(value1 + number, value2);
                graph.addEdges(value2 + number, value1);
            }
            else if (value1 > 0 && value2 < 0) {
                graph.addEdges(value1 + number, number - value2);
                graph.addEdges(-value2, value1);
            }
            else if (value1 < 0 && value2 > 0) {
                graph.addEdges(-value1, value2);
                graph.addEdges(value2 + number, number - value1);
            }
            else {
                graph.addEdges(-value1, number - value2);
                graph.addEdges(-value2, number - value1);
            }
        }
        
        result.push_back(graph.is2SAT());        
        file.close();
    }
    
    for (auto i : result) cout << i;

    return 0;
}