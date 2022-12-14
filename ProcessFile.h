#ifndef PROCESSFILE_H
#define PROCESSFILE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<pair<string, vector<double>>> readFromFile(string);
void databaseValidation (vector<pair<string, vector<double>>>&);

#endif