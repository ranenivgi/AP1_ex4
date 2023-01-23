#ifndef DOWNLOADRESULTS_H
#define DOWNLOADRESULTS_H

#include <string>
#include "Command.h"

using namespace std;

class DownloadResults : public Command
{
public:
    DownloadResults(DefaultIO* io, ClientDetails* clientDetails);
    void execute() override;
    ~DownloadResults() = default;
};

#endif