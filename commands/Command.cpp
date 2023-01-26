#include "Command.h"

/**
 * @brief getter for the IO
 * 
 * @return DefaultIO* 
 */
DefaultIO *Command::getIO()
{
    return this->io;
}

/**
 * @brief setter for the IO
 * 
 * @param io 
 */
void Command::setIO(DefaultIO *io)
{
    this->io = io;
}

/**
 * @brief getter for the client details
 * 
 * @return ClientDetails* 
 */
ClientDetails *Command::getClientDetails()
{
    return this->clientDetails;
}

/**
 * @brief setter for the command description
 * 
 * @param description 
 */
void Command::setDescription(string description)
{
    this->description = description;
}

/**
 * @brief getter for the command description
 * 
 * @return string 
 */
string Command::getDescription()
{
    return this->description;
}

/**
 * @brief setter for the client details
 * 
 * @param clientDetails 
 */
void Command::setClientDetails(ClientDetails *clientDetails)
{
    this->clientDetails = clientDetails;
}
