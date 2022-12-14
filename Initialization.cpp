#include "Initialization.h"

vector<pair<string, vector<double>>> readFromFile(string filePath) {
    vector<pair<string, vector<double>>> database;
    stringstream ss;

    // Open the file for reading.
    ifstream file(filePath);

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
            if ((ss >> num) && ss.eof())
            {
                temp.second.push_back(num);
            } else {
                break;
            }
        }
        //cout << value << endl;
        temp.first = value;
        database.push_back(temp);
    }
    databaseValidation(database);
    return database;
}

void databaseValidation (vector<pair<string, vector<double>>>& database) {
    if (database.empty()) {
        cout << "table is empty" << endl;
        exit(1);
    }
    int vecSize = database[0].second.size();
    int databaseSize = database.size();
    
    for(int i = 0; i < databaseSize; i++){
        if(database[i].second.size() != vecSize || database[i].second.size() == 0){
            cout << "invalid table" << endl;
            exit(1);
        }
    } 
}