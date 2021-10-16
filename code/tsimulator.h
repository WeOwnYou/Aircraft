#ifndef TSIMULATOR_H
#define TSIMULATOR_H
#pragma once
#include "rls.h"
#include "commandpost.h"
#include "target.h"

class TSimulator
{
private:
    double T0,Tk,dt;
    Rls *rls = new Rls(0,0,1,2,3);
    CommandPost CP;
    ofstream FT;
    int countTarget;
    vector<Target*> vector_of_flying_objects;
public:
    TSimulator(double t0, double dt, double tk);
    void createTarget(enum Target::Target_type type, vector<double> target);
    void run(double t);
    void createAircraft(vector<double> t);
    void createMissile(vector<double> t);
    vector<Target*> get_targets();
    void close_file();
};

#endif // TSIMULATOR_H
