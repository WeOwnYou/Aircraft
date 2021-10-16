#include "rls.h"
//#include "Target.h"

Rls::Rls(double x, double y, double d0, double t0, double tk)
{
    position.CurPosition.x = x;
    position.CurPosition.y = y;
    this->distance_of_appear = d0;
    this->t0 = t0;
    this->tk = tk;
    this->dt = 0.01;
    printf("\n%f !! %f %f\n",this->t0,dt,this->tk);
    detected_targets.open("Detected_Targets.txt");
}


void Rls::init(QStringList aircrafts, QStringList missiles)
{
    for (int i = 0; i < aircrafts.size(); i++)
    {
        QStringList t = aircrafts[i].split(" ");
        vector_of_flying_objects.push_back(new Aircraft(t[0].toDouble(), t[1].toDouble(), t[2].toDouble(),t[3].toDouble()));
    }
    for (int i = 0; i < missiles.size(); i++)
    {
        QStringList t = missiles[i].split(" ");
        vector_of_flying_objects.push_back(new Missile(t[0].toDouble(), t[1].toDouble(), t[2].toDouble(),t[3].toDouble(), t[4].toDouble()));
    }
}

double* Rls::get_time()
{
    double time[3] = {t0, tk, dt};
    return time;
}

void Rls::peleng(double t, vector<Target*> vector_of_flying_objects1)
{
    double azimut;

    int n = vector_of_flying_objects1.size();
    //detected_targets<<n;

    for (int i = 0; i < n; i++)
    {
        double d0;
        //vector_of_flying_objects[i]->move(dt);
        d0 = sqrt(pow(position.CurPosition.x - vector_of_flying_objects1[i]->get_x(), 2) + pow(position.CurPosition.y - vector_of_flying_objects1[i]->get_y(), 2));
        detected_targets << vector_of_flying_objects1[i]->get_v() << " "<<t<<"\n";
        if (d0 < distance_of_appear)
        {
            azimut = atan2((position.CurPosition.y - vector_of_flying_objects1[i]->get_y()),
                    (position.CurPosition.x - vector_of_flying_objects1[i]->get_x())); //* 180 / 3.14 + 180;
            //cout<<endl<<azimut<<"!!!"<<endl;
            //detected_targets << azimut << endl;
         //}else cout<<endl<<"mda "<<atan2((y - vector_of_flying_objects[i]->get_y()),
           //                            (x - vector_of_flying_objects[i]->get_x())) * 180 / 3.14; //+ 180<<endl;
        }
    }
}

vector<Target*> Rls::get_coords()
{
    return vector_of_flying_objects;
}

void Rls::close()
{

    detected_targets.close();
}

Rls ::~Rls()
{
    vector_of_flying_objects.clear();
    vector_of_flying_objects.shrink_to_fit();
}
