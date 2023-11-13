/* Typical TSP problem with concept of Hamiltonian Cycle and bitmasking operation to improve time complexity.
   Note to self, vector is way faster than map/hash table in this regard.
   Performance check included.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>
#include <ctime>

using namespace std;

#define axis pair<double, double>
#define C 25
#define T pow(2, C)
#define FINISH (1<<C) - 1

double TSP(int mask, int position, vector<vector<double>> &distance, vector<vector<double>> &visited) {
    double minValue{DBL_MAX}, result;

    if (mask == FINISH) return distance[position][0];
    if (visited[mask][position] != -1) return visited[mask][position];

    for (auto i = 0; i < C; i++) {
        if (!(mask & (1<<i))) {
            result = distance[position][i] + TSP(mask | (1<<i), i, distance, visited);
            minValue = min(minValue, result);
        }
    }

    return visited[mask][position] = minValue;
}

int main() {
    clock_t start, end;
    start = clock();

    int number;
    double x, y;
    vector<axis> city;
    vector<vector<double>> distance(C, vector<double>(C, 0));
    vector<vector<double>> visited(T, vector<double>(C, -1));
    ifstream file("tsp.txt");

    file >> number;

    while (file >> x >> y) {
        city.push_back(axis(x, y));
    }

    for (auto i = 0; i < C; i++) {
        for (auto j = 0; j < C; j++) {
            if (distance[i][j]) continue;
            distance[i][j] = distance[j][i] = sqrt(pow(city[i].first - city[j].first, 2) + pow(city[i].second - city[j].second, 2));
        }
    }

    cout << floor(TSP(1, 0, distance, visited)) << endl;

    end = clock();
    auto duration = (double) (end - start) / CLOCKS_PER_SEC;

    cout << setprecision(2) << fixed << duration << 's';

    return 0;
}