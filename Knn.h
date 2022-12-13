#ifndef KNN_H
#define KNN_H
#include <vector>
#include <string>
#include "VectorDistances.h"
#include <algorithm>
#include <map>

using namespace std;

class Knn
{
    public:
        Knn(unsigned int K, vector<double> mainVec, vector<pair<string, vector<double>>> *database);
        string findVectorKind();

    private:
        unsigned int K;
        vector<pair<string, double>> distances;
        vector<double> mainVector;
        vector<pair<string, vector<double>>> *database;
        void convertToDistance(vector<pair<string, double>> &distances);
};

#endif