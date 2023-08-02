#include "StandartIO.h"

/**
 * @brief writes data to the standart IO
 * 
 * @param data 
 */
void StandartIO::write(string data) {
    cout << data;
}

/**
 * @brief reads data from the standart IO
 * 
 * @return string 
 */
string StandartIO::read() {
    string data;
    getline(cin, data);
    return data;
}