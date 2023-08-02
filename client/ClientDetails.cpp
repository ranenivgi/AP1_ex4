#include "ClientDetails.h"

/**
 * @brief getter for classified database
 *
 * @return vector<pair<string, vector<double>>>&
 */
vector<pair<string, vector<double>>> &ClientDetails::getClassified()
{
    return this->classifiedVectors;
}

/**
 * @brief getter for unclassified database
 *
 * @return vector<pair<string, vector<double>>>&
 */
vector<pair<string, vector<double>>> &ClientDetails::getUnclassified()
{
    return this->unclassifiedVectors;
}

/**
 * @brief getter for K neighbors
 *
 * @return int
 */
int ClientDetails::getK()
{
    return this->k;
}

/**
 * @brief getter for the algorithm
 *
 * @return string
 */
string ClientDetails::getAlgorithm()
{
    return this->algorithm;
}

/**
 * @brief setter for classified database
 *
 * @param classifiedVec
 */
void ClientDetails::setClassified(vector<pair<string, vector<double>>> classifiedVec)
{
    this->classifiedVectors = classifiedVec;
}

/**
 * @brief setter for unclassified database
 *
 * @param unclassifiedVec
 */
void ClientDetails::setUnclassified(vector<pair<string, vector<double>>> unclassifiedVec)
{
    this->unclassifiedVectors = unclassifiedVec;
}

/**
 * @brief setter for k number
 *
 * @param k
 */
void ClientDetails::setK(int k)
{
    this->k = k;
}

/**
 * @brief setter for algorithm
 *
 * @param algorithm
 */
void ClientDetails::setAlgorithm(string algorithm)
{
    this->algorithm = algorithm;
}