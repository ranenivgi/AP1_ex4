#include "UploadData.h"

UploadData::UploadData(DefaultIO* io, ClientDetails* clientDetails)
{
    this->setDescription("1. upload an unclassified csv data file\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

void UploadData::execute()
{
    this->getIO()->write("Please upload your local train CSV file.");
    string line;

    while (true) {
        line = this->getIO()->read();
        if(line == "end of line" || line.empty()){
            break;
        } 
        readLineFromFile(line, this->getClientDetails()->getClassified());
    }

    if(!databaseValidation(this->getClientDetails()->getClassified())){
        this->getIO()->write("invalid input");
        return;
    }

    this->getIO()->write("Upload complete.");

    this->getIO()->write("Please upload your local test CSV file.");

    while (true) {
        line = this->getIO()->read();
        if(line != "end of line" || line.empty()){
            break;
        } 
        strToVec(line, this->getClientDetails()->getUnclassified());
    }

    if(!unclassifiedVectorsValidation(this->getClientDetails()->getUnclassified(),
                                        this->getClientDetails()->getClassified()[0].second.size())){
        this->getIO()->write("invalid input");
        return;
    }
    this->getIO()->write("Upload complete.");
}