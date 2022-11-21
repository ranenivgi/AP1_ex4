#ifndef EX1_DISTANCEVECTOR_H
#define EX1_DISTANCEVECTOR_H
#include <vector>
#include <math.h>

using namespace std;

double minkowskiDistance(vector<double>, vector<double>, const int);
double euclideanDistance(vector<double>, vector<double>);
double manhattanDistance(vector<double>, vector<double>);
double chebyshevDistance(vector<double>, vector<double>);
double canberraDistance(vector<double>, vector<double>);

#endif