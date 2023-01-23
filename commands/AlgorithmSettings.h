#ifndef ALGORIMSETTINGS_H
#define ALGORIMSETTINGS_H

#include <string>
#include "Command.h"
#include <sstream>
#include "../server/VectorDistances.h"

using namespace std;

class AlgorithmSettings : public Command
{
public:
    AlgorithmSettings(DefaultIO* io, ClientDetails* clientDetails);
    void execute() override;
    void convertInput(string input);
    ~AlgorithmSettings() = default;
};

#endif