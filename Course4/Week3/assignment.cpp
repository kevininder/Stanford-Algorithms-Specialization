/* TSP with nearest neighbour heuristic. */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <float.h>

using namespace std;

#define axis pair<double, double>

int main() {
    int number, index, src{}, dest;
    double x, y, result{}, distance;
    vector<axis> city;
    ifstream file("nn.txt");

    file >> number;

    vector<bool> visited(number, false);
    visited[0] = true;

    while (file >> index >> x >> y) {
        city.push_back(axis(x, y));
    }

    int count{number-1};
    
    while (count--) {
        double minValue{DBL_MAX};

        for (auto i = 1; i < number; i++) {
            if (visited[i]) continue;
            distance = sqrt(pow(city[src].first - city[i].first, 2) + pow(city[src].second - city[i].second, 2));
            if (distance < minValue) {
                minValue = distance;
                dest = i;
            }
        }
        
        visited[dest] = true;
        src = dest;
        result += minValue;
    }
    
    cout << (int) round(result + sqrt(pow(city[src].first - city[0].first, 2) + pow(city[src].second - city[0].second, 2)));
    
    return 0;
}