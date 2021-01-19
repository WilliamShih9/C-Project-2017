#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

#ifndef WAVE_H
#define WAVE_H

class Wave{
    public:
    Wave();
    Wave(double amplitude0, double wavelength0, Point middle, double period0, Color color0);
    void set_wave(double amplitude0, double wavelength0, Point middle, double period0, Color color0);
    private:
    Point center;
    double amplitude;
    double wavelength;
    double period;
    Color color0;
   };
#endif

Wave::Wave()
{
center.set(0,0);
amplitude=0;
wavelength=0;
period=0;
color0.set(0,0,0);
}

Wave::Wave(double amplitude0, double wavelength0, Point middle, double period0, Color color0)
{
amplitude=amplitude0;
wavelength=wavelength0;
center.set(middle);
period=period0;
color0.set(color0);
}

void Wave::set_wave(double amplitude0, double wavelength0, Point middle, double period0, Color color0)
{
	amplitude=amplitude0;
	wavelength=wavelength0;
	center.set(middle);
	period=period0;
	color0.set(color0);
}


