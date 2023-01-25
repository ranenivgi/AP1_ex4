#include "UploadData.h"

UploadData::UploadData(DefaultIO* io, ClientDetails* clientDetails)
{
    this->setDescription("1. upload an unclassified csv data file\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

void UploadData::execute()
{
    vector<pair<string, vector<double>>> classifiedVectors;
    vector<pair<string, vector<double>>> unclassifiedVectors;
    this->getIO()->write("Please upload your local train CSV file.\n");
    string line = this->getIO()->read();

    if (line != "start of file") {
        this->getIO()->write("invalid input\n");
        return;
    }
    while (true) {
        line = this->getIO()->read();
        if(line == "end of file" || line.empty()){
            break;
        } 
        readLineFromFile(line, classifiedVectors);
    }

    if(!databaseValidation(classifiedVectors)){
        this->getIO()->write("invalid input\n");
        return;
    }

    this->getIO()->write("Upload complete.\nPlease upload your local test CSV file.\n");

    line = this->getIO()->read();
    if (line != "start of file") {
        this->getIO()->write("invalid input\n");
        return;
    }
    while (true) {
        line = this->getIO()->read();
        if(line == "end of file" || line.empty()){
            break;
        } 
        strToVec(line, unclassifiedVectors);
    }

    if(!unclassifiedVectorsValidation(unclassifiedVectors,
                                        classifiedVectors[0].second.size())){
        this->getIO()->write("invalid input\n");
        return;
    }

    this->getIO()->write("Upload complete.\n");
    this->getClientDetails()->setClassified(classifiedVectors);
    this->getClientDetails()->setUnclassified(unclassifiedVectors);
}