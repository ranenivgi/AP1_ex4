#include "Command.h"

DefaultIO* Command::getIO() {
    return this->io;
}

void Command::setIO(DefaultIO* io) {
    this->io = io;
}

ClientDetails* Command::getClientDetails() {
    return this->clientDetails;
}

void Command::setDescription(string description) {
    this->description = description;
}

string Command::getDescription() {
    return this->description;
}

void Command::setClientDetails(ClientDetails *clientDetails) {
    this->clientDetails = clientDetails;
}

