#include "target.h"
#pragma once

class Aircraft : public Target
{
  public:
    Aircraft(double x, double y, double v, double angle);
    void move(double dt);
    int getType();
};
