//PRELIMINARY CLASS
// Angle is in radians
// Speed is in pixels per second

#ifndef WIND_H
#define WIND_H

class Wind
{
	public:
	Wind();
	Wind(double speed, double angle);
	void set_wind(double speed, double angle);
	void set_speed(double speed);
	void set_angle(double angle);
	double get_speed();
	double get_angle();
	private:
	double spd;
	double ang;
};
#endif

Wind::Wind()
{
	spd=0;
	ang=0;
}

Wind::Wind(double speed, double angle)
{
	spd=speed;
	ang=angle;
}
void Wind::set_wind(double speed, double angle)
{
	spd=speed;
	ang=angle;
}
void Wind::set_speed(double speed)
{
	spd=speed;
}
void Wind::set_angle(double angle)
{
	ang=angle;
}
double Wind::get_angle()
{
	return ang;
}
double Wind::get_speed()
{
	return spd;
}
