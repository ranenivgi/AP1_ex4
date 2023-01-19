#include "TCPClient.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
#include <stdlib.h>
#include <vector>

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
    stringstream lineStream(input);
    string value;
    double num;

    while (getline(lineStream, value, ' '))
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
    (algorithmStream >> algorithm);
    // insert the K number to the variable and check input validation
    if (!(lineStream >> k) || !lineStream.eof())
    {
        // k can't be negative, so if it isn't valid we will change k to -1
        k = -1;
    }
}

/**
 * @brief the main function of the program, recives a vector and finds its type following the KNN algorithm.
 *
 * @return int exit the program
 */
int main(int argc, char **argv)
{
    // argument input check
    if (argc != 3)
    {
        cerr << "invalid argument input" << endl;
        return 0;
    }

    // check if the ip is valid
     const char *ip = argv[1], *buffer;
    if(inet_pton(AF_INET, ip, &buffer) != 1)
    {
        cerr << "invalid ip" << endl;
        return 0;
    }

    // check if the port is valid
    size_t port;
    stringstream ss(argv[2]);
    if (!(ss >> port) || !ss.eof() )
    {
        cerr << "invalid port" << endl;
        return 0;
    }

    // create new client
    TCPClient *client = new TCPClient(argv[1], port);

    // create server socket, connect to the server and check for validation
    if(!client->createSocket() || !client->connectToServer())
    {
        return 0;
    }

    string input;

    // the loop gets input from the client, check if it is valid send data to the server, gets data from the server and prints it
    while (true)
    {
        // gets the user input
        getline(cin, input);
        int done;
        stringstream ss(input);
        // if the user insert -1 we finish the loop and exit the program
        if ((ss >> done) && (done == -1))
        {
            break;
        }

        vector<double> vector;
        string algorithm;
        int k;

        // split the input to the vector, algorithm and k number
        convertInput(input, vector, algorithm, k);

        // k number and vector size input validation
        if(k < 1 || !vector.size())
        {
            // the input is not valid so we receive new vector
            cout << "invalid input" << endl;
            continue;
        }

        // if we cant send the data to the server, we finish the loop and exit the program
        if(!client->sendToServer(input)){
            break;
        }

        // receive data from the client
        string output = client->receiveFromServer();
        // if the string is empty we couldn't receive data from the server, so we finish the loop and exit the program
        if(output.empty())
        {
            break;
        }
        cout << output << endl;
    }
    // close server socket
    client->closeSocket();
    delete(client);
    return 0;
}