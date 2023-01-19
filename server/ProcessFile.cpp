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
        // return empty database (the caller function will stop the program)
        return database;
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
        stringstream temp(value);

        // if there isnt first element in the line we leave it empty (it wont be valid in the validation function)
        if (!(temp >> num)) {
            pair.first = value;
        }
        // insert the pair to the database
        database.push_back(pair);
    }
    // database validation
    int flag = 0;
    databaseValidation(database, flag);
    // if the flag equals 1, the database is not vaild so we send empty database for the caller function
    if (flag) {
        vector<pair<string, vector<double>>> emptyDatabase;
        return emptyDatabase;
    }

    return database;
}

/**
 * @brief the function checks if the database created is valid (not empty, same vector size etc).
 * 
 * @param database 
 */
void databaseValidation(vector<pair<string, vector<double>>> &database, int& flag)
{
    // check if the file is empty and set the flag accordingly
    if (database.empty())
    {
        flag = 1;
        return;
    }

    int vecSize = database[0].second.size();
    int databaseSize = database.size();

    for (int i = 0; i < databaseSize; i++)
    {
        // compare the vectors size from the database and set the flag accordingly
        if (database[i].second.size() != vecSize || database[i].second.size() == 0 || database[i].first.empty())
        {
            flag = 1;
            return;
        }
    }
}