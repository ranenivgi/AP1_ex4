#ifndef UPLOADDATA_H
#define UPLOADDATA_H

#include <string>
#include "Command.h"
#include "../server/ProcessFile.h"
#include "../IO/DefaultIO.h"

using namespace std;

class UploadData : public Command
{
public:
    UploadData(DefaultIO* io, ClientDetails* clientDetails);
    void execute() override;
    ~UploadData() = default;
};

#endif
