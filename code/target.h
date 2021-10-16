#pragma once

#include <iostream>
#include <fstream>
#include<QString>
#include<QtDebug>
#include <math.h>
#define PI 3.141592653589793
//#include "Target_type.h"
#include "PosObject.h"


class Target
{
  public:
    enum Target_type {Aircraft, Missile};
  protected:
    double v, angle, t;
    PosObject position;
    Target_type type;
  public:
    Target(double x, double y, double v, double angle);
    virtual void move(double dt){};
    double get_x();
    double get_y();
    double get_v();
    virtual int getType(){return 0;}
    //Target_type get_type();
};
