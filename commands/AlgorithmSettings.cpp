#include "AlgorithmSettings.h"

/**
 * @brief Construct a new Algorithm Settings:: Algorithm Settings object
 * 
 * @param io 
 * @param clientDetails 
 */
AlgorithmSettings::AlgorithmSettings(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("2. algorithm settings\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

/**
 * @brief executes the algorithm command, its purpose is to be able to receive "K" neighbors and "algorithm" sepereated
 * by a space, and set it for the next classification.
 * 
 */
void AlgorithmSettings::execute()
{
    this->getIO()->write("The current KNN parameters are: K = " + to_string(this->getClientDetails()->getK()) 
                                + " distance metric = " + this->getClientDetails()->getAlgorithm() + "\n");
    // read the desired algorithm settings
    string input = this->getIO()->read();
    if (input.empty())
    {
        return;
    }
    // convert the input from a string and set it for the client data
    convertAndSetInput(input);
}

/**
 * @brief the function receives string input and splits it to two variables (K and algorithm), then it inserts it to
 * the user data.
 * 
 * @param input the string input
 * @param unclassifiedVec the first part of the string is being transfered to a vector (unclassified)
 * @param algorithm the second part of the string is being transfered to a string (algorithm)
 * @param k the third part of the string is being transfered to an int (k neighbors)
 */
void AlgorithmSettings::convertAndSetInput(string input)
{
    stringstream wordStream(input);
    string value;
    int k;

    getline(wordStream, value, ' ');
    // take the algorithm and insert into string variable
    stringstream ss(value);
    // take the k number and insert into int variable
    wordStream >> value;
    // check algorithm validation
    bool isValidAlgorithm = selectAlgorithm(value) == -1 ? false : true;
    // check k validation
    if (!((ss >> k) && ss.eof()) || k < 1)
    {
        this->getIO()->write("invalid input for K\n");
        if (!isValidAlgorithm)
        {
            this->getIO()->write("invalid value for metric\n");
        }
        return;
    }
    if (!isValidAlgorithm)
    {
        this->getIO()->write("invalid value for metric\n");
        return;
    }
    
    // set the client details
    this->getClientDetails()->setK(k);
    this->getClientDetails()->setAlgorithm(value);
}