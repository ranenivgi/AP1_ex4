#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "../IO/DefaultIO.h"
#include "../client/ClientDetails.h"

using namespace std;

class Command
{
private:
    string description;
    DefaultIO *io;
    ClientDetails *clientDetails;
public:
    Command(/* args */) = default;
    virtual void execute() = 0;
    DefaultIO *getIO();
    void setIO(DefaultIO* io);
    ClientDetails *getClientDetails();
    void setClientDetails(ClientDetails *clientDetails);
    void setDescription(string description);
    ~Command() = default;
};

#endif