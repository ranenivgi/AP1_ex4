#include "CLI.h"

CLI::CLI(DefaultIO* io, Command* commands[5]){
    this->io = io;
    this->commands = commands;
}

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
    string input;
    int choice = 0;
    while (true) {
        menu();
        string str = this->io->read();
        stringstream ss(str);
        if (!(ss >> choice))
        {
            if(str == "connection is closed")
            {
            break;   
            }
            this->io->write("invalid input\n");
            continue;
        }
        if (choice == 8) {
            this->io->write("<exit>");
            break;
        }
        if (!ss.eof() || choice < 1 || choice > 5) {      
            this->io->write("invalid input\n");
            continue;
        }
        this->commands[choice - 1]->execute();
    }
}