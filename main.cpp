#include "VectorDistances.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>

using namespace std;

/**
 * @brief printing the distance in the required format (with precision of 1 when the number is floored, and 17 when it is not).
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
 * @brief this function converts string input to vector using stringstream object.
 *
 * @param str the string
 * @return vector<double> the vector
 */
vector<double> strToVec(string str)
{
    vector<double> vec;
    double num;
    stringstream ss;

    // insert the string to the ss
    ss << str;

    // insert the numbers to the vector (split by spaces)
    while (true)
    {
        ss >> num;
        if (!ss)
            break;
        vec.push_back(num);
    }
    return vec;
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
    const char *pattern = "^-?[0-9]+(\\.[0-9]+)?( -?[0-9]+(\\.[0-9]+)?)*(\n\r|\r\n|\r|\n)?$";

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
    string strVec1, strVec2;
    cout << "enter the vectors:" << endl;
    getline(cin, strVec1) && getline(cin, strVec2);
    vector<double> v1 = strToVec(strVec1), v2 = strToVec(strVec2);

    // receive input from the user until it is correct
    while (true)
    {
        if ((isValid(strVec1) && isValid(strVec2)) && (v1.size() == v2.size()) && v1.size() && v2.size())
        {
            break;
        }
        cout << "problem, try again:" << endl;
        getline(cin, strVec1) && getline(cin, strVec2);
        v1 = strToVec(strVec1);
        v2 = strToVec(strVec2);
    }

    // print the distances between two vectors by the algorithms
    printDistance(euclideanDistance(v1, v2));
    printDistance(manhattanDistance(v1, v2));
    printDistance(chebyshevDistance(v1, v2));
    printDistance(canberraDistance(v1, v2));
    printDistance(minkowskiDistance(v1, v2, 2));
}