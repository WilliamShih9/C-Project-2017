#include "Point.h"
#include "Color.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std; 

#ifndef CLOUD_H
#define CLOUD_H

class Cloud{
    public:
	Cloud();
	Cloud(int ellipse, double pwind, int px, int py, double width0, double height0, Color cloud);
    void set_cloud(double pwind, int px, int py, double width0, double height0, Color cloud);
    void set_ellipses(int ellipse);
    void keep_ellipses(int numellipse, vector<Point> opt);
    void set_dimension(double width0, double height0);
    Point get_middle();
    Color get_color();
    int get_width();
    int get_height();
    vector<Point> get_ellipses();
    private:
    class Point middle;
    class Color cloudcolor;
    double wind;
    double width;
    double height;
    vector<Point> ellipses;
};
#endif




//An ellipse can be represented by the vector function r(t) = < width*cos(t) , height*sin(t) >
//We use this fact to find the centers of the circles along the ellipse that make the ellipse 
//fluffy and look like a cloud 
Cloud::Cloud(){
	middle.set(0,0);
    cloudcolor.set(200,200,200);
	wind=0;
    vector<Point> ellipses(0);
}

Cloud::Cloud(int ellipse, double pwind, int px, int py, double width0, double height0, Color cloud)
{
	middle.set(px,py);
	wind=pwind;
    width=width0;
    height=height0;
	cloudcolor.set(cloud.get_r(), cloud.get_g(), cloud.get_b());
    vector<Point> ellipses(ellipse);
}    

void Cloud::set_cloud(double pwind, int px, int py, double width0, double height0, Color cloud)
{
    middle.set(px,py);
	wind=pwind;
    width=width0;
    height=height0;
	cloudcolor.set(cloud.get_r(), cloud.get_g(), cloud.get_b());
}
void Cloud::set_ellipses(int ellipse)
{
    // min is middle.x-width, max middle.x+width
    // min is middle.y-height, max is middle.y+height
    for (int i=0; i<ellipse; i++){
        int intwidth=(int)(width+0.5);
        int intheight=(int)(height+0.5);
		int xvalue=1.0*(rand()%intwidth)-0.5*width;
		int yvalue=1.0*(rand()%intheight)-0.5*height;
        Point* coordinate=new Point(xvalue,yvalue);
        ellipses.push_back(*coordinate);
	}
}
void Cloud::keep_ellipses(int numellipse, vector<Point> opt)
{
    for (int i=0; i<numellipse; i++){
        ellipses.push_back(opt[i]);
    }
}
vector<Point> Cloud::get_ellipses()
{
	return ellipses;
}
int Cloud::get_width()
{
    return (int)(width+0.5);
}
int Cloud::get_height()
{
    return (int)(height+0.5);
}
Color Cloud::get_color()
{
    return cloudcolor;
}
Point Cloud::get_middle()
{
    return middle;
}