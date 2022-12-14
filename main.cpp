#include "VectorDistances.h"
#include "ProcessFile.h"
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
            cerr << "invalid input" << endl;
            exit(1);
        }
        vec.push_back(num);
    }
    return vec;
}

/**
 * @brief the main function of the program, recives a vector and finds its type following the KNN algorithm.
 *
 * @return int exit the program
 */
int main(int argc, char **argv)
{
    // argument input check
    if (argc != 4)
    {
        cerr << "Invalid argument input" << endl;
        exit(1);
    }

    // read the data from the file and insert it to a database
    vector<pair<string, vector<double>>> database = readFromFile(argv[2]);

    // convert the K number to unsigned int and check validation
    int k;
    stringstream ss(argv[1]);
    if (!(ss >> k) || k < 1 || k > database.size())
    {
        cerr << "K number error" << endl;
        exit(1);
    }

    string input;
    while (true)
    {
        // get the input from the user and converts it to a vector and check its validation
        getline(cin, input);
        vector<double> unclassifiedVec = strToVec(input);
        if (!isValid(input) || !unclassifiedVec.size() || unclassifiedVec.size() != database[0].second.size())
        {
            cerr << "invalid vector input" << endl;
            exit(1);
        }

        // create Knn object to find the input type
        Knn *knn = new Knn(k, unclassifiedVec, &database, argv[3]);
        cout << knn->findVectorType() << endl;
    }
}