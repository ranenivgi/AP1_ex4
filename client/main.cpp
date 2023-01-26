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
#include <chrono>

#define EXIT 8
bool stop = false;



using namespace std;

/**
 * @brief the function is used by a thread and its purpose is to write the results to a file
 *
 * @param io the IO written to
 * @param filePath the file path
 * @param results
 */
void writeToFile(DefaultIO *io, string filePath, string results)
{
    ofstream outfile;
    outfile.open(filePath);
    outfile << results;
}

/**
 * @brief checks if an input is a txt file which should be written to, and creates a thread to do it.
 *
 * @param io the IO
 * @param input the input (filepath)
 * @return true if it was written sucessfully
 * @return false otherwise
 */
bool isTXTFile(DefaultIO *io, string input)
{
    // the .txt format
    string writeFile = ".txt";

    // checks if the input ends with .txt
    if (equal(writeFile.rbegin(), writeFile.rend(), input.rbegin()))
    {
        // create new file
        ofstream outfile;
        outfile.open(input);
        if (!outfile.is_open())
        {
            cout << "invalid path" << endl;
            io->read();
            return true;
        }

        // write to the file
        thread th(writeToFile, io, input, io->read());
        th.detach();
        return true;
    }
    return false;
}

/**
 * @brief the function recieves input from the server until it gets the input "<exit>"
 *
 * @param io
 */
void recieveFromServer(DefaultIO *io)
{
    while (true)
    {
        try
        {
            // read an input from the server
            string input = io->read();

            // check if we should stop
            if (input == "<exit>")
            {
                stop = true;
                break;
            }

            // check if the input is a txt file which should be written to and does it
            if (isTXTFile(io, input))
            {
                continue;
            }
            // print the input
            cout << input;
        }
        catch (...)
        {
            cout << "server connection is closed" << endl;
            exit(0);
        }
    }
}

/**
 * @brief check if an input is a csv file, if so it sends it to the server as a file.
 *
 * @param io
 * @param input
 * @return true
 * @return false
 */
bool isCSVFile(DefaultIO *io, string input)
{
    // the csv format
    string readFile = ".csv";
    // check if the input ends with the .csv format
    if (equal(readFile.rbegin(), readFile.rend(), input.rbegin()))
    {
        // send it to the server line by line
        sendFile(input, io);
        return true;
    }
    return false;
}

/**
 * @brief the function recieves input from the user and sends it to the server until it gets the input "8"
 *
 * @param io the IO
 */
void sendToServer(DefaultIO *io)
{
    int exit;
    string input;
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(35));
        // check if the function should be stopped
        if (stop)
        {
            break;
        }
        // get input from the user
        getline(cin, input);
        stringstream ss(input);

        // check if the input is a CSV file which should be uploaded to the server
        if (isCSVFile(io, input))
        {
            continue;
        }

        // send the input to the server
        io->write(input); 
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

    // create new socket IO
    DefaultIO *socketIO = new SocketIO(client->getSocket());

    // create a thread for recieving messages
    thread thread(recieveFromServer, socketIO);
    thread.detach();

    // the main thread will send messages to the server
    sendToServer(socketIO);

    // close server socket
    client->closeSocket();
    return 0;
}