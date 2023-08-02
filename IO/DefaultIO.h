#ifndef DEFAULTIO_H
#define DEFAULTIO_H

#include <string>

using namespace std;

/**
 * @brief DefaultIO abstract class
 * 
 */
class DefaultIO
{
public:
    DefaultIO() = default;
    virtual string read() = 0;
    virtual void write(string data) = 0;
    ~DefaultIO() = default;
};

#endif