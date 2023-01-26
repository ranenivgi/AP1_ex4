#include "TCPServer.h"

#define BUFFER_SIZE 4096

/**
 * @brief Construct a new TCPServer::TCPServer object
 *
 * @param serverPort
 */
TCPServer::TCPServer(const size_t serverPort)
{
    // initiallize the server address struct
    memset(&this->server, 0, sizeof(this->server));
    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(serverPort);
}

/**
 * @brief the function creates a new socket for the server
 *
 * @return true if it was created sucessfully
 * @return false else
 */
bool TCPServer::createSocket()
{
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket < 0)
    {
        perror("error creating socket");
        return false;
    }
    return true;
}

/**
 * @brief the function binds the server socket to its struct and listens.
 *
 * @return true if it was sucessfull
 * @return false else
 */
bool TCPServer::start()
{
    if (bind(this->serverSocket, (struct sockaddr *)&this->server, sizeof(this->server)) < 0)
    {
        perror("error binding socket");
        close(this->serverSocket);
        return false;
    }
    // listen up to 5 clients at a time
    if (listen(this->serverSocket, 5) < 0)
    {
        perror("error listening to a socket");
        close(this->serverSocket);
        return false;
    }
    return true;
}

/**
 * @brief the function and accepts clients
 *
 * @return true
 * @return false if there was a problem
 */
bool TCPServer::acceptClient()
{
    // create a new socket for the client trying to connect
    unsigned int addr_len = sizeof(this->client);
    this->clientSocket = accept(this->serverSocket, (struct sockaddr *)&this->client, &addr_len);
    if (this->clientSocket < 0)
    {
        perror("error accepting client");
        close(this->clientSocket);
        return false;
    }

    return true;
}

/**
 * @brief the function closes the server socket
 *
 */
void TCPServer::closeServerSocket()
{
    close(this->serverSocket);
}

/**
 * @brief the function closes the client socket
 *
 */
void TCPServer::closeClientSocket()
{
    close(this->clientSocket);
}

/**
 * @brief getter for client socket
 *
 * @return int
 */
int TCPServer::getClientSocket()
{
    return this->clientSocket;
}
