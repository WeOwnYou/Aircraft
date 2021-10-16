#include "aircraft.h"
#include "missile.h"
#pragma once
//#include "mainwindow.h"
using namespace std;

class Rls
{
private:
    //double x, y
    double distance_of_appear, t0, tk, dt;
    PosObject position;
    vector<Target*> vector_of_flying_objects;
    ofstream detected_targets;
    //Ui::MainWindow *ui;
public:
    Rls(double x0, double y0, double d0, double t0, double tk);
    void init(QStringList aircrafts, QStringList missiles);
    void peleng(double t, vector<Target*> vector_of_flying_objects1);
    double* get_time();
    void close();
    vector<Target*> get_coords();
    ~Rls();
};
