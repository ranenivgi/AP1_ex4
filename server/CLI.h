#ifndef CLI_H
#define CLI_H

#include <string>
#include "../IO/DefaultIO.h"
#include "../commands/Command.h"
#include <sstream>

using namespace std;

class CLI
{
private:
    DefaultIO* io;
    Command* commands[5];
    void menu();

public:
    CLI(/* args */) = default;
    void start();
    ~CLI() = default;
};

#endif