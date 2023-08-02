#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

class TCPServer
{
public:
    TCPServer(const size_t);
    bool createSocket();
    bool start();
    bool acceptClient();
    void closeServerSocket();
    int getClientSocket();
    void closeClientSocket();
    ~TCPServer() = default;

private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in client;
    struct sockaddr_in server;
};

#endif