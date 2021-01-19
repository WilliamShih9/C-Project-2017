#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

double string_to_double(string s)
{
   istringstream strm;
   strm.str(s);
   double n=0;
   strm >> n;
   return n;
}

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration
{
    public:
    /*
        Initializes Configuration object with a name and a value
    */
    Configuration(string name,double value);
    /*
        Returns the name of the Configuration object
    */
    string get_name() const;
    /*
        Returns the value of the Configuration object
    */
    double get_value() const;
    /*
	  Finds the position of the name and returns the value in a vector
    */
    private:
    string name;
    double value;
};

#endif

Configuration::Configuration(string nam, double val)
{
	name=nam;
	value=val;
}

string Configuration::get_name() const
{
    return name;
}

double Configuration::get_value() const
{
    return value;
}

