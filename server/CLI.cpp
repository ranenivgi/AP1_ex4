#include "CLI.h"

void CLI::menu()
{
    string menuMessage = "Welcome to the KNN Classifier server. Please choose an option:\n";
    for (int i = 0; i < 5; ++i)
    {
        menuMessage.append(this->commands[i]->getDescription());
    }
    menuMessage.append("8. exit\n");
    this->io->write(menuMessage);
}

void CLI::start()
{
    stringstream ss;
    int choice = 0;
    while (true) {
        menu();
        ss << (this->io->read());
        if (!(ss >> choice))
        {
            this->io->write("invalid input\n");
            continue;
        }
        if (choice == 8) {
            break;
        }
        if (!ss.eof() || choice < 1 || choice > 5) {      
            this->io->write("invalid input\n");
            continue;
        }
        this->commands[choice - 1]->execute();
    }
}