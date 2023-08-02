#ifndef STANDARTIO_H
#define STANDARTIO_H

#include <string>
#include <iostream>
#include "../commands/Command.h"
#include "DefaultIO.h"

using namespace std;

class StandartIO : public DefaultIO
{
public:
    StandartIO() = default;
    string read() override;
    void write(string data) override;
    ~StandartIO() = default;
};

#endif