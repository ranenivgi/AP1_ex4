#include "ClientDetails.h"

vector<pair<string, vector<double>>>& ClientDetails::getClassified() {
    return this->classifiedVectors;
}

vector<pair<string, vector<double>>>& ClientDetails::getUnclassified() {
    return this->unclassifiedVectors;
}

int ClientDetails::getK() {
    return this->k;
}

string ClientDetails::getAlgorithm() {
    return this->algorithm;
}

//check if used
void ClientDetails::setClassified(vector<pair<string, vector<double>>> classifiedVec) {
    this->classifiedVectors = classifiedVec;
}

//check if used
void ClientDetails::setUnclassified(vector<pair<string, vector<double>>> unclassifiedVec) {
    this->unclassifiedVectors = unclassifiedVec;
}

void ClientDetails::setK(int k) {
    this->k = k;
}

void ClientDetails::setAlgorithm(string algorithm) {
    this->algorithm = algorithm;
}