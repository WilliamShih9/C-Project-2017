
#include "Cloud.h"
#include "Rain.h"
#include "Wave.h"
#include <cmath>
#include <cstdlib>
using namespace std;

double degrees_to_rad(int deg)
{
    return deg*3.141592653589793/180.0;
}
#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
    public:
    Graphics();
    Graphics(int x, int y);
    void set(int x, int y);
    // Change entire grid into one color
        void full_color(unsigned char red, unsigned char green, unsigned char blue);
        void full_color(Color complete);
    // Colors the entire board a color based on the area of the clouds that take up the screen and the darkness factor, increasing the darknessfactor makes the sky darker with the same amount of clouds
        void set_sky(Color initialsky, int clouds, double darknessfactor);
    // Change current drawing and filling color
        void canvas_color(unsigned char red, unsigned char green, unsigned char blue);
        void canvas_color(Color complete);
    // Draw Circle with center x,y
        void draw_circle(int radius, Point middle);
    // Fill Circle with center x,y
        void fill_circle(int radius, Point middle);
    // Draw Oval with center x,y
        void draw_oval(Point middle, double width, double height);
    // Draw Oval with center x,y and rotation in degrees
        void draw_oval(Point middle, double width, double height, int degrees);
    // Fill Oval with center x,y
        void fill_oval(Point middle, double width, double height);
    // Fill Oval with center x,y and rotation in degrees
        void fill_oval(Point middle, double width, double height, int degrees);
    // Draw line with start x0,y0 and end x1,y1
        void draw_line(Point initial, Point last);
    // Draw line rotated
        void draw_line(Point initial, Point last, int degrees);
    // Draw Rectangle with upper left corner x,y and lower right corner x+width,y+height
        void draw_rect(Point upleft, int width, int height);
    // Draw Rectangle with rotation in degrees
        void draw_rect(Point upleft, int width, int height, int degrees);
    // Fill Rectangle with upper left corner x,y and lower right corner x+width,y+height
        void fill_rect(Point upleft, int width, int height);
    // Fill Rectangle with rotation in degrees
        void fill_rect(Point upleft, int width, int height, int degrees);
    // Fill Border with xpixels left and right, ypixels top and bottom
        void fill_border(int xpixels, int ypixels);
    // Draw a Boat with rotation in degrees
        void draw_boat(Point middle, double height, double base, double width_mast, double depth, double degrees, Color ofboat, Color ofmast);
    // For cloudnumber cloud, draw numraindrops per second, and drop at speed (pixels per frame)
        void set_rain(int cloudnumber, double percentage, int sizethreshold, double speed, Color color0, double rainthreshold);
     // Adds a raindrop to the current frame
        void add_rain(Rain att);
     // Draws the raindrops on the current frame
        void draw_rain();
      // Returns the vector of raindrops on the current frame
        vector<Rain> get_rain();
        void setup_clouds(int numberofclouds);
    // Sets the cloud of the cloudnumber with the number of ellipses, the wind speed, the center point, the width, the height, and the color
        void set_cloud(int cloudnumber, int numellipse, double wind, Point middle, int width, int height, Color cloud);
	// Sets the cloud of the cloudnumber with the wind speed, the center point, the width, the height, the color, the vector of points, and the factor
        void set_cloud(int cloudnumber, double wind, Point middle, int width, int height, Color cloud, vector<Point> copy, double factor);
        // Draws the cloudnumber's cloud shape centered at a certain point
        void draw_cloud(int cloudnumber, Point middle);
    // Cloud shape using the cloud's point, which already has a point defined for its center
        void draw_cloud(int cloudnumber);
        // Cloud shape with the number of ellipses, a vector of points, and a factor
        void cloud_shape(int cloudnumber, int numellipse, vector<Point> opt, double factor);
    // Get cloud shape
        vector<Point> get_cloud(int cloudnumber);
	// Draw a circular object with rays sticking out at 18 degree intervals at point middle, with a radius, and a color
    	void draw_sun(Point middle, double radius, Color suncol);
	// Draw a wave with a height, width, period, yaxis, and color. All points below the wave are also colored the color of the current wave
        void draw_wave(double height, double width, double period, Point middle, Color wave);
    //  Draw a tornado with a cetain height, width, amplitude, centered at a point and with a certain color
        void draw_Tornado(double height, double width, double amplitude, double period, Point middle, Color tornado);
    Color** get_canvas() const;
    // Rotates pixels around current center with rotation in radians and draws pixel of current color
    void rotate(double x, double y);
    // Draws a pixel of current color there
    void draw(int x, int y);
    private:
    Color** canvas;
    class Color current;
    int px;
    int py;
    double rotation;
    class Point center;
    vector<Rain> newrain;
    vector<Rain> rainlocation;
    class Wave wavecolor;
    int cloudnumber;
    Cloud* cloudlocation;
};

#endif

void Graphics::rotate(double x, double y)
{
    int x2 = ((x-center.x())*cos(rotation))-((y-center.y())*sin(rotation))+center.x();
    int y2 = ((x-center.x())*sin(rotation))+((y-center.y())*cos(rotation))+center.y();
    draw(x2,y2);
}
void Graphics::draw(int x, int y)
{
    if (x<px && x>=0 && y<py && y>=0) {
        canvas[x][y].set(current);
    }
}
Graphics::Graphics()
{
    canvas=new Color*[0];
    for (int i=0; i<0; i++){
        canvas[i]=new Color[0];
    }
    px=0;
    py=0;
    vector<Cloud> cloudlocation(0);
}
Graphics::Graphics(int x, int y)
{
    canvas=new Color*[x];
	for (int i=0; i<y; i++){
		canvas[i]=new Color[y];
	}
    px=x;
    py=y;
    vector<Point> rainlocation(0);
    vector<Cloud> cloudlocation(0);
}
void Graphics::set(int x, int y)
{
    canvas=new Color*[x];
	for (int i=0; i<x; i++){
		canvas[i]=new Color[y];
	}
    px=x;
    py=y;
    vector<Cloud> cloudlocation(0);
}
void Graphics::full_color(unsigned char red, unsigned char green, unsigned char blue)
{
    for (int i=0; i<px; i++){
        for (int j=0; j<py; j++){
            canvas[i][j].set(red,green,blue);
        }
    }
}
void Graphics::set_sky(Color initialsky, int clouds, double darknessfactor)
{
    int red=initialsky.get_r();
    int green=initialsky.get_g();
    int blue=initialsky.get_b();
    double area=0;
    for (int i=1; i<=clouds; i++){
        Point mid=cloudlocation[i].get_middle();
        double width=cloudlocation[i].get_width();
        double height=cloudlocation[i].get_height();
        area+=width*height;
    }
    double percentage=darknessfactor*area/(px*py);
    if (red-percentage>=10 && green-percentage>=10 && blue-percentage>=10){
            full_color(red-percentage,green-percentage,blue-percentage);
    }
    else {
            full_color(15,15,15);
    }
}
void Graphics::full_color(Color complete)
{
    for (int i=0; i<px; i++){
        for (int j=0; j<py; j++){
            canvas[i][j].set(complete);
        }
    }
}
void Graphics::canvas_color(unsigned char red, unsigned char green, unsigned char blue)
{
    current.set(red,green,blue);
}
void Graphics::canvas_color(Color complete)
{
    current.set(complete);
}
void Graphics::draw_circle(int radius, Point middle)
{
    double x=middle.x();
    double y=middle.y();;
    center.set(x,y);
    int sx=-radius;
    int sy=0;
    int error=2-2*radius;
    do {
        draw(x-sx,y+sy);
        draw(x-sy,y-sx);
        draw(x+sx,y-sy);
        draw(x+sy,y+sx);
        radius=error;
        if (radius<=sy){
            error+=++sy*2+1;
        }
        if (radius>sx || error>sy){
            error+=++sx*2+1;
        }
    }
    while(sx<0);
}
void Graphics::fill_circle(int radius, Point middle)
{
    double x=middle.x();
    double y=middle.y();;
    center.set(x,y);
    for (int i=x-radius; i<=x+radius; i++){
        for (int j=y-radius; j<=y+radius; j++) {
            if ((i-x)*(i-x)+(j-y)*(j-y)<radius*radius){
                draw(i,j);
            }
        }
    }
}
void Graphics::draw_oval(Point middle, double width, double height)
{
    double x=middle.x();
    double y=middle.y();;
    center.set(x,y);
    width/=2;
    height/=2;
    int x0=x-width;
    int x1=x+width;
    int y0=y-height;
    int y1=y+height;
    int a=abs(x1-x0);
    int b=abs(y1-y0);
    int b1=b&1;
    long sx=4*(1-a)*b*b;
    long sy=4*(b1+1)*a*a;
    long error=sx+sy+b1*a*a;
    long e2;
    if (x0>x1){
        x0=x1;
        x1+=a;
    }
    if (y0>y1){
        y0=y1;
    }
    y0+=(b+1)/2;
    y1=y0-b1;
    a*=8*a;
    b1=8*b*b;
    do{
        draw(x1,y0);
        draw(x0,y0);
        draw(x0,y1);
        draw(x1,y1);
        e2=2*error;
        if (e2<=sy){
            y0++;
            y1--;
            error+=sy+=a;
        }
        if (e2>=sx || 2*error>sy){
            x0++;
            x1--;
            error+=sx+=b1;
        }
    } while (x0<=x1);

    while (y0-y1<b){
        draw(x0-1,y0);
        draw(x1+1,y0++);
        draw(x0-1,y1);
        draw(x1+1,y1--);
    }
}
void Graphics::draw_oval(Point middle, double width, double height, int degrees)
{
    double x=middle.x();
    double y=middle.y();;
    rotation=degrees_to_rad(degrees);
    center.set(x,y);
    width/=2;
    height/=2;
    int x0=x-width;
    int x1=x+width;
    int y0=y-height;
    int y1=y+height;
    int a=abs(x1-x0);
    int b=abs(y1-y0);
    int b1=b&1;
    long sx=4*(1-a)*b*b;
    long sy=4*(b1+1)*a*a;
    long error=sx+sy+b1*a*a;
    long e2;
    if (x0>x1){
        x0=x1;
        x1+=a;
    }
    if (y0>y1){
        y0=y1;
    }
    y0+=(b+1)/2;
    y1=y0-b1;
    a*=8*a;
    b1=8*b*b;
    do{
        rotate(x1,y0);
        rotate(x0,y0);
        rotate(x0,y1);
        rotate(x1,y1);
        e2=2*error;
        if (e2<=sy){
            y0++;
            y1--;
            error+=sy+=a;
        }
        if (e2>=sx || 2*error>sy){
            x0++;
            x1--;
            error+=sx+=b1;
        }
    } while (x0<=x1);

    while (y0-y1<b){
        rotate(x0-1,y0);
        rotate(x1+1,y0);
        y0++;
        rotate(x0-1,y1);
        rotate(x1+1,y1);
        y1--;
    }

}
void Graphics::fill_oval(Point middle, double width, double height)
{
    double x=middle.x();
    double y=middle.y();;
    center.set(x,y);
    width/=2;
    height/=2;
    for (int i=x-width; i<=x+width; i++){
        for (int j=y-height; j<=y+height; j++){
            if ((i-x)*(i-x)*height*height+(j-y)*(j-y)*width*width<height*height*width*width){
                draw(i,j);
            }
        }
    }
}
void Graphics::fill_oval(Point middle, double width, double height, int degrees)
{
    double x=middle.x();
    double y=middle.y();;
    rotation=degrees_to_rad(degrees);
    center.set(x,y);
    width/=2;
    height/=2;
    for (int i=x-width-height; i<=x+width+height; i++){
        for (int j=y-width-height; j<=y+width+height; j++){
            if (((i-x)*1.00*cos(rotation)+(j-y)*1.0*sin(rotation))*
                ((i-x)*1.00*cos(rotation)+(j-y)*1.0*sin(rotation))*height*height
              +(((i-x)*1.00*sin(rotation)-(j-y)*1.0*cos(rotation))*
                ((i-x)*1.00*sin(rotation)-(j-y)*1.0*cos(rotation))*width*width)<height*height*width*width){
                draw(i,j);
            }
        }
    }
}
void Graphics::draw_line(Point initial, Point later)
{
    double x0=initial.x();
    double y0=initial.y();
    double x1=later.x();

    double y1=later.y();
    center.set((x0+x1)/2,(y0+y1)/2);
    if (x0>x1){
        int copy=x0;
        x0=x1;
        x1=copy;
    }
    if (y0>y1){
        int copy=y0;
        y0=y1;
        y1=copy;
    }
    double deltaX=x1-x0;
    double deltaY=y1-y0;
    double slope=abs(deltaY/deltaX);
    double error=slope-0.5;
    int sy=y0;
    if (deltaX==0){
        for (int i=y0; i<=y1; i++){
            draw(x0,i);
        }
    }
    else if (deltaY==0){
        for (int i=x0; i<=x1; i++){
            draw(i,sy);
        }
    }
    else{
        if (slope>=1){
            for (double i=x0; i<=x1; i+=1/slope){
                draw(i,sy);
                error+=1;
                if (error>=0.5){
                    sy+=1;
                    error-=1/slope;
                }
            }
        }
        else{
            for (double i=x0; i<=x1; i+=1){
                draw(i,sy);
                error+=slope;
                if (error>=0.5){
                    sy+=1;
                    error-=1;
                }
            }
        }
    }
}
void Graphics::draw_line(Point initial, Point later, int degrees)
{
    rotation=degrees_to_rad(degrees);
    double x0=initial.x();
    double y0=initial.y();
    double x1=later.x();
    double y1=later.y();
    if (x0>x1){
        double copy=x0;
        x0=x1;
        x1=copy;
    }
    if (y0>y1){
        double copy=y0;
        y0=y1;
        y1=copy;
    }
    double deltaX=1.0*x1-x0;
    double deltaY=1.0*y1-y0;
    double slope=1.0*deltaY/deltaX;
    double error=slope-0.5;
    double y=y0*1.0;
    if (deltaX==0){
        for (int i=y0; i<=y1; i++){
            rotate(x0,i);
        }
    }
    else if (deltaY==0){
        for (int i=x0; i<=x1; i++){
            rotate(i,y);
        }
    }
    else{
        if (slope<=-1){
            for (double i=x1; i<=x0; i-=1/slope){
                rotate(i,y);
                error+=1;
                if (error>=0.5){
                    y+=1;
                    error-=1/slope;
                }
            }
        }
        else if (slope>=1){
            for (double i=x0; i<=x1; i+=1/slope){
                rotate(i,y);
                error+=1;
                if (error>=0.5){
                    y+=1;
                    error-=1/slope;
                }
            }
        }
        else{
            for (double i=x0; i<=x1; i+=1){
                rotate(i,y);
                error+=slope;
                if (error>=0.5){
                    y+=1;
                    error-=1;
                }
            }
        }
    }
}
void Graphics::draw_rect(Point upleft, int width, int height)
{
    double x=upleft.x();
    double y=upleft.y();
    center.set(x+width/2,y+height/2);
    draw_line(Point(x,y),Point(x+width,y));
    draw_line(Point(x+width,y),Point(x+width,y+height));
    draw_line(Point(x,y+height),Point(x+width,y+height));
    draw_line(Point(x,y),Point(x,y+height));
}
void Graphics::draw_rect(Point upleft, int width, int height, int degrees) // INCOMPLETE
{
    double x=upleft.x();
    double y=upleft.y();
    rotation=degrees_to_rad(degrees);
    center.set(x+width/2,y+height/2);
    draw_line(Point(x,y),Point(x+width,y), degrees);
    draw_line(Point(x+width,y),Point(x+width,y+height), degrees);
    draw_line(Point(x,y+height),Point(x+width,y+height), degrees);
    draw_line(Point(x,y),Point(x,y+height), degrees);
}
void Graphics::fill_rect(Point upleft, int width, int height)
{
    double x=upleft.x();
    double y=upleft.y();
    center.set(x+width/2,y+height/2);
    for (int i=x; i<x+width; i++){
        for (int j=y; j<y+height; j++){
            draw(i,j);
        }
    }
}
void Graphics::fill_rect(Point upleft, int width, int height, int degrees)
{
    double x=upleft.x();
    double y=upleft.y();
    center.set(x+width/2,y+height/2);
    for (double i=x; i<x+width; i+=0.5){
        for (double j=y; j<y+height; j+=0.5){
            rotate(i,j);// draw(i,j);
        }
    }
}
void Graphics::fill_border(int xpixels, int ypixels)
{
    center.set(px/2,py/2);
    for (int j=0; j<py; j++){
        for (int i=0; i<=xpixels; i++){
             draw(i,j);
        }
        for (int i=px-xpixels-1; i<px; i++){
             draw(i,j);
        }
    }
    for (int i=0; i<px; i++){
        for (int j=0; j<=ypixels; j++){
             draw(i,j);
        }
        for (int j=py-ypixels-1; j<py; j++){
             draw(i,j);
        }
    }
}
void Graphics::draw_boat(Point middle, double height, double base, double width_mast, double depth, double degrees, Color ofboat, Color ofmast)
{
    int degree=(int)degrees;
    int degreecopy=degree%360;
    /*    if (degreecopy>=30 && degreecopy<90){
        double alternate=degree-30;
        degrees=degrees-2*alternate;
    }
    else if ((degreecopy>=90 && degreecopy<150) || (degreecopy>=210 && degreecopy<270) || (degreecopy>=330 && degreecopy<360)){
        double alternate=-30-degrees;
        degrees=degrees+2*alternate;
    }
    else if (degreecopy>=150 && degreecopy<210){
        double alternate=degree-150;
        degrees=degrees-2*alternate;
    }
    else if (degreecopy>=270 && degreecopy<330){
        double alternate=degree-270;
        degrees=degrees-2*alternate;
    }
    */
    for (int i=30; i<degreecopy; i+=9999){
        double alternate=degree-30;
        degrees=degrees-2*alternate;
    }
    for (int i=90; i<degreecopy; i+=9999){
        double alternate=-30-degrees;
        degrees=degrees+2*alternate;
    }
    for (int i=150; i<degreecopy; i+=9999){
        double alternate=degree-150;
        degrees=degrees-2*alternate;
    }
    for (int i=210; i<degreecopy ; i+=9999){
        double alternate=-30-degrees;
        degrees=degrees+2*alternate;
    }
    for (int i=270; i<degreecopy; i+=9999){
        double alternate=degree-270;
        degrees=degrees-2*alternate;
    }
    for (int i=330; i<degreecopy; i+=9999){
        double alternate=-30-degrees;
        degrees=degrees+2*alternate;
    }
    double x=middle.x();
    double y=middle.y();
    center.set(x,y);
    rotation=degrees_to_rad(degrees);
    double xmax=middle.x()+base/2.0;
    double xmin=middle.x()-base/2.0;
    double ymin=middle.y()-depth;
    vector<Point> vect;
    double multiplier=(depth)/(0.25*base*base);
    for (double i=-base/2; i<base/2; i+=0.2){
        Point os=Point(i,-multiplier*i*i+depth);
        os.translate(x,y);
        vect.push_back(os);
    }
    current.set(ofboat);
    for (int i=0; i<vect.size(); i++){
        rotate(vect[i].x(),vect[i].y());
    }
    for (int i=xmin; i<xmax; i++){
        rotate(i,middle.y());
    }
    int g=0;
    for (double i=xmin; i<xmax; i+=0.2){
        for (int k=middle.y(); k<vect[g].y()-0.2; k++){
            rotate(i,k);
        }
        g++;
    }
    current.set(ofmast);
    for (double i=middle.y(); i>middle.y()-height; i-=0.2){
        rotate(middle.x(),i);
    }
    for (double i=middle.x(); i<middle.x()+width_mast; i+=0.2){
        rotate(i,middle.y()-height/2);
    }
    vector<Point> slant;
    for (double i=0; i<width_mast; i+=0.2){
        Point os=Point(i,-(i*(-height/2.00)/width_mast)-(height/2.00));
        os.translate(x,y-height/2);
        slant.push_back(os);
    }
    int p=0;
    for (double i=middle.x(); i<middle.x()+width_mast; i+=0.2){
        for (double k=middle.y()-height/2; k>slant[p].y()-0.2; k-=0.2){
            rotate(i,k);
        }
        p++;
    }
}

void Graphics::set_rain(int cloudnumber, double percentage, int sizethreshold, double speed, Color color0, double rainthreshold)
{
    Point midpoint=cloudlocation[cloudnumber].get_middle();
    int widh=cloudlocation[cloudnumber].get_width();
    int heigh=cloudlocation[cloudnumber].get_height();
    int wid=widh;
    int heig=heigh;
    if (widh*heigh>rainthreshold){
        int radius=0;
        do {
              rainthreshold=rainthreshold*sizethreshold;
              radius++;
        }
        while (widh*heigh>rainthreshold);
        int xmax=midpoint.x()+widh/2.0;
        int xmin=midpoint.x()-widh/2.0;
        int ymax=midpoint.y()+heigh/2.0;
        int ymin=midpoint.y()-heigh/2.0;
        int range2=ymax-ymin;
        int range=xmax-xmin;
        int numraindrops=sqrt(heigh)/radius*round((0.01*percentage*range)/(radius*2));
        for (int i=0; i<numraindrops; i++){
            Rain item=Rain(radius,Point(rand()%range+xmin,rand()%range2+ymin),speed,color0);
            newrain.push_back(item);
        }
    }

}
void Graphics::add_rain(Rain att)
{
    rainlocation.push_back(att);
}
vector<Rain> Graphics::get_rain()
{
    for (int i=0; i<newrain.size(); i++){
        Point cent=newrain[i].pointy();
    }
    return newrain;
}
void Graphics::draw_rain()
{
    for (int i=0; i<rainlocation.size(); i++)
    {
        Point cvt=rainlocation[i].pointy();
        current.set(0,0,0);
        fill_circle(rainlocation[i].get_radius(),cvt);
        current.set(rainlocation[i].get_color());
        fill_circle(rainlocation[i].get_radius(),cvt);
    }
}
void Graphics::setup_clouds(int numberofclouds)
{
    cloudlocation=new Cloud[numberofclouds+1];
    cloudnumber=numberofclouds;
}
void Graphics::set_cloud(int cloudnumber, int numellipse, double wind, Point middle, int width, int height, Color cloud)
{
    cloudlocation[cloudnumber].set_cloud(wind,middle.x(),middle.y(),width,height,cloud);
    cloudlocation[cloudnumber].set_ellipses(numellipse);
}
void Graphics::set_cloud(int cloudnumber, double wind, Point middle, int width, int height, Color cloud, vector<Point> copy, double factor)
{
    cloudlocation[cloudnumber].set_cloud(wind,middle.x(),middle.y(),width,height,cloud);
    for (int i=0; i<copy.size(); i++){
       copy[i].factor(factor);
    }
    cloudlocation[cloudnumber].keep_ellipses(copy.size(), copy);
}
void Graphics::draw_cloud(int cloudnumbers, Point middle)
{
    if (cloudnumbers>999){
    }
    else{
        int radii=sqrt(cloudlocation[cloudnumber].get_width()*cloudlocation[cloudnumber].get_height())/2;
        if (radii<1){
            return;
        }
        canvas_color(cloudlocation[cloudnumber].get_color());
        vector<Point> list=cloudlocation[cloudnumber].get_ellipses();
        for (int i=0; i<list.size(); i++){

            fill_circle(radii,Point(list[i].x()+middle.x(),list[i].y()+middle.y()));
        }
    }
}
void Graphics::draw_cloud(int cloudnumbers)
{
      int radii=sqrt(cloudlocation[cloudnumbers].get_width()*cloudlocation[cloudnumber].get_height())/2;
        double area=0;
        for (int i=1; i<=cloudnumbers; i++){
            Point mid=cloudlocation[i].get_middle();
            double xnegative=0;
            double ynegative=0;
            double width=cloudlocation[i].get_width();
            double height=cloudlocation[i].get_height();
            area+=width*height;
        }
        Color ost=cloudlocation[cloudnumbers].get_color();
        int red=ost.get_r();
        int green=ost.get_g();
        int blue=ost.get_b();
        double percentage=80.00*area/(px*py);
        Point middle=cloudlocation[cloudnumbers].get_middle();
        if (red-percentage>5 && green-percentage>5 && blue-percentage>5){
            canvas_color(red-percentage,green-percentage,blue-percentage);
        }
        else{
            canvas_color(10,10,10);
        }
        vector<Point> list=cloudlocation[cloudnumbers].get_ellipses();
        for (int i=0; i<list.size(); i++){
            fill_circle(radii,Point(list[i].x()+middle.x(),list[i].y()+middle.y()));
        }
}
void Graphics::cloud_shape(int cloudnumber, int numellipse, vector<Point> opt, double factor)
{
    for (int i=0; i<opt.capacity(); i++){
        opt[i].factor(factor);
    }
    cloudlocation[cloudnumber].keep_ellipses(numellipse, opt);
}
    // Get cloud shape
