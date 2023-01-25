#include "SocketIO.h"

/**
 * @brief Construct a new Socket I O:: Socket I O object
 *
 * @param socket
 */
SocketIO::SocketIO(int socket)
{
    this->socket = socket;
}

/**
 * @brief write data to the socket IO
 *
 * @param data
 */
void SocketIO::write(string data)
{
    // add tag for the end of line (it will be removed in the read function)
    data.append("end of line");
    // send the message to the client and check if it was sent sucessfully
    int sentBytes = send(this->socket, data.c_str(), strlen(data.c_str()), 0);
    if (sentBytes < 0)
    {
        perror("error writing");
    }
}

/**
 * @brief read data from the socket IO
 *
 * @return string
 */
string SocketIO::read()
{
    // create a buffer and initiallize it
    char buffer[1];
    // end of line tag
    string end = "end of line";
    string line;

    // read one byte after another and append to the line until we reached the "end of line" tag
    do
    {
        // reset the buffer
        memset(buffer, 0, 1);
        int readBytes = recv(this->socket, buffer, 1, 0);
        // connection closed
        if (readBytes == 0)
        {
            string temp = "connection is closed";
            return temp;
        }
        // error trying to receive
        else if (readBytes < 0)
        {
            string temp = "connection is closed";
            return temp;
        }
        line.append(buffer);
    } while (!equal(end.rbegin(), end.rend(), line.rbegin()));

    // remove the "end of line" tag from the end of the string
    line.erase(line.end() - 11, line.end());
    return line;
}