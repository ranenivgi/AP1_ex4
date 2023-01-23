#include "SocketIO.h"

SocketIO::SocketIO(int socket) {
    this->socket = socket;
}

void SocketIO::write(string data) {
    // send the message to the client and check if it was sent sucessfully
    int sentBytes = send(this->socket, data.c_str(), strlen(data.c_str()), 0);
    if (sentBytes < 0)
    {
        perror("error writing");
        //return false;
    }
    //return true;
}

string SocketIO::read() {
    // create a buffer and initiallize it
    char buffer[1];
    string line;
    do
    {
        memset(buffer, 0, 1);
        int readBytes = recv(this->socket, buffer, 1, 0);
        // connection closed
        if (readBytes == 0)
        {
            perror("connection is closed");
            close(this->socket);
            string temp;
            return temp;
        }
        // error trying to receive
        else if (readBytes < 0)
        {
            perror("error receiving from client");
            close(this->socket);
            string temp;
            return temp;
        }
        line.append(buffer);
    } while (buffer[0] != '\n' || buffer[0] != '\r');

    // return the vector in a string format
    return line;
}