#include "AlgorithmSettings.h"

AlgorithmSettings::AlgorithmSettings(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("2. algorithm settings\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

void AlgorithmSettings::execute()
{
    this->getIO()->write("The current KNN parameters are: K = " + to_string(this->getClientDetails()->getK()) + " distance metric = " + this->getClientDetails()->getAlgorithm() + "\n");
    string input = this->getIO()->read();
    if (input.empty())
    {
        return;
    }
    convertInput(input);
}

/**
 * @brief the function receives string input and splits it to three variables
 *
 * @param input the string input
 * @param unclassifiedVec the first part of the string is being transfered to a vector (unclassified)
 * @param algorithm the second part of the string is being transfered to a string (algorithm)
 * @param k the third part of the string is being transfered to an int (k neighbors)
 */
void AlgorithmSettings::convertInput(string input)
{
    stringstream wordStream(input);
    string value;
    int k;

    getline(wordStream, value, ' ');
    stringstream ss(value);
    wordStream >> value;
    bool isValidAlgorithm = selectAlgorithm(value) == -1 ? false : true;
    if(!(wordStream.eof()))
    {
        this->getIO()->write("invalid input\n");
        return;
    }
    if (!((ss >> k) && ss.eof()) || k < 1)
    {
        this->getIO()->write("invalid input for K\n");
        if (!isValidAlgorithm) {
            this->getIO()->write("invalid value for metric\n");
        }
        return;
    }

    if (!isValidAlgorithm) {
        this->getIO()->write("invalid value for metric\n");
        return;
    }
    this->getClientDetails()->setK(k);
    this->getClientDetails()->setAlgorithm(value);
}