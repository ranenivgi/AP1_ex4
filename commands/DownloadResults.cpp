#include "DownloadResults.h"

/**
 * @brief Construct a new Download Results:: Download Results object
 * 
 * @param io 
 * @param clientDetails 
 */
DownloadResults::DownloadResults(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("5. download results\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

/**
 * @brief sends to the client a path to create the new txt file and the text that should be sent
 * 
 * @param input 
 */
void DownloadResults::sendToClient(string input)
{
    // send the path for the creation of the file
    this->getIO()->write(input + "/ClassifiedResults.txt");
    
    // read each line from the unclassified database and append to a message
    int size = this->getClientDetails()->getUnclassified().size();
    string message;
    for (int i = 0; i < size; ++i)
    {
        message.append(to_string(i + 1) + "\t" + this->getClientDetails()->getUnclassified()[i].first + "\n");
    }
    // send the final message to the client
    this->getIO()->write(message);
}

/**
 * @brief execues the download command, receives a path (folder) from the user and send him the unclassified vectors 
 * which each of them is antecedent to a numeration.
 * 
 */
void DownloadResults::execute()
{
    // check if we uploaded the data
    if (this->getClientDetails()->getClassified().empty() || this->getClientDetails()->getUnclassified().empty())
    {
        this->getIO()->write("please upload data\n");
        return;
    }
    // check if we classified the data
    if (this->getClientDetails()->getUnclassified()[0].first.empty())
    {
        this->getIO()->write("please classify the data\n");
        return;
    }
    // read the folder path
    string input = this->getIO()->read();
    // send the client the file (so he can upload it to his local path)
    sendToClient(input);
}