/* Implementation of heap/priority queue. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    int sum{}, mod{10000};
    string data;
    priority_queue<int, vector<int>, greater<>> minHeap; // Intrinsically sorted, more convenient than make_heap
    priority_queue<int> maxHeap;
    minHeap.push(INT_MAX);
    maxHeap.push(INT_MIN);
    ifstream file("Median.txt");

    while (getline(file, data)) {
        int number;
        istringstream iss(data);

        iss >> number;

        if (minHeap.size() > maxHeap.size()) {
            if (number > minHeap.top()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(number);
            }
            else maxHeap.push(number);
            sum = (sum + maxHeap.top()) % mod;
        }
        else if (minHeap.size() < maxHeap.size()) {
            if (number < maxHeap.top()) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                maxHeap.push(number);
            }
            else minHeap.push(number);
            sum = (sum + maxHeap.top()) % mod;
        }
        else {
            if (number > minHeap.top()) {
                minHeap.push(number);
                sum = (sum + minHeap.top()) % mod;
            }
            else {
                maxHeap.push(number);
                sum = (sum + maxHeap.top()) % mod;
            }
        }
    }
    
    cout << sum;

    return 0;
}