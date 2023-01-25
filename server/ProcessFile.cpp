#include "ProcessFile.h"

/**
 * @brief this function converts string input to vector using stringstream object.
 *
 * @param str the string
 * @return vector<double> the vector
 */
void strToVec(string line, vector<pair<string, vector<double>>> &unclassifiedVectors)
{
    vector<double> vec;
    double num;
    pair<string, vector<double>> pair;
    // create a string stream from the line
    stringstream line_stream(line);
    string value;

    while (getline(line_stream, value, ','))
    {
        // insert the string to a stringstream before the conversion to double
        stringstream ss(value);
        // checking if the input is valid, if its not valid we break the loop
        if (!ss.eof() && (ss >> num))
        {
            pair.second.push_back(num);
        }
        else
        {
            break;
        }
    }
    unclassifiedVectors.push_back(pair);
}

void readLineFromFile(string line, vector<pair<string, vector<double>>> &database)
{
    stringstream ss;

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
    if (!(temp >> num))
    {
        pair.first = value;
    }
    // insert the pair to the database
    database.push_back(pair);
}

bool databaseValidation(vector<pair<string, vector<double>>> &database)
{
    // check if the file is empty and set the flag accordingly
    if (database.empty())
    {
        return false;
    }

    int vecSize = database[0].second.size();
    int databaseSize = database.size();

    for (int i = 0; i < databaseSize; i++)
    {
        // compare the vectors size from the database and set the flag accordingly
        if (database[i].second.size() != vecSize || database[i].second.size() == 0 || database[i].first.empty())
        {
            return false;
        }
    }
    return true;
}

bool unclassifiedVectorsValidation(vector<pair<string, vector<double>>> &unclassifiedVectors,
                                   int databaseVecSize)
{
    // check if the file is empty and set the flag accordingly
    if (unclassifiedVectors.empty())
    {
        return false;
    }

    int vecSize = unclassifiedVectors[0].second.size();
    int size = unclassifiedVectors.size();

    for (int i = 0; i < size; i++)
    {
        // compare the vectors size from the database and set the flag accordingly
        if (unclassifiedVectors[i].second.size() != vecSize || unclassifiedVectors[i].second.size() == 0 
        || unclassifiedVectors[i].second.size() != databaseVecSize)
        {
            return false;
        }
    }
    return true;
}

void sendFile(string filePath, DefaultIO* io) {
    // open the file and check if it was opened successfully
    ifstream file;
    file.open(filePath);
    if (!file.is_open())
    {
        io->write("end of file");
        return;
    }

    io->write("start of file");
    // read the file line by line
    string line;
    while (getline(file, line))
    {
        io->write(line);
    }
    io->write("end of file");
}