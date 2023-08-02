#ifndef DISPLAYRESULTS_H
#define DISPLAYRESULTS_H

#include <string>
#include "Command.h"

using namespace std;

class DisplayResults : public Command
{
public:
    DisplayResults(DefaultIO *io, ClientDetails *clientDetails);
    void execute() override;
    ~DisplayResults() = default;
};

#endif