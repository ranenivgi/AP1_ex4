#include "ProcessFile.h"

/**
 * @brief the fucntion reads file and inserts it to a database designed as vector of pairs,
 * the first element of the pair is the type and the second is vector of properties represented as double.
 * 
 * @param filePath the file path
 * @return vector<pair<string, vector<double>>> the database
 */
vector<pair<string, vector<double>>> readFromFile(string filePath)
{
    vector<pair<string, vector<double>>> database;
    stringstream ss;

    // open the file and check if it was opened successfully
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "could not open file" << endl;
        exit(1);
    }

    // read the file line by line
    string line;
    while (getline(file, line))
    {
        // create a string stream from the line
        stringstream line_stream(line);
        string value;

        // we insert each line from the table to a pair (first element is the type, and the second is its properties)
        pair<string, vector<double>> pair;
        double num;

        // use the string stream to read the values from the line, seperated by commas
        while (getline(line_stream, value, ','))
        {
            // insert the string to a stringstream before the conversion to double
            stringstream ss(value);
            // checking if the input is valid, if its not valid we reached the type so we break the loop
            if ((ss >> num) && ss.eof())
            {
                // insert the number to the vector in the second element
                pair.second.push_back(num);
            }
            else
            {
                break;
            }
        }
        // insert the type to the first element
        pair.first = value;
        // insert the pair to the database
        database.push_back(pair);
    }
    // database validation
    databaseValidation(database);
    return database;
}

/**
 * @brief the function checks if the database created is valid (not empty, same vector size etc).
 * 
 * @param database 
 */
void databaseValidation(vector<pair<string, vector<double>>> &database)
{
    // check if the table is empty
    if (database.empty())
    {
        cerr << "table is empty" << endl;
        exit(1);
    }

    int vecSize = database[0].second.size();
    int databaseSize = database.size();

    for (int i = 0; i < databaseSize; i++)
    {
        // compare the vectors size from the database
        if (database[i].second.size() != vecSize || database[i].second.size() == 0)
        {
            cerr << "invalid table" << endl;
            exit(1);
        }
    }
}