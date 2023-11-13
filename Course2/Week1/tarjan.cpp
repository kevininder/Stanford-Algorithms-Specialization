/* Alternative solution to the assignment with Tarjan's algorithm.
   Note. This approach works fine on a much smaller scale. But this graph is quite large, and hence stack overflow may ensue.
   Try "ulimit -s unlimited"(for Mac) in terminal before running the code.
   This command removes the stack size limit for the shell session. After running this command, execute the program from the same terminal window.
   However, this may solve the segmentation fault issue caused by a small stack size, it's not a fundamental solution.
   Recursive algorithms can still run into issues for very large input sizes, and an iterative approach might be more robust in such cases.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>

using namespace std;

#define status tuple<int, int, bool>

class Graph {
    public:
        map<int, status> M;

        Graph(int V) : V(V){}
        void addEdges(int src, int dest);
        void setStatus();
        void DFS(int s, stack<int> &S, vector<int> &result);
        void findSCCs();
        virtual ~Graph(){}
    private:
        int V{};
        map<int, list<int>> adjList;
};

void Graph::addEdges(int src, int dest) {
    adjList[src].push_back(dest);
}

void Graph::setStatus() {
    for (auto i = 1; i <= V; i++) M.insert(pair(i, make_tuple(0, 0, false)));
}

void Graph::DFS(int s, stack<int> &S, vector<int> &result) {
    int count{};
    static int t{1};

    get<0>(M[s]) = get<1>(M[s]) = t++;
    get<2>(M[s]) = true;
    S.push(s);

    for (auto i : adjList[s]) {
        if (!get<0>(M[i])) {
            DFS(i, S, result);
            get<1>(M[s]) = min(get<1>(M[s]), get<1>(M[i]));
        }
        else if (get<2>(M[i])) get<1>(M[s]) = min(get<1>(M[s]), get<0>(M[i]));
    }
    
    if (get<0>(M[s]) == get<1>(M[s])) {
        while (S.top() != s) {
            count++;
            get<2>(M[S.top()]) = false;
            S.pop();
        }
        count++;
        get<2>(M[S.top()]) = false;
        S.pop();
        result.push_back(count);
    }
}

void Graph::findSCCs() {
    vector<int> result;
    stack<int> S;

    setStatus();
    for (auto i = 1; i <= V; i++) if (!get<0>(M[i])) DFS(i, S, result);

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