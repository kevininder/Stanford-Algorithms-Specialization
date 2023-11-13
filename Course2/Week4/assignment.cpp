/* Hash table approach mentioned in the lecture takes forever. A niftier algorithm, like this one, is required. */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
    long long number;
    vector<long long> data;
    set<int> result;
    ifstream file("algo1-programming_prob-2sum.txt");

    while (file >> number) {
        data.push_back(number);
    }

    sort(data.begin(), data.end());

    int i{}, j{(int) data.size()-1};

    while (i < j) {
        if (data[i] + data[j] < -10000) i++;
        else if (data[i] + data[j] > 10000) j--;
        else {
            for (auto k = i; k < j; k++) {
                if (data[k] + data[j] > 10000) break;
                if (data[k] != data[j]) result.insert(data[k] + data[j]);
            }
            j--;
        }
    }
    
    cout << result.size();

    return 0;
}