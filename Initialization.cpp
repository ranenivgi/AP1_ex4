#include "Initialization.h"

vector<pair<string, vector<double>>> readFromFile(string filePath) {
    vector<pair<string, vector<double>>> database;
    stringstream ss;

    // Open the file for reading.
    ifstream file("datasets/iris/iris_classified.csv");

    // Check if the file was opened successfully.
    if (!file.is_open()) {
        cerr << "Could not open file!" << endl;
        exit(1);
    }

    // Read the file line by line.
    string line;
    while (getline(file, line)) {
        // Create a string stream from the line.
        stringstream line_stream(line);
        string value;
        double num;
        pair<string, vector<double>> temp;
        // Use the string stream to read the values from the line,
        // separated by commas.
        while (getline(line_stream, value, ',')) {
            // insert the string to a stringstream before the conversion to double
            stringstream ss(value);
            // checking if the input is valid, if its not valid we break the loop
            if (!(ss >> num))
            {
                break;
            } else {
                temp.second.push_back(num);
            }
            // Print the value to the console.
            cout << value << " ";
        }
        temp.first = value;
        database.push_back(temp);
        cout << endl;
    }
    return database;
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
