/* Idea of dynamic programming is incorporated. */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main () {
    int number, weight, array[8] = {1, 2, 3, 4, 17, 117, 517, 997};
    vector<int> vW, vR;
    map<int, char> mR;
    ifstream file("mwis.txt");

    file >> number;

    vW.push_back(0);
    vR.push_back(0);

    while (file >> weight) {
        vW.push_back(weight);
    }

    vR.push_back(vW[1]);

    for (auto i = 2; i <= number; i++) {
        vR.push_back(max(vR[i-1], vR[i-2] + vW[i]));
    }

    int j = number;

    mR.insert(make_pair(1, '1'));

    while (j > 1) {
        if (vR[j-2] + vW[j] >= vR[j-1]) {
            mR.insert(make_pair(j, '1'));
            mR.insert(make_pair(j--, '0'));
            mR.insert(make_pair(j--, '0'));
        }
        else mR.insert(make_pair(j--, '0'));
    }

    for (auto i = 0; i < 8; i++) {
        cout << mR[array[i]];
    }
    
    return 0;
}