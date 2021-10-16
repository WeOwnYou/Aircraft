#include "target.h"
#pragma once

class Missile : public Target
{
  private:
    double n;
  public:
    Missile(double x, double y, double v, double angle, double n);
    void move(double dt);
    int getType();
};
