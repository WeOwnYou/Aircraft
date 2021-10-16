#include "aircraft.h"

Aircraft::Aircraft(double x, double y, double v, double angle) : Target(x, y, v, angle)
{
    type = Target::Aircraft;
}

void Aircraft :: move (double dt)
{
  position.CurPosition.x += v * cos(angle) * dt;
  position.CurPosition.y -= v * sin(angle) * dt;
  //x -= v * cos(angle) * dt;
  //y -= v * sin(angle) * dt;
  //t += 1;
  position.CurTime += dt;
}

int Aircraft::getType()
{
    return 1;
}
