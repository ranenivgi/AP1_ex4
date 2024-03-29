#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

class TCPClient
{
public:
    TCPClient(const char *, const size_t);
    bool createSocket();
    bool connectToServer();
    void closeSocket();
    int getSocket();
    ~TCPClient() = default;

private:
    struct sockaddr_in client;
    int serverSock;
};

#endif