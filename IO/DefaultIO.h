#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <string>

using namespace std;

class DefaultIO
{
public:
    DefaultIO(/* args */) = default;
    virtual string read() = 0;
    virtual void write(string data) = 0;
    ~DefaultIO() = default;
};

#endif