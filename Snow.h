#include "Snow.h"


#ifndef SNOW_H
#define SNOW_H

class Snow
{
    public:
    	Snow();
    	Snow(double rad, int px, int py, Color snow);
    private:
    	double radius;
    	int x;
    	int y;
    	class Color SnowColor;
};

#endif

Snow::Snow()
{
	radius = 1;
	x = 5;
	y = 5;
	SnowColor.set_color(200, 200, 200);
}

Snow::Snow(double rad, int px, int py, Color snow){
	radius = rad;
	x = px;
	y = py;
	SnowColor.set_color(snow.get_r(), snow.get_g(), snow.get_b());

}