
#include "TCPClient.h"

#define BUFFER_SIZE 4096

/**
 * @brief Construct a new TCPClient::TCPClient object
 * 
 * @param serverIP 
 * @param serverPort 
 */
TCPClient::TCPClient(const char *serverIP, const size_t serverPort)
{
    // initiallize the client address struct
    memset(&this->client, 0, sizeof(this->client));
    this->client.sin_family = AF_INET;
    this->client.sin_addr.s_addr = inet_addr(serverIP);
    this->client.sin_port = htons(serverPort);
}

/**
 * @brief the function creates a new socket for the server
 * 
 * @return true if it was created sucessfully
 * @return false else
 */
bool TCPClient::createSocket()
{
    this->serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSock < 0)
    {
        perror("error creating socket");
        close(this->serverSock);
        return false;
    }
    return true;
}

/**
 * @brief the function connect the client to the server
 * 
 * @return true if the connection was successful
 * @return false else
 */
bool TCPClient::connectToServer()
{
    if (connect(this->serverSock, (struct sockaddr *)&this->client, sizeof(this->client)) < 0)
    {
        perror("error connecting to server");
        close(this->serverSock);
        return false;
    }
    return true;
}

/**
 * @brief the function receives data from the server and returns it as a string
 * 
 * @return string 
 */
string TCPClient::receiveFromServer()
{
    // create a buffer and initiallize it
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    int expectedDataLen = sizeof(buffer);
    int readBytes = recv(this->serverSock, buffer, expectedDataLen, 0);
    // connection closed
    if (readBytes == 0)
    {
        perror("connection is closed");
        string temp;
        return temp;
    }
    // error trying to receive
    else if (readBytes < 0)
    {
        perror("error receiving from server");
        string temp;
        return temp;
    }
    // return the vector in a string format
    string str(buffer);
    return str;
}

/**
 * @brief the function closes the server socket
 * 
 */
void TCPClient::closeSocket()
{
    close(this->serverSock);
}

int TCPClient::getSocket() {
    return this->serverSock;
}