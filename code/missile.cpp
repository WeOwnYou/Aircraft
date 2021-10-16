#include "missile.h"

Missile :: Missile(double x, double y, double v, double angle, double n) : Target(x, y, v, angle)
{
  this-> n = n;
  type = Target::Missile;
}

void Missile :: move(double dt)
{
  v += n * dt;
  position.CurPosition.x += v * cos(angle) * dt;
  position.CurPosition.y -= v * sin(angle) * dt;
  position.CurTime += dt;
}
int Missile :: getType()
{
    return 2;
}
