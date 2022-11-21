#include "VectorDistances.h"

double minkowskiDistance(vector<double> vec1, vector<double> vec2, const int p = 2)
{
    double sum=0;
    for (int i = 0; i < vec1.size(); i++) {
        sum += pow(abs(vec1[i]-vec2[i]), p);
    }
    return pow(sum, (double) 1 / p);
}

double euclideanDistance(vector<double> vec1, vector<double> vec2)
{
    return minkowskiDistance(vec1, vec2, 2);
}

double manhattanDistance(vector<double> vec1, vector<double> vec2)
{
    return 0;
}

double chebyshevDistance(vector<double> vec1, vector<double> vec2)
{
    return 0;
}

double canberraDistance(vector<double> vec1, vector<double> vec2)
{
    return 0;
}