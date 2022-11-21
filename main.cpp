#include "VectorDistances.cpp"
#include <iostream>

using namespace std;
int main() {
    vector<double> v1 = {1,2,3};
    vector<double> v2 = {3,2,1};
    cout.precision(17);
    cout << minkowskiDistance(v1,v2) << endl;
}