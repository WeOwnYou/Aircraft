#ifndef COMMANDPOST_H
#define COMMANDPOST_H
#include "PosObject.h"

class CommandPost
{
private:
    double SafetyDistance;
    Point pos;
public:
    CommandPost();
    void move();
};

#endif // COMMANDPOST_H
