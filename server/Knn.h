#ifndef KNN_H
#define KNN_H

#include <vector>
#include <string>
#include "VectorDistances.h"
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

class Knn
{
public:
    Knn(unsigned int K, vector<double> mainVec, vector<pair<string, vector<double>>> *database, string algorithm);
    string findVectorType();
    ~Knn() = default;

private:
    unsigned int K;
    vector<pair<string, double>> distances;
    vector<double> unclassifiedVec;
    vector<pair<string, vector<double>>> *database;
    string algorithm;
    void convertToDistance(vector<pair<string, double>> &distances);
};

#endif