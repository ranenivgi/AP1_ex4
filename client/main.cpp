#include "TCPClient.h"
#include "../IO/DefaultIO.h"
#include "../IO/SocketIO.h"
#include "../IO/StandartIO.h"
#include "../server/ProcessFile.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex.h>
#include <stdlib.h>
#include <vector>
#include <thread>

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

void downloadThread(DefaultIO* io, string input, string message) {
    ofstream outfile;
    outfile.open(input);
    outfile << message;
}

void recieve(DefaultIO *io)
{
    string writeFile = ".txt";
    while (true)
    {
        string input = io->read();
        if (input == "<exit>"){
            break;
        }

        if (input == "connection is closed"){
            exit(1);
        }

        if (equal(writeFile.rbegin(), writeFile.rend(), input.rbegin()))
        {
            ofstream outfile;
            outfile.open(input);
            if (!outfile.is_open())
            {
                cout << "invalid path" << endl;
                io->read();
                continue;
            }
            thread th(downloadThread, io, input, io->read());
            th.detach();
            continue;
        }
        cout << input;
    }
}

void sendMsg(DefaultIO *io)
{
    int exit; 
    string input;
    string readFile = ".csv";
    while (true)
    {
        getline(cin, input);
        stringstream ss(input);
        if (equal(readFile.rbegin(), readFile.rend(), input.rbegin()))
        {
            sendFile(input, io);
            continue;
        }
        
        io->write(input);
        if ((ss >> exit) && exit == 8) {
            break;
        }
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
    if (inet_pton(AF_INET, ip, &buffer) != 1)
    {
        cerr << "invalid ip" << endl;
        return 0;
    }

    // check if the port is valid
    size_t port;
    stringstream ss(argv[2]);
    if (!(ss >> port) || !ss.eof())
    {
        cerr << "invalid port" << endl;
        return 0;
    }

    // create new client
    TCPClient *client = new TCPClient(argv[1], port);

    // create server socket, connect to the server and check for validation
    if (!client->createSocket() || !client->connectToServer())
    {
        return 0;
    }

    DefaultIO *socketIO = new SocketIO(client->getSocket());

    thread thread(recieve, socketIO);
    thread.detach();

    sendMsg(socketIO);

    // close server socket
    client->closeSocket();
    delete (client);
    return 0;
}