/* Idea of greedy algorithm is incorporated. */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Job {
    public:
        double weight, length;

        Job() = default;
        virtual ~Job(){}
};

bool sortVector(Job a, Job b) {
    if (a.weight - a.length == b.weight - b.length
    && a.weight > b.weight) return true;

    return a.weight - a.length > b.weight - b.length;
}

long weightedSum(vector<Job> &vJob) {
    long temp{}, sum{};

    for (auto i = 0; i < vJob.size(); i++) {
        temp += vJob[i].length;
        sum += vJob[i].weight * temp;
    }
    
    return sum;
}

int main() {
    double weight, length;
    string data;
    Job job;
    vector<Job> vJob;
    ifstream file("jobs.txt");

    file >> data;

    while (file >> weight >> length) {
        job.weight = weight;
        job.length = length;
        vJob.push_back(job);
    }
    
    sort(vJob.begin(), vJob.end(), sortVector);
    cout << weightedSum(vJob) << endl;

    sort(vJob.begin(), vJob.end(), [](Job a, Job b){return a.weight / a.length > b.weight / b.length;});
    cout << weightedSum(vJob) << endl;

    return 0;
}