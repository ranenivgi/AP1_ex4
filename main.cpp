#include "VectorDistances.cpp"
#include <iostream>
#include <cstring>
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

vector<double> strToVec(string str)
{
    vector<double> vec;
    double num;
    stringstream ss;
    ss << str;

    while (true)
    {
        ss >> num;
        if (!ss)
            break;
        vec.push_back(num);
    }
    return vec;
    
}

bool isVaild(string str)
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
 * @return int
 */

int main()
{
    string strVec1, strVec2;
    cout << "enter the vectors:" << endl;
    getline(cin, strVec1) && getline(cin, strVec2);
    vector<double> v1 = strToVec(strVec1), v2 = strToVec(strVec2);
    
    while (true)
    {
        if((isVaild(strVec1) && isVaild(strVec2)) && (v1.size() == v2.size()) && v1.size() && v2.size()) {
            break;
        }
        cout << "problem, try again:" << endl;
        getline(cin, strVec1) && getline(cin, strVec2);
        v1 = strToVec(strVec1);
        v2 = strToVec(strVec2);
    }
    
    printDistance(euclideanDistance(v1, v2));
    printDistance(manhattanDistance(v1, v2));
    printDistance(chebyshevDistance(v1, v2));
    printDistance(canberraDistance(v1, v2));
    printDistance(minkowskiDistance(v1, v2, 2));
}