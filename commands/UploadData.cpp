#include "UploadData.h"

/**
 * @brief Construct a new Upload Data:: Upload Data object
 *
 * @param io the IO
 * @param clientDetails the client details
 */
UploadData::UploadData(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("1. upload an unclassified csv data file\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

/**
 * @brief executes the command, uploads classified vectors from a CSV file and upload unclassified vectors from a CSV file.
 *
 */
void UploadData::execute()
{
    vector<pair<string, vector<double>>> classifiedVectors;
    vector<pair<string, vector<double>>> unclassifiedVectors;
    this->getIO()->write("Please upload your local train CSV file.\n");

    // receive the "start of file" tag and check validation
    string line = this->getIO()->read();
    if (line != "start of file")
    {
        this->getIO()->write("invalid input\n");
        return;
    }

    // read each line from the client and insert to the database until we reach the "end of file" tag
    while (true)
    {
        line = this->getIO()->read();
        if (line == "end of file" || line.empty())
        {
            break;
        }
        // insert to the database
        readClassifiedLineFromFile(line, classifiedVectors);
    }

    // check if the database is valid
    if (!databaseValidation(classifiedVectors))
    {
        this->getIO()->write("invalid input\n");
        return;
    }

    this->getIO()->write("Upload complete.\nPlease upload your local test CSV file.\n");

    // receive the "start of file" tag and check validation
    line = this->getIO()->read();
    if (line != "start of file")
    {
        this->getIO()->write("invalid input\n");
        return;
    }

    // read each line from the client and insert to the database until we reach the "end of file" tag
    while (true)
    {
        line = this->getIO()->read();
        if (line == "end of file" || line.empty())
        {
            break;
        }
        // insert to the database
        readUnclassifiedLineFromFile(line, unclassifiedVectors);
    }

    // check if the database is valid
    if (!unclassifiedVectorsValidation(unclassifiedVectors, classifiedVectors[0].second.size()))
    {
        this->getIO()->write("invalid input\n");
        return;
    }

    this->getIO()->write("Upload complete.\n");

    // set the client databases to the ones the user inserted
    this->getClientDetails()->setClassified(classifiedVectors);
    this->getClientDetails()->setUnclassified(unclassifiedVectors);
}