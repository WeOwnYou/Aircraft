#include "target.h"

Target :: Target(double x, double y, double v, double angle)
{
  position.InitPosition.x = x + 1328/2;
  position.InitPosition.y = y + 556/2;
  position.CurPosition.x = position.InitPosition.x;
  position.CurPosition.y = position.InitPosition.y;
  position.CurTime = 0;
  this->v = v;
  this->angle = angle / 180 * PI;//angle * 180 / 3.14 + 90;//3.14159265 + 90; //- 90;
  //if(this->angle > 360)
 //     this->angle -= 360;
}
double Target::get_x()
{
    return position.CurPosition.x;
}
double Target::get_y()
{
    return position.CurPosition.y;
}
double Target::get_v()
{
    return v;
}
