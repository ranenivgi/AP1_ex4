#include "VectorDistances.h"
#include "Initialization.h"
#include "Knn.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
#include <stdlib.h>
using namespace std;

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
    while (!ss.eof())
    {
        // checking if the input is valid
        if (!(ss >> num))
        {
            cout << "invalid input" << endl;
            exit(1);
        }
        vec.push_back(num);
    }
    return vec;
}

/**
 * @brief the main function of the program, recives two vectors and prints their distance in each of the 5 given algorithms.
 *
 * @return int exit the program
 */
int main(int argc, char** argv)
{
    //"datasets/iris/iris_classified.csv"
    vector<pair<string, vector<double>>> database = readFromFile(argv[2]);
   
    string str;
    while(true) {
        getline(cin, str);
        vector<double> mainv = strToVec(str);

        //convert char* to unsigned int
        unsigned int k;
        stringstream s(argv[1]);
        s >> k;
        
        Knn *knn = new Knn(k, mainv, &database);
        cout << knn->findVectorKind() << endl;
    }
    
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
