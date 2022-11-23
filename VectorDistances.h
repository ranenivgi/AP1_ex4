#ifndef VECTOR_DISTANCES_H
#define VECTOR_DISTANCES_H
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;

double minkowskiDistance(vector<double>, vector<double>, const int = 2);
double euclideanDistance(vector<double>, vector<double>);
double manhattanDistance(vector<double>, vector<double>);
double chebyshevDistance(vector<double>, vector<double>);
double canberraDistance(vector<double>, vector<double>);

#endif