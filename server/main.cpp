#include "VectorDistances.h"
#include "ProcessFile.h"
#include "Knn.h"
#include "TCPServer.h"
#include "../IO/DefaultIO.h"
#include "../IO/SocketIO.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
#include <stdlib.h>
#include <thread>
#include "CLI.h"
#include "../client/ClientDetails.h"
#include "../commands/UploadData.h"
#include "../commands/AlgorithmSettings.h"
#include "../commands/ClassifyData.h"
#include "../commands/DisplayResults.h"
#include "../commands/DownloadResults.h"

using namespace std;

/**
 * @brief the function receives string input and splits it to three variables 
 * 
 * @param input the string input
 * @param unclassifiedVec the first part of the string is being transfered to a vector (unclassified)
 * @param algorithm the second part of the string is being transfered to a string (algorithm)
 * @param k the third part of the string is being transfered to an int (k neighbors)
 */
void convertInput(string input, vector<double> &unclassifiedVec, string &algorithm, int &k)
{
    stringstream wordStream(input);
    string value;
    double num;

    while (getline(wordStream, value, ' '))
    {
        // insert the string to a stringstream before the conversion to double
        stringstream ss(value);
        // checking if the input is valid, if its not valid we reached the algorithm so we break the loop
        if ((ss >> num) && ss.eof())
        {
            // insert the number to the vector
            unclassifiedVec.push_back(num);
        }
        else
        {
            break;
        }
    }
    // insert the algorithm and K number to the variables and check input validation
    stringstream algorithmStream(value);
    algorithmStream >> algorithm;
    // insert the K number to the variable and check input validation
    if (!(wordStream >> k) || !wordStream.eof())
    {
        // k can't be negative, so if it isn't valid we will change k to -1
        k = -1;
    }
}

void clientProcess(TCPServer* server) {
    DefaultIO *io = new SocketIO(server->getClientSocket());
    ClientDetails *clientDetails = new ClientDetails();
    Command* commands[5];

    commands[0] = new UploadData(io, clientDetails);
    commands[1] = new AlgorithmSettings(io, clientDetails);
    commands[2] = new ClassifyData(io, clientDetails);
    commands[3] = new DisplayResults(io, clientDetails);
    commands[4] = new DownloadResults(io, clientDetails);

    CLI *cli = new CLI(io, commands);
    cli->start();
    server->closeClientSocket();
}

/**
 * @brief the main function of the server, creates a new server capable of receiving vector
 * from the client, find its type following the KNN algorithm and send it back to the client.
 *
 * @return int exit the program
 */
int main(int argc, char **argv)
{
    // argument input check
    if (argc != 2)
    {
        cerr << "invalid server input, the program is closed" << endl;
        return 0;
    }

    // check for port validation
    size_t port;
    stringstream ss(argv[1]);
    if (!(ss >> port) || !ss.eof())
    {
        cerr << "port is not valid, the program is closed" << endl;
        return 0;
    }

    // create new server
    TCPServer *server = new TCPServer(port);

    // create server socket and check for validation
    if (!(server->createSocket()) || !(server->start()))
    {
        return 0;
    }
    
    while(true)
    {
        if(!server->acceptClient())
        {
            continue;
        }
        
        thread thread(clientProcess, server);
        thread.detach();
    }
    // close server socket (if it will be closed)
    server->closeServerSocket();
    delete (server);
    return 0;
}
