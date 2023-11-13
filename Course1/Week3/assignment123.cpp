/* Implementation of quick sort with pivots at front, back, medium and middle. */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Totally irrelevant due to my misunderstanding of the assignment but works like a charm
void quickSortMidPosition(vector<int> &array, int start, int end) {
    int pivot{array[(start+end)/2]}, i{start}, j{end};
 
    while (i <= j) {
        while (array[i] < pivot) i++; 
        while (array[j] > pivot) j--;
        if (i <= j) swap(array[i++], array[j--]);
    };

    if (start < j) quickSortMidPosition(array, start, j);
    if (i < end) quickSortMidPosition(array, i, end);
}

int partition(vector<int> &array, int start, int end, int position, int &comparison) {
    if (position != 0) swap(array[start], array[position]);

    int pivot{array[start]}, j{start + 1};

    for (size_t i = start+1; i <= end; i++) {
        if (array[i] < pivot) swap(array[i], array[j++]);
        comparison++;
    }

    swap(array[start], array[j-1]);

    return j - 1;
}

int findMedium(vector<int> &array, int start, int end) {
    int position{(start+end)/2};

    pair<int, int> minAndMax = minmax({array[start], array[position], array[end]});
    
    if (array[start] != minAndMax.first && array[start] != minAndMax.second) return start;
    else if (array[end] != minAndMax.first && array[end] != minAndMax.second) return end;
    else return position;
}

long quickSort(vector<int> &array, int start, int end, int &comparison) {
    if (start < end) {
        int index = partition(array, start, end, 0, comparison); // front
        // int index = partition(array, start, end, end, comparison); // back
        // int index = partition(array, start, end, findMedium(array, start, end), comparison); // medium
        quickSort(array, start, index-1, comparison);
        quickSort(array, index+1, end, comparison);
    }

    return comparison;
}

int main() {
    int comparison{};
    string data;
    vector<int> v;

    ifstream file("QuickSort.txt");

    while (getline(file, data)) {
        v.push_back(stoi(data));
    }

    cout << quickSort(v, 0, v.size()-1, comparison);
    
    return 0;
}