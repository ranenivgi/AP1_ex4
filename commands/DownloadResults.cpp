#include "DownloadResults.h"

DownloadResults::DownloadResults(DefaultIO* io, ClientDetails* clientDetails)
{
    this->setDescription("5. download results\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

void DownloadResults::sendToClient(string input) {
    this->getIO()->write(input + "/ClassifiedResults.txt");
    int size = this->getClientDetails()->getUnclassified().size() - 1;
    string message;
    for (int i = 0; i < size; ++i) {
        message.append(to_string(i + 1) + "\t" + this->getClientDetails()->getUnclassified()[i].first + "\n");
    }
    message.append(to_string(size + 1) + "\t" + this->getClientDetails()->getUnclassified()[size].first);
    this->getIO()->write(message);
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
    sendToClient(input);
}