#ifndef CLASSIFYDAYA_H
#define CLASSIFYDAYA_H

#include <string>
#include "Command.h"
#include "../server/Knn.h"

using namespace std;

class ClassifyData : public Command
{
public:
    ClassifyData(DefaultIO *io, ClientDetails *clientDetails);
    void execute() override;
    ~ClassifyData() = default;
};

#endif