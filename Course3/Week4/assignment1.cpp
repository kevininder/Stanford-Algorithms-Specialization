/* Knapsack problem with idea of dynamic programming. */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int W, number, value, weight;
    vector<pair<int, int>> K;
    ifstream file("knapsack.txt");

    file >> W >> number;

    vector<vector<int>> R(number+1, vector<int>(W+1, 0));

    while (file >> value >> weight) {
        K.push_back(make_pair(value, weight));
    }

    for (auto i = 1; i <= number; i++) {
        for (auto j = 1; j <= W; j++) {
            if (j < K[i-1].second) R[i][j] = R[i-1][j];
            else R[i][j] = max(R[i-1][j], R[i-1][j-K[i-1].second] + K[i-1].first);
        }
    }
    
    cout << R[number][W];
        
    return 0;
}