#include "Knn.h"

    Knn::Knn(unsigned int K, vector<double> mainVec, vector<pair<string, vector<double>>> *database)
    {
        this->K = K;
        this->mainVector = mainVec;
        this->database = database;
        convertToDistance(distances);
    }

    string Knn::findVectorKind()
    {
        // create the map to count the amount of each type
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

        // sort the map so the type shown the most is the first
        long best_score = 0;
        string best_player;

        // Iterate over the elements in the map
        for (std::map<std::string, long>::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            // Update the best player and score if a larger score is found
            if (it->second > best_score) {
            best_player = it->first;
            best_score = it->second;
            }
        }
        return best_player;
    }

    void Knn::convertToDistance(vector<pair<string, double>> &distances)
    {
        // iterate over the database and push pairs of kind and distance to the new distances vector
        for (pair<string, vector<double>> iterator : *this->database)
        {
            distances.push_back(make_pair(iterator.first, minkowskiDistance(this->mainVector, iterator.second)));
        }

        // sort the distances so the closest will be the first
        sort(distances.begin(), distances.end(),
             [](const pair<string, double> &a, const pair<string, double> &b)
             {
                 return a.second < b.second;
             });
    }