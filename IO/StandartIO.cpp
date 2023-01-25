#include "StandartIO.h"

void StandartIO::write(string data) {
    cout << data;
}

string StandartIO::read() {
    string data;
    getline(cin, data);
    return data;
}