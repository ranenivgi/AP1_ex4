#include "DisplayResults.h"

/**
 * @brief Construct a new Display Results:: Display Results object
 *
 * @param io
 * @param clientDetails
 */
DisplayResults::DisplayResults(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("4. display results\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

/**
 * @brief execues the display command, send to the user a list of the unclassified vectors which each of them is
 * antecedent to a numeration.
 *
 */
void DisplayResults::execute()
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

    // send the vectors to the client
    int size = this->getClientDetails()->getUnclassified().size();
    for (int i = 0; i < size; ++i)
    {
        this->getIO()->write(to_string(i + 1) + "\t" + this->getClientDetails()->getUnclassified()[i].first + "\n");
    }
    this->getIO()->write("done\n");
}