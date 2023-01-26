#include "CLI.h"

/**
 * @brief Construct a new CLI::CLI object
 *
 * @param io
 * @param commands
 */
CLI::CLI(DefaultIO *io, Command *commands[5])
{
    this->io = io;
    this->commands = commands;
}

/**
 * @brief this function sends the menu to the client
 *
 */
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

/**
 * @brief this function executes a command following the client's choice
 *
 */
void CLI::start()
{
    string input;
    int choice = 0;
    while (true)
    {
        // send the menu
        menu();
        // read the client's choice
        string str = this->io->read();
        stringstream ss(str);
        // check if the choice is in the range (1-5,8)
        if (!(ss >> choice))
        {
            if (str == "connection is closed")
            {
                break;
            }
            this->io->write("invalid input\n");
            continue;
        }

        // if the choice is 8 we exit
        if (choice == 8)
        {
            this->io->write("<exit>");
            break;
        }
        if (!ss.eof() || choice < 1 || choice > 5)
        {
            this->io->write("invalid input\n");
            continue;
        }

        // execute the desired command
        this->commands[choice - 1]->execute();
    }
}