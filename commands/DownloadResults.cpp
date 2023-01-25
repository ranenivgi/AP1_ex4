#include "DownloadResults.h"

DownloadResults::DownloadResults(DefaultIO* io, ClientDetails* clientDetails)
{
    this->setDescription("5. download results\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

void DownloadResults::execute()
{
    if (this->getClientDetails()->getClassified().empty() 
    || this->getClientDetails()->getUnclassified().empty()) {
        this->getIO()->write("please upload data\n");
        return;
    }
    if (this->getClientDetails()->getUnclassified()[0].first.empty()) {
        this->getIO()->write("please classify the data\n");
        return;
    }

    string input = this->getIO()->read();
    this->getIO()->write(input + "/ClassifiedResults.txt");
    int size = this->getClientDetails()->getUnclassified().size();
    string message;
    for (int i = 0; i < size; ++i) {
        message.append(to_string(i + 1) + "\t" + this->getClientDetails()->getUnclassified()[i].first + "\n");
    }
    this->getIO()->write(message);
}