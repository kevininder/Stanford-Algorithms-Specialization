/* Implementation of merge sort. */

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void merge(vector<int> &array, int left, int mid, int right, long &inversion) {
    int i{left}, j{mid + 1}, k{};
    int *temp{new int[right-left+1]};

    while (i <= mid && j <= right) {
        array[i] <= array[j] ? temp[k++] = array[i++] : (temp[k++] = array[j++], inversion += mid - i + 1);
    }

    while (i <= mid) temp[k++] = array[i++];
    while (j <= right) temp[k++] = array[j++];
    
    for (auto i = left; i <= right; i++) {
        array[i] = temp[i-left];
    }
    
    delete[] temp;
    temp = nullptr;
}

long mergeSort(vector<int> &array, int left, int right, long &inversion) {
    int mid = (left + right) / 2;
    
    if (left < right) {
        mergeSort(array, left, mid, inversion);
        mergeSort(array, mid + 1, right, inversion);
        merge(array, left, mid, right, inversion);
    }

    return inversion;
}

int main() {
    long inversion{};
    string data;
    vector<int> v;

    ifstream file("IntegerArray.txt");

    while (getline(file, data)) {
        v.push_back(stoi(data));
    }

    cout << mergeSort(v, 0, v.size() - 1, inversion);
    
    return 0;
}