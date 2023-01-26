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
 * @brief creates new data for a new client and run its process
 *
 * @param server
 */
void clientProcess(TCPServer *server)
{
    DefaultIO *io = new SocketIO(server->getClientSocket());
    ClientDetails *clientDetails = new ClientDetails();
    Command *commands[5];

    commands[0] = new UploadData(io, clientDetails);
    commands[1] = new AlgorithmSettings(io, clientDetails);
    commands[2] = new ClassifyData(io, clientDetails);
    commands[3] = new DisplayResults(io, clientDetails);
    commands[4] = new DownloadResults(io, clientDetails);

    CLI *cli = new CLI(io, commands);

    // start the process
    cli->start();
    // close the socket when the process is over
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

    while (true)
    {
        // accept new client
        if (!server->acceptClient())
        {
            continue;
        }

        // activate the client process while accepting new client (thread)
        thread thread(clientProcess, server);
        thread.detach();
    }
    // close server socket (if it will be closed)
    server->closeServerSocket();
    return 0;
}
