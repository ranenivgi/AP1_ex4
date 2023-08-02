#ifndef CLI_H
#define CLI_H

#include <string>
#include "../IO/DefaultIO.h"
#include "../commands/Command.h"
#include <sstream>
#include <iostream>

using namespace std;

class CLI
{
private:
    DefaultIO *io;
    Command **commands;
    void menu();

public:
    CLI(DefaultIO *io, Command *commands[5]);
    void start();
    ~CLI() = default;
};

#endif