

#ifndef RAIN_H
#define RAIN_H

class Rain
{   
public:
    Rain();
    Rain(double rad, Point middle, double speed0, Color rain);
    Rain transform(double windspeed);
    Point pointy();
    double get_radius();
    Color get_color();
private:
    double radius;
    double speed;
    class Point center;
    class Color RainColor;
};

#endif

Rain::Rain()
{
	radius=1;
	center.set(0,0);
	RainColor.set(200,200,200);
}
Rain::Rain(double rad, Point middle, double speed0, Color rain)
{
	radius=rad;
    speed=speed0;
    center.set(middle);
	RainColor.set(rain.get_r(), rain.get_g(), rain.get_b());
}

Rain Rain::transform(double windrate)
{
    double xtransform=60.00/(1+100*pow(2.71828,-0.1*windrate));  
    double psx=center.x()+tan(xtransform*3.1415/180.00)*speed;
    double psy=center.y()+speed+0.0;
    center.set(center.x()+tan(xtransform*3.1415/180.00)*speed,center.y()+speed);
    return Rain(radius,Point(psx,psy),speed,RainColor);
}
Point Rain::pointy()
{
    return Point(center);
}
double Rain::get_radius()
{
    return radius;
}
Color Rain::get_color()
{
    return RainColor;
}