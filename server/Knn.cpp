#include "Knn.h"

/**
 * @brief Construct a new Knn:: Knn object
 *
 * @param K the neighbors amount
 * @param unclassifiedVec the input vector from the user
 * @param database the database
 * @param algorithm the chosen algorithm
 */
Knn::Knn(unsigned int K, vector<double> unclassifiedVec, vector<pair<string, vector<double>>> *database,
         string algorithm)
{
    this->K = K;
    this->unclassifiedVec = unclassifiedVec;
    this->database = database;
    this->algorithm = algorithm;
    // calculate the distance between the vectors from the database and the unclassified vector
    convertToDistance(distances);
}

/**
 * @brief calculates the distance beween each vector from the database and the input vector,
 * and inserts it to the distances vector as a pair consists of type and distance.
 * Then, it sorts the distances vector by the distance from the input vector.
 *
 * @param distances the distances vector
 */
void Knn::convertToDistance(vector<pair<string, double>> &distances)
{
    // iterate over the database and push "type" and "distance" pairs to the distances vector
    for (pair<string, vector<double>> iterator : *this->database)
    {
        distances.push_back(make_pair(iterator.first, selectAlgorithm(this->algorithm, this->unclassifiedVec,
                                                                      iterator.second)));
    }

    // sort the distances so the closest to the unclassified vector will be the first
    sort(distances.begin(), distances.end(),
         [](const pair<string, double> &a, const pair<string, double> &b)
         {
             return a.second < b.second;
         });
}

/**
 * @brief the function iterates over the closest K neighbors and inserts each to a map consists of
 * the type (key) and the amount of time it appears (value).
 * Then, it finds the most common type in the map.
 *
 * @return string the most common type
 */
string Knn::findVectorType()
{
    // create the map to count the appearance of each type
    map<string, long> neighbors;
    for (int i = 0; i < this->K; i++)
    {
        if (neighbors.count(this->distances.at(i).first) > 0)
        {
            neighbors[distances.at(i).first] += 1;
        }
        else
        {
            neighbors[distances.at(i).first] = 1;
        }
    }

    // find the map most common type
    long maxNumber = 0;
    string mostCommonType;

    for (map<string, long>::iterator iterator = neighbors.begin(); iterator != neighbors.end(); ++iterator)
    {
        // update the most common type (and the max number) if we found a greater one
        if (iterator->second > maxNumber)
        {
            mostCommonType = iterator->first;
            maxNumber = iterator->second;
        }
    }
    return mostCommonType;
}