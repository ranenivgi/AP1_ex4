#include "VectorDistances.cpp"
#include <iostream>

using namespace std;

/**
 * @brief printing the distance in the required format (with precision of 1 when the number is floored, and 17 when it is not).
 *
 * @param number the number to print
 */
void printDistance(double number)
{
    fixed(cout);
    floor(number) == number ? cout.precision(1) : cout.precision(17);
    cout << number << endl;
}

/**
 * @brief the main function of the program, recives two vectors and prints their distance in each of the 5 given algorithms.
 *
 * @return int
 */
int main()
{
    vector<double> v1 = {1, 2, 3};
    vector<double> v2 = {3, 2, 1};

    printDistance(euclideanDistance(v1, v2));
    printDistance(manhattanDistance(v1, v2));
    printDistance(chebyshevDistance(v1, v2));
    printDistance(canberraDistance(v1, v2));
    printDistance(minkowskiDistance(v1, v2));
}