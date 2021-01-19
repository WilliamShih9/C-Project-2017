#include <iostream>
#include<cmath>
using namespace std;
#ifndef TORNADO_H
#define TORNADO_H


class Tornado
{
    public:
    Tornado();
    Tornado( double T_amplitude0, double T_height0, double T_width0, Color T_color0,Point T_middle );
    void set_Tornado( double T_amplitude0, double T_height0, double T_width0, Color T_color0, Point T_middle);
    private:
    Point center;
    double T_amplitude;
    double height;
    double width;
    Color  T_color0;

};
#endif // TORNADO_H

Tornado::Tornado()
{
    center.set(0,0);
    T_amplitude=0;
    height=0;
    width=0;
    T_color0.set(0,0,0);
}

Tornado::Tornado(double T_amplitude0, double T_height0, double T_width0, Color T_color0,Point T_middle)
{
    T_amplitude=T_amplitude0;
    height= T_height0;
    width= T_width0;
    center.set(T_middle);
    T_color0.set(T_color0);
}

void Tornado::set_Tornado(double T_amplitude0, double T_height0, double T_width0, Color T_color0,Point T_middle)
{
    T_amplitude=T_amplitude0;
    height= T_height0;
    width= T_width0;
    center.set(T_middle);
    T_color0.set(T_color0);
}

