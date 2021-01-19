#ifndef POINT_H
#define POINT_H

class Point
{
    public:
    Point();
    Point(double px, double py);
    void set(double px, double py);
    void set(Point middle);
    double x();
    double y();
    Point translate(double px, double py);
    Point get_point();
    void factor(double value);
    private:
    double x0;
    double y0;
};

#endif




Point::Point()
{
    x0=0.0;
    y0=0.0;
}
Point::Point(double px, double py)
{
    x0=1.0*px;
    y0=1.0*py;
}
void Point::set(double px, double py)
{
    x0=1.0*px;
    y0=1.0*py;
}
void Point::set(Point middle)
{
    x0=1.0*middle.x();
    y0=1.0*middle.y();
}
double Point::x()
{
    return x0;
}
double Point::y()
{
    return y0;
}
Point Point::translate(double px, double py)
{
    x0+=px;
    y0+=py;
    return Point(x0,y0);
}
Point Point::get_point()
{
    return Point(x0,y0);
}
void Point::factor(double value)
{
    x0=x0*value;
    y0=y0*value;
}