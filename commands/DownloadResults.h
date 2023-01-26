#ifndef DOWNLOADRESULTS_H
#define DOWNLOADRESULTS_H

#include <string>
#include "Command.h"
#include <thread>

using namespace std;

class DownloadResults : public Command
{
private:
    void sendToClient(string input);

public:
    DownloadResults(DefaultIO *io, ClientDetails *clientDetails);
    void execute() override;
    ~DownloadResults() = default;
};

#endif