#include "tsimulator.h"

TSimulator::TSimulator(double t0, double dt, double tk)
{
    this->T0 = t0;
    this->Tk = tk;
    this->dt = dt;
}

void TSimulator::run(double t)
{
    //FT.open("Detected_Targets.txt");
    int n = vector_of_flying_objects.size();

    for (int i = 0; i < n; i++)
    {
        //cout<<vector_of_flying_objects[i]->get_x()<<endl;
        vector_of_flying_objects[i]->move(dt);
    }
    rls->peleng(t, vector_of_flying_objects);
}

void TSimulator::createAircraft(vector<double> t)
{
    vector_of_flying_objects.push_back(new Aircraft(t[0], t[1], t[2], t[3]));
    return;
}

void TSimulator::createMissile(vector<double> t)
{
    vector_of_flying_objects.push_back(new Missile(t[0], t[1], t[2], t[3], t[4]));
    return;
}

void TSimulator::createTarget(enum Target::Target_type type, vector<double> target)
{
    if(type == Target::Target_type::Aircraft)
        createAircraft(target);
    else if(type == Target::Target_type::Missile)
        createMissile(target);
    return;
}

vector<Target*> TSimulator::get_targets()
{
    return vector_of_flying_objects;
}
void TSimulator::close_file()
{
    rls->close();
}
