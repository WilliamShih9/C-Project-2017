#include <cmath>
using namespace std;
#ifndef COLOR_H
#define COLOR_H


class Color
{
    public:
    Color();
    Color(unsigned char red, unsigned char green, unsigned char blue);
    void set(unsigned char red, unsigned char green, unsigned char blue);
    void set(Color complete);
    void set_r(unsigned char red);
    void set_g(unsigned char green);
    void set_b(unsigned char blue);
    Color get() const;
    unsigned char get_r() const;
    unsigned char get_g() const;
    unsigned char get_b() const;
    private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


#endif

Color::Color()
{
    r=0;
    g=0;
    b=0;
}
Color::Color(unsigned char red, unsigned char green, unsigned char blue)
{
    r=red;
    g=green;
    b=blue;
}


void Color::set(unsigned char red, unsigned char green, unsigned char blue)
{
    r=red;
    g=green;
    b=blue;
}
void Color::set(Color complete)
{
    r=complete.r;
    g=complete.g;
    b=complete.b;
}

void Color::set_r(unsigned char red)
{
	r=red;
}
void Color::set_g(unsigned char green)
{
	g=green;
}
void Color::set_b(unsigned char blue)
{
	b=blue;
}
Color Color::get() const
{
    return Color(r,g,b);
}
unsigned char Color::get_r() const
{
	return r;
}
unsigned char Color::get_g() const
{
	return g;
}
unsigned char Color::get_b() const
{
	return b;
}	
