/* Knapsack problem with a refined DP solution, e.g. top-down approach/concept of memoization to avoid redundant recursion.
   Performance check included.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

#define item pair<int, int>

int findValue(vector<item> &K, map<item, int> &V, int i, int w) {
    if (i >= 0) {
        if (V.find(pair(i, w)) != V.end()) return V[pair(i, w)];
        else {
            if (w < K.front().second) V[pair(i, w)] = 0;
            else if (w < K[i].second) findValue(K, V, i-1, w);
            else V[pair(i, w)] = max(findValue(K, V, i-1, w), findValue(K, V, i-1, w-K[i].second) + K[i].first);
            return V[pair(i, w)];
        }
    }
    else return 0;
}

int main() {
    clock_t start, end;
    start = clock();

    int W, number, value, weight;
    vector<item> K;
    map<item, int> V;
    ifstream file("knapsack_big.txt");

    file >> W >> number;

    while (file >> value >> weight) {
        K.push_back(make_pair(value, weight));
    }

    sort(K.begin(), K.end(), [](auto a, auto b){return a.second < b.second;});

    cout << findValue(K, V, number-1, W) << endl;
    
    end = clock();
    auto duration = (double) (end - start) / CLOCKS_PER_SEC;
    
    cout << setprecision(2) << fixed << duration << 's';

    return 0;
}