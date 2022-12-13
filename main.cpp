#include "VectorDistances.h"
#include "Knn.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
#include <stdlib.h>
using namespace std;

/**
 * @brief printing the distance in the required format (with precision of 1 when the number is floored, and 16 when it is not).
 *
 * @param number the number to print
 */
void printDistance(double number)
{
    fixed(cout);
    floor(number) == number ? cout.precision(1) : cout.precision(16);
    cout << number << endl;
}



/**
 * @brief checking if the string recevied by the user is valid using regex pattern.
 *
 * @param str the sting
 * @return true if the string is valid
 * @return false otherwise
 */
bool isValid(string str)
{
    int status = 0;
    // the required pattern
    const char *pattern = "^[-+]?[0-9]+(\\.[0-9]+)?( [-+]?[0-9]+(\\.[0-9]+)?)*(\n\r|\r\n|\r|\n)?$";

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        return false;
    }
    status = regexec(&regex, str.c_str(), (size_t)0, NULL, 0);
    regfree(&regex);
    if (status)
    {
        return false;
    }
    return true;
}

/**
 * @brief the main function of the program, recives two vectors and prints their distance in each of the 5 given algorithms.
 *
 * @return int exit the program
 */
int main()
{
    vector<pair<string, vector<double>>> database;
    vector<double> v1 = {5.9,3.0,5.1,1.8};
    database.push_back(make_pair("Iris-virginica", v1));
    vector<double> v2 = {6.4,2.8,5.6,2.1};
    database.push_back(make_pair("Iris-virginica", v2));
    vector<double> v3 = {7.4,2.8,6.1,1.9};
    database.push_back(make_pair("Iris-versicolor", v3));
    vector<double> v4 = {5.7,2.6,3.5,1.0};
    database.push_back(make_pair("Iris-versicolor", v4));
    vector<double> mainv = {7.7,3.0,6.1,2.3};
    Knn *k = new Knn(4,mainv,&database);
    cout << k->findVectorKind() << endl;

    // string strVec1, strVec2;
    // cout << "please enter the vectors:" << endl;
    // getline(cin, strVec1) && getline(cin, strVec2);
    // vector<double> v1 = strToVec(strVec1), v2 = strToVec(strVec2);
    
    // // checking if the input is valid
    // if ((isValid(strVec1) && isValid(strVec2)) && (v1.size() == v2.size()) && v1.size())
    // {
    //     // print the distances between two vectors by the algorithms
    //     printDistance(euclideanDistance(v1, v2));
    //     printDistance(manhattanDistance(v1, v2));
    //     printDistance(chebyshevDistance(v1, v2));
    //     printDistance(canberraDistance(v1, v2));
    //     printDistance(minkowskiDistance(v1, v2));
    // }
    // else
    // {
    //     cout << "invalid input" << endl;
    //     exit(1);
    // }
}
