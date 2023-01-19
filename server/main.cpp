#include "VectorDistances.h"
#include "ProcessFile.h"
#include "Knn.h"
#include "TCPServer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
#include <stdlib.h>

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

/**
 * @brief the main function of the server, creates a new server capable of receiving vector
 * from the client, find its type following the KNN algorithm and send it back to the client.
 *
 * @return int exit the program
 */
int main(int argc, char **argv)
{
    // argument input check
    if (argc != 3)
    {
        cerr << "invalid server input, the program is closed" << endl;
        return 0;
    }

    // read the data from the file, insert it to a database and check for validation
    vector<pair<string, vector<double>>> database = readFromFile(argv[1]);
    if (database.empty())
    {
        cerr << "database is not valid, the program is closed" << endl;
        return 0;
    }

    // check for port validation
    size_t port;
    stringstream ss(argv[2]);
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

    // loop responsible of accepting clients
    while (server->acceptClient())
    {
        //loop responsible of receiving data from the user, process it and send it back
        while (true)
        {
            int k;
            vector<double> unclassifiedVec;
            string algorithm;
            
            // receive data from the client
            string clientInput = server->receiveFromClient();
            // if the string is empty the connection is closed, we move to the next client
            if (clientInput.empty())
            {
                break;
            }
            
            // split the input to the vector, algorithm and k number
            convertInput(clientInput, unclassifiedVec, algorithm, k);

            // k number, vector size and algorithm input validation
            if ((k < 1 || !unclassifiedVec.size() || unclassifiedVec.size() != database[0].second.size()) 
                || (k > database.size()) || (selectAlgorithm(algorithm) == -1))
            {
                // if we cant send the data for the user, we move to the next client
                if (!server->sendToClient("invalid input"))
                {
                    break;
                }
                // else the input is not valid so we receive new vector
                continue;
            }

            // create Knn object to find the input type
            Knn *knn = new Knn(k, unclassifiedVec, &database, algorithm);

            // send the classified vector to the user and check for validation
            if (!server->sendToClient(knn->findVectorType()))
            {
                // if it wasn't sent sucessfully we move to the next client
                break;
            }
            delete (knn);
        }
    }
    // close server socket (if it will be closed)
    server->closeServerSocket();
    delete (server);
    return 0;
}