vector<Point> Graphics::get_cloud(int cloudnumber)
{
    return cloudlocation[cloudnumber].get_ellipses();
}

void Graphics::draw_sun(Point middle, double radius, Color suncol)
{
    double x=middle.x();
    double y=middle.y();
	canvas_color(suncol);
	draw_circle(radius,middle);
	fill_circle(radius,middle);
	for (int i=0; i <= 20; i++)
	{
		//draws rays a quarter radius long a quarter radius away from the circle 18 degrees apart from each other
		draw_line( Point(x + 5*radius/4, y+ 5*radius/4) , Point(x + 3*radius/2  , y + 3*radius/2) , i * 18);
	}
}

// wave equation is y = height*sin(k*x0+ k*width)
void Graphics::draw_wave(double height, double width, double period, Point middle, Color wave)
{
    current.set(wave);
	double k = 2.00*3.1415/ width;
    vector<Point> venter;
    for(double i =0.0; i<px;i+=0.1)
    {
        Point os=Point(1.0*i,1.0*height*sin(k*i+ k*width+2.00*M_PI*period)+middle.y());
        venter.push_back(os);
    }
    for (int i=0;i<venter.size()-1; i++)
    {
        if (venter[i].y()>middle.y()-height){
            draw(venter[i].x(),venter[i].y());
        }
    }
    for (int i=0; i<px; i++)
    {
        for (int j=py; j>venter[i*10].y(); j--)
        {
            draw(i,j);
        }
    }
}
//Tornados resemble a parametric sine wave
//Therefore they can be modeled by the equations
//x=(|t|/a) * sin((t)/10.0 ) and y = (t/10.0) * sin(8-a)/3.0
//a is a factor affecting shape of the wave, where as "a" approaches 8
//the shape approaches a line

void Graphics::draw_Tornado(double height, double width, double amplitude, double period, Point middle, Color tornado)
{
    current.set(tornado);
    vector<Point> tenter;
    for(double i =0.0; i<px;i+=0.02)
    {
        Point os=Point(1.00*width*(abs(i)/amplitude) * sin((i)/10.0 +2.00*M_PI*period),1.0*height*(i/10.0) * sin(8.0-amplitude)/3.0);
        tenter.push_back(os);
    }
    for (int i=0;i<tenter.size()-1; i++)
    {

            draw(tenter[i].x()+middle.x(),tenter[i].y()+middle.y());

    }

}
Color** Graphics::get_canvas() const
{
    return canvas;
}

