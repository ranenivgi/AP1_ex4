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
    this->getIO()->write(input);
    // read each line from the unclassified database and append to a message
    int size = this->getClientDetails()->getUnclassified().size() - 1;
    string message;
    for (int i = 0; i < size; ++i)
    {
        message.append(to_string(i + 1) + "\t" + this->getClientDetails()->getUnclassified()[i].first + "\n");
    }
    // append the last line from the unclassified database to a message without '\n'
    message.append(to_string(size + 1) + "\t" + this->getClientDetails()->getUnclassified()[size].first);
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

    // if received a path to a folder create a new file named "ClassifiedResults.txt", otherwise its a txt file.
    string writeFile = ".txt";
    if (!equal(writeFile.rbegin(), writeFile.rend(), input.rbegin()))
    {
        input.append("/ClassifiedResults.txt");
    }

    // check if its a file with csv ending (invalid path and the file information was sent)
    if (input == "start of file")
    {
        while (this->getIO()->read() != "end of file") {
            continue;
        }
    }
    // send the client the file (so he can upload it to his local path)
    sendToClient(input);
}