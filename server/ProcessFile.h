#ifndef PROCESSFILE_H
#define PROCESSFILE_H

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../IO/DefaultIO.h"

using namespace std;

bool unclassifiedVectorsValidation(vector<pair<string, vector<double>>> &, int);
bool databaseValidation(vector<pair<string, vector<double>>> &database);
void readUnclassifiedLineFromFile(string, vector<pair<string, vector<double>>> &);
void readClassifiedLineFromFile(string, vector<pair<string, vector<double>>> &);
void sendFile(string filePath, DefaultIO *io);

#endif