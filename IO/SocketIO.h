#ifndef SOCKETIO_H
#define SOCKETIO_H

#include <string.h>
#include <iostream>
#include "../commands/Command.h"
#include "DefaultIO.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class SocketIO : public DefaultIO
{

private:
    int socket;
public:
    SocketIO(int socket);
    string read() override;
    void write(string data) override;
    ~SocketIO() = default;
};

#endif