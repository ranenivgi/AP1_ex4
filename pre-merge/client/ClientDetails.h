#ifndef CLIENTDETAILS_H
#define CLIENTDETAILS_H

#include <string>
#include <vector>

using namespace std;

class ClientDetails
{
private:
    int k = 5;
    string algorithm = "AUC";
    vector<pair<string, vector<double>>> classifiedVectors;
    vector<pair<string, vector<double>>> unclassifiedVectors;

public:
    ClientDetails() = default;
    vector<pair<string, vector<double>>> &getClassified();
    vector<pair<string, vector<double>>> &getUnclassified();
    void setClassified(vector<pair<string, vector<double>>> classifiedVec);
    void setUnclassified(vector<pair<string, vector<double>>> unclassifiedVec);
    int getK();
    string getAlgorithm();
    void setK(int k);
    void setAlgorithm(string algorithm);
    ~ClientDetails() = default;
};

#endif