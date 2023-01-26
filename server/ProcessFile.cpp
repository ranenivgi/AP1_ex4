#include "ProcessFile.h"

/**
 * @brief this function recieves a line from unclassified csv file and converts it to a vector.
 *
 * @param line the line
 * @param database the database
 */
void readUnclassifiedLineFromFile(string line, vector<pair<string, vector<double>>> &database)
{
    vector<double> vec;
    double num;
    // we insert each line from the table to a pair
    pair<string, vector<double>> pair;
    
    if (line.back() == '\r' || line.back() == '\n') {
        //remove the end of line carriage char from the end of the line
        line.erase(line.end() - 1, line.end());
    }

    // create a string stream from the line
    stringstream line_stream(line);
    string value;

    // use the string stream to read the values from the line, seperated by commas
    while (getline(line_stream, value, ','))
    {
        // insert the string to a stringstream before the conversion to double
        stringstream ss(value);
        // checking if the input is valid and push to the vector, if its not valid we break the loop
        if ((ss >> num) && ss.eof())
        {
            pair.second.push_back(num);
        }
        else
        {
            if(!ss.eof()){
                pair.first = value;
            }
            break;
        }
    }
    database.push_back(pair);
}

/**
 * @brief this function recieves a line from classified csv file and converts it to database.
 *
 * @param line the line
 * @param database the database
 */
void readClassifiedLineFromFile(string line, vector<pair<string, vector<double>>> &database)
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
        // checking if the input is valid and push to the, if its not valid we reached the type so we break the loop
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

/**
 * @brief the function checks if the classified database created is valid (not empty, same vector size etc).
 *
 * @param database
 */
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

/**
 * @brief the function checks if the unclassified database created is valid (not empty, same vector size etc).
 *
 * @param database
 */
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
        || unclassifiedVectors[i].second.size() != databaseVecSize || !unclassifiedVectors[i].first.empty())
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief the function opens a csv file and send line after line to the server
 *
 * @param filePath
 * @param io
 */
void sendFile(string filePath, DefaultIO *io)
{
    // open the file and check if it was opened successfully
    ifstream file;
    file.open(filePath);
    if (!file.is_open())
    {
        // mark the end of the file
        io->write("end of file");
        return;
    }

    // mark the begining of a file
    io->write("start of file");
    // read the file line by line and send to the server
    string line;
    while (getline(file, line))
    {
        io->write(line);
    }
    // mark the end of the file
    io->write("end of file");
}