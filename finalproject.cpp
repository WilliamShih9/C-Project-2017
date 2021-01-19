// William Shih Period 4
// CS-102, Fall 2016
// Final Animation Project

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ios>
#include <ctime>
#include "Configuration.h"
#include "Graphics.h"


// class Configuration reads the config_file.txt
// class Color has a variable for red, green, and blue (values 0-255)

using namespace std;
//--------------------------------------------------------------
// List of Functions
// Returns the value of the variable with a certain string name
double check(string variable, vector<Configuration> list);
// Converts a double to an integer
int to_int(double floating);
// Creates a vector of Configuration from the configuration file
vector<Configuration> create_list(ifstream& infile);
// Writes the output name for the BMP file
void write_bmp_header_file(ofstream& output_file, int px, int pz);
// Creates the BMP file from the Graphics object
void write_bmp_file(int f_number, string output_file_name, Graphics g, int px, int pz);
// Creates a frame number
string int_to_five_digit_string(int frame_number);
// Testing purposes
void test(int number);
string int_to_res(int first, int second);
// Creates a string for the resolution based on the width and height of the frame
// Converts an integer to a string
string int_to_string(int number);
// Creates a cloud color based on configuration file details
Color create_cloud_color(vector<Configuration> list);
// Creates a cloud at initial point on initial frame, moving linearly to final point on final frame, with an initial width and final width, increasing by size factor linearly
void cloudinterval(int ellipses, int cloudnumber, int iframe, int fframe, Point ipoint, Point fpoint, int iwidth, int iheight, int factor, vector<Configuration> list, Graphics g[]);
// Draws rain from initial to final frame based on the clouds of that frame, width and height of frame must be also inserted
void drawrain(int iframe, int fframe, Graphics g[], int px, int py, vector<double> rainspeed);
// Returns the color of the ship
Color shipcolor(vector<Configuration> list);
// Returns the color of the mast
Color mastcolor(vector<Configuration> list);
// Returns the color of the rain
Color raincolor(vector<Configuration> list);
// Returns the color of the sky
Color skycolor(vector<Configuration> list);
// Returns the color of the sun
Color suncolor(vector<Configuration> list);
// Returns the color of the ocean
Color oceancolor(vector<Configuration> list);
// Returns the point of cloud formation
Point cloudspawn(vector<Configuration> list);
// Returns the point of cloud dissipation
Point cloudfinal(vector<Configuration> list);
// Returns a vector with two values: the width and height of the cloud
vector<double> cloudwidthheight(double cloudfactor, vector<Configuration> list);
// Retunrs a vector with the values of the wind
vector<double> getwind(vector<Configuration> list);
// Returns the points of the where the sun is located on each frame
vector<Point> sunpoints(vector<Configuration> list);
// End List of Functions
//--------------------------------------------------------------
int main (int argc, char* argv[])
{

    srand(time(NULL));
    ifstream infile;
    // argv[1] should be config_file.txt
    infile.open(argv[1]);
    if (!infile.is_open()){
        cout << "Can't open configuration file: " << argv[1] << endl;
        return 0;
    }
    cout << "Below are list of configuration variables. " << endl;
	vector<Configuration> list;
	list=create_list(infile);
	int xaxis=to_int(check("xaxis",list));
    int yaxis=to_int(check("yaxis",list));
    if (xaxis<=5 || yaxis<=5) {
        cout << "xaxis or yaxis is set to a invalid low number (below 5): x=" << xaxis << " and y= " << yaxis << endl;
        return 0;
    }
    int frames=to_int(check("frames",list))+1;
    int framesper=to_int(check("framespersecond",list));
    int clouds=to_int(check("numberofclouds",list));
    Graphics* g=new Graphics[frames];
    for (int i=0; i<frames; i++){
        g[i].set(xaxis,yaxis);
        g[i].setup_clouds(clouds);
    }
    int minwind=to_int(check("initialwind",list));
    int maxwind=to_int(check("maxwind",list));
    vector<double> windrate;
    windrate=getwind(list);
    double initialwave=1.0*check("initwaveheight",list);
    double finalwave=1.0*check("finalwaveheight",list);
    double iboat=xaxis*0.01*to_int(check("boatinitialx",list));
    double fboat=xaxis*0.01*to_int(check("boatfinalx",list));
    double rangelol=fboat-iboat;
    double boatincrement=1.00*rangelol/frames;
    double range=1.00*finalwave-initialwave;
    double wincrement=1.00*range/frames;
    double factor=1.0*check("waveperiodfactor",list);
    double maxfactor=1.0*check("waveperiodmaxfactor",list);
    double factorrange=maxfactor-factor;
    double factorincrement=1.00*factorrange/frames;
    double darknessfactor=1.0*check("skydarknessfactor",list);
    for (int i=1; i<frames; i++) {
        g[i].full_color(255,255,255);
        if (i==-1){
            int mincircles=to_int(check("mincirclespercloud",list));
            int maxcircles=to_int(check("maxcirclespercloud",list));
            int range=maxcircles-mincircles;
            double cloudfactor=check("cloudfactor",list);
            vector<double> two;
            two=cloudwidthheight(cloudfactor,list);
            vector<Point> suns;
            suns=sunpoints(list);
            // Creates a cloud at initial point on initial frame, moving linearly to final point on final frame, with an initial width and final width, increasing by size factor linearly
            // void cloudinterval(int ellipses, int cloudnumber, int iframe,
            // int fframe, Point ipoint, Point fpoint, int iwidth, int fwidth,
            // int factor, vector<Configuration> list, Graphics g[]);
            for (int k=1; k<=clouds; k++){
                cloudinterval(rand()%range+mincircles,k,2,frames/3,cloudspawn(list),cloudfinal(list),1,1,2.00*sqrt(two[0]*two[1]),list,g);
                 cloudinterval(rand()%range+mincircles,k,frames/3,2*frames/3,cloudspawn(list),cloudfinal(list),two[0],two[1],cloudfactor,list,g);
                 cloudinterval(rand()%range+mincircles,k,2*frames/3,frames-1,Point(-xaxis/2,yaxis/4),cloudfinal(list),5*two[0],two[1],1,list,g);
            }
            for (int p=1; p<frames; p++){
                g[p].set_sky(skycolor(list),clouds,darknessfactor);
            }
            for (int s=1; s<frames; s++){
                g[s].draw_sun(suns[s-1],to_int(check("sunradius",list)),suncolor(list));
            }
        }
        int minrainpct=to_int(check("minrainpercentage",list));
        int maxrainpct=to_int(check("maxrainpercetnage",list));
        int range=maxrainpct-minrainpct;
        if (i==-1) {
            for (int k=1; k<frames; k++){
                for (int j=1; j<=clouds; j++){
                    g[k].set_rain(j,rand()%range+minrainpct,to_int(check("sizethreshold",list)),to_int(check("rainspeed",list)),raincolor(list),to_int(check("rainthreshold",list)));
                }
            }
            drawrain(0,frames,g,xaxis,yaxis,windrate);
            cout << "Rain done!" << endl;
        }
        /* for (int j=1; j<=clouds; j++){
            g[i].draw_cloud(j);
        }*/
        g[i].draw_wave(initialwave+i*wincrement,to_int(check("wavewidth",list)),factor*i/framesper,Point(i,(yaxis)*(1.00-(check("wavetoyaxisratio",list)))),oceancolor(list));
        g[i].draw_boat(Point(iboat+i*boatincrement,(yaxis)*(1.00-(check("wavetoyaxisratio",list)))),to_int(check("shipheight",list)),to_int(check("shipwidth",list)),to_int(check("shipwidthmast",list)),to_int(check("shipdepth",list)),i*4*pow(factor,2)*180/3.1415*(2.00*3.1415/320),shipcolor(list),mastcolor(list));
        g[i].draw_Tornado(3.00*i/frames,3.00*i/frames,10.00,3.00, Point(500,500),Color(0,0,0));
        cout << "Frame " << i << " calculated..." << endl;
        factor+=factorincrement;
    }
    cout << "Frames successfully completed. " << endl;
    for (int i=1; i<frames; i++){
        write_bmp_file(i, "weatherproject.bmp", g[i], xaxis, yaxis);
    }
    string resolution=int_to_res(xaxis,yaxis);
    cout << "Copy and paste the three lines below to create animation. Must have ffmpeg and mogrify avaiable: " << endl;
    cout << "cd BMPFolder" << endl;
    cout << "mogrify -format jpeg *.bmp" << endl;
  //  cout << "mogrify -format jpeg *.bmp" << endl;
    string framerate=int_to_string(framesper);
    cout << "ffmpeg -framerate "+framerate+" -i %05dweatherproject.bmp -s:v "+resolution+" -c:v libx264 -profile:v high -crf 18 -pix_fmt yuv420p weatheranimation.mp4" << endl;
    delete[] g;
    g=NULL;
}


//-----------------------------------------------

double check(string variable, vector<Configuration> list)
{
	for (int i=0; i<list.size(); i++) {
		if (list[i].get_name()==variable) {
			return list[i].get_value();
		}
	}
	return 0;
}
int to_int(double floating)
{
    return (int)(floating+0.5);
}

vector<Configuration> create_list(ifstream& infile)
{
    vector <Configuration> list;
    while (infile) {
        string a;
        if (!getline(infile,a)){
            break;
        }
        istringstream next(a);
        // Add the instructions
        string number="";
        string nam="";
	    for (int i=0; i<a.length(); i++){
            if (isalpha(a[i])){
                nam+=a[i];
            }
            if (isdigit(a[i]) || ispunct(a[i])){
                number+=a[i];
            }
        }
        double val=string_to_double(number);
        cout << nam << " : " << val << endl;
        Configuration okay(nam,val);
        list.push_back(okay);
    }
    return list;
}
void write_bmp_header_file(ofstream& output_file, int px, int pz)
{
	unsigned short int bfType;
	bfType = 0x4D42;
   output_file.write ((char*)&bfType, sizeof (short int));

   unsigned int bfSize;
	int rem;
	rem=3*px%4;
	int padding;
	if(rem==0){
		padding=0;
	}
	else{
		padding=4-rem;
	}

	bfSize = 14 + 40 + (3 * px+padding) * pz;
//	bfSize = 14 + 40 + (3 * px+padding) * pz + 2;
   output_file.write ((char*)&bfSize, sizeof (int));

    unsigned short int bfReserved1;
	bfReserved1 = 0;
   output_file.write ((char*)&bfReserved1, sizeof (short int));

	unsigned short int bfReserved2;
	bfReserved2 = 0;
   output_file .write ((char*)&bfReserved2, sizeof (short int));

	unsigned int bfOffsetBits;
	bfOffsetBits = 14 + 40;
   output_file.write ((char*)&bfOffsetBits, sizeof (int));

	unsigned int biSize;
	biSize=40;
   output_file.write ((char*)&biSize, sizeof (int));

	int biWidth;
	biWidth=px;
   output_file.write ((char*)&biWidth, sizeof (int));

	int biHeight;
	biHeight=pz;
   output_file.write ((char*)&biHeight, sizeof (int));

	unsigned short int biPlanes;
	biPlanes=1;
   output_file.write ((char*)&biPlanes, sizeof (short int));

	unsigned short int biBitCount;
	biBitCount=24;
   output_file.write ((char*)&biBitCount, sizeof (short int));

	unsigned int biCompression;
// #define BI_RGB 0
   unsigned int bi_rgb = 0;
//	biCompression=BI_RGB;
	biCompression=bi_rgb;
   output_file.write ((char*)&biCompression, sizeof (int));

	unsigned int biSizeImage;
	biSizeImage=0;
   output_file.write ((char*)&biSizeImage, sizeof (int));

	unsigned int biXPelsPerMeter;
	biXPelsPerMeter=0;
   output_file.write ((char*)&biXPelsPerMeter, sizeof (int));

	unsigned int biYPelsPerMeter;
	biYPelsPerMeter=0;
   output_file.write ((char*)&biYPelsPerMeter, sizeof (int));

	unsigned int biClrUsed;
	biClrUsed = 0;
   output_file.write ((char*)&biClrUsed, sizeof (int));

	unsigned int biClrImportant;
	biClrImportant = 0;
   output_file.write ((char*)&biClrImportant, sizeof (int));
}
void write_bmp_file(int f_number, string output_file_name, Graphics g, int px, int pz)
{
   ofstream ostrm_1;
   string o_file_name ="./BMPFolder/"+int_to_five_digit_string(f_number)+output_file_name;
   ostrm_1.open(o_file_name.c_str(), ios::out | ios::binary);
   istream::iostate word=ostrm_1.rdstate();
    if(word & ios::failbit){
    cout<<"Failbit flag is set. ";
    }
   if(ostrm_1.fail()){
      cout << "Error.  Can't open output file " << o_file_name << "." << endl;
      return;
   }
   cout << "Opening output file " << o_file_name <<"." << endl;

	int rem;
	rem=3*px%4;
	int padding;
	if(rem==0){
		padding=0;
	}
	else {
		padding=4-rem;
	}
   //cout << "padding is " << padding << "." << endl;
    //cout << "rem is "  << rem << "." << endl;
   write_bmp_header_file(ostrm_1, px, pz);

	unsigned char p_buffer[4];
	p_buffer[0]=0;
	p_buffer[1]=0;
	p_buffer[2]=0;
	p_buffer[3]=0;

   unsigned char * line_buffer = new unsigned char[px*3];

   int i;
   int j;
   Color** canvas=g.get_canvas();
   for (i=pz-1;i>=0;i--){
      for (j=0;j<px;j++){
         line_buffer[3*j+0]=canvas[j][i].get_b();
         line_buffer[3*j+1]=canvas[j][i].get_g();
         line_buffer[3*j+2]=canvas[j][i].get_r();
      }
      ostrm_1.write ((char*)line_buffer, px*3*sizeof (unsigned char));
      ostrm_1.write ((char*)p_buffer, padding*sizeof (unsigned char));
   }
   delete[] line_buffer;
   line_buffer = NULL;
   ostrm_1.close();
}
string int_to_five_digit_string(int frame_number)
{
   ostringstream strm;
   strm << setfill('0') << setw(5) << frame_number;
   return strm.str();
}
void test(int number)
{
    cout << "Check " << number << endl;
}
string int_to_res(int first, int second)
{
    stringstream ss;
    ss << first;
    string str1=ss.str();
    stringstream s;
    s << second;
    string str2=s.str();
    string resolution=str1+"x"+str2;
    return resolution;
}
string int_to_string(int number)
{
    stringstream ss;
    ss << number;
    string str1=ss.str();
    return str1;
}
Color create_cloud_color(vector<Configuration> list)
{
    int redmin=to_int(check("cloudrmin",list));
    int redmax=to_int(check("cloudrmax",list));
    int bluemin=to_int(check("cloudbmin",list));
    int bluemax=to_int(check("cloudbmax",list));
    int greenmin=to_int(check("cloudgmin",list));
    int greenmax=to_int(check("cloudgmax",list));
    int red=redmax-redmin;
    int green=greenmax-greenmin;
    int blue=bluemax-bluemin;
    return Color(rand()%red+redmin,rand()%green+greenmin,rand()%blue+bluemin);
}
void cloudinterval(int ellipses, int cloudnumber, int iframe, int fframe, Point ipoint, Point fpoint, int iwidth, int iheight, int factor, vector<Configuration> list, Graphics g[])
{
    Color okay=create_cloud_color(list);
    int framedif=fframe-iframe;
    int yinitial=ipoint.y();
    int yfinal=fpoint.y();
    int xinitial=ipoint.x();
    int xfinal=fpoint.x();
    double xincrement=(xfinal-xinitial)*1.0/framedif;
    double yincrement=(yfinal-yinitial)*1.0/framedif;
    double heightincrement=((factor-1.0)*iheight*1.0)/framedif;
    double widthincrement=((factor-1.0)*iwidth*1.0)/framedif;
    double factorincrement=(factor-1.0)/framedif;
    g[0].set_cloud(cloudnumber,ellipses,0,Point(0,0),iwidth*factor,iheight*factor,okay);
    vector<Point> current=g[0].get_cloud(cloudnumber);
    int t=0;
    for (int i=iframe; i<=fframe; i++){
        g[i].set_cloud(cloudnumber,0,Point(xinitial+t*xincrement,yinitial+t*yincrement),
        iwidth+t*widthincrement,iheight+t*heightincrement,okay,current,(1.00+t*factorincrement)/factor);
        t++;
    }
}
void drawrain(int iframe, int fframe, Graphics g[], int px, int py, vector<double> windrate)
{
    vector<Point> raingetting;
    for (int i=iframe; i<fframe; i++) {
        vector<Rain> raining=g[i].get_rain();
        for (int k=i; k<fframe; k++){
            for (int j=0; j<raining.size(); j++) {
                Point middle1=raining[j].pointy();
                if ((middle1.y()>py && middle1.x()>px) || (middle1.y()<0 && middle1.x()<0)) break;
                Rain getting=raining[j].transform(windrate[i]);
                Point middle2=getting.pointy();
                if (middle2.y()<py && middle2.x()<px && middle2.y()>0 && middle2.x()>0){
                     g[k].add_rain(getting);
                }
            }
        }
    }
    for (int i=iframe; i<fframe; i++){
        g[i].draw_rain();
    }
}
Color shipcolor(vector<Configuration> list)
{
    int red=to_int(check("shipr",list));
    int green=to_int(check("shipg",list));
    int blue=to_int(check("shipb",list));
    return Color(red,green,blue);
}
Color mastcolor(vector<Configuration> list)
{
    int red=to_int(check("mastr",list));
    int green=to_int(check("mastg",list));
    int blue=to_int(check("mastb",list));
    return Color(red,green,blue);
}
Color raincolor(vector<Configuration> list)
{
    int red=to_int(check("raincolorr",list));
    int green=to_int(check("raincolorg",list));
    int blue=to_int(check("raincolorb",list));
    return Color(red,green,blue);
}
Color skycolor(vector<Configuration> list)
{
    int red=to_int(check("skycolorr",list));
    int green=to_int(check("skycolorg",list));
    int blue=to_int(check("skycolorb",list));
    return Color(red,green,blue);
}
Color oceancolor(vector<Configuration> list)
{
    int red=to_int(check("oceanr",list));
    int green=to_int(check("oceang",list));
    int blue=to_int(check("oceanb",list));
    return Color(red,green,blue);
}
Color suncolor(vector<Configuration> list)
{
    int red=to_int(check("suncolorr",list));
    int green=to_int(check("suncolorg",list));
    int blue=to_int(check("suncolorb",list));
    return Color(red,green,blue);
}
Point cloudspawn(vector<Configuration> list)
{
    int xmin=to_int(check("cloudminxspawn",list));
    int xmax=to_int(check("cloudmaxxspawn",list));
    int xrange=xmax-xmin;
    int ymin=to_int(check("cloudminyspawn",list));
    int ymax=to_int(check("cloudmaxyspawn",list));
    int yrange=ymax-ymin;
    Point get=Point(rand()%xrange+xmin,rand()%yrange+ymin);
    return get;
}
Point cloudfinal (vector<Configuration> list)
{
    int ymin=to_int(check("cloudminyfinal",list));
    int ymax=to_int(check("cloudmaxyfinal",list));
    int xaxis=to_int(check("xaxis",list));
    int yrange=ymax-ymin;
    int xmin=xaxis*-0.2;
    int xmax=xaxis*1.2;
    int xrange=xmax-xmin;
    if (check("cloudslefttoright",list)==0)
    {
        xmin=xaxis*1.4;
        xmax=xaxis*1.7;
        xrange=xmax-xmin;
    }
    Point get=Point(rand()%xrange+xmin,rand()%yrange+ymin);
    return get;
}
vector<double> cloudwidthheight(double cloudfactor, vector<Configuration> list)
{
    int maxwidth=to_int(check("cloudmaxwidth",list));
    int maxheight=to_int(check("cloudmaxheight",list));
    double minratio=check("cloudminwidthtoheightratio",list);
    double maxratio=check("cloudmaxwidthtoheightratio",list);
    int minwidth=maxwidth/3;
    int minheight=maxheight/3;
    int widthrange=maxwidth-minwidth;
    int heightrange=maxheight-minheight;
    int height=0;
    int width=0;
    do{
        height=rand()%heightrange+minheight;
        width=rand()%widthrange+minwidth;
    }
    while (width/height<minratio && width/height>maxratio);
    vector<double> two;
    two.push_back(width/cloudfactor);
    two.push_back(height/cloudfactor);
    return two;
}
vector<double> getwind(vector<Configuration> list)
{
    int frames=to_int(check("frames",list));
    int initialwind=to_int(check("initialwind",list));
    int maxwind=to_int(check("maxwind",list));
    int range=maxwind-initialwind;
    double timeofmaxwind=check("timeofmaxwind",list);
    double timepct=timeofmaxwind*0.01;
    double midframe=timepct*frames;
    double restframe=frames-midframe;
    int finalwind=to_int(check("finalwind",list));
    vector<double> windrate;
    double positiveincrement=0;
    double negativeincrement=0;
    double pincrement=range/midframe;
    double nincrement=range/restframe;
    windrate.push_back(0);
    for (int i=1; i<midframe; i++){
        windrate.push_back(pincrement*positiveincrement);
        positiveincrement++;
    }
    for (int i=midframe; i<frames; i++){
        windrate.push_back(maxwind+nincrement*negativeincrement);
        negativeincrement--;
    }
    return windrate;
}
vector<Point> sunpoints(vector<Configuration> list)
{
    vector<Point> center;
    int frames=to_int(check("frames",list));
    double idegree=1.0*check("suninitialdegree",list);
    double fdegree=1.0*check("sunfinaldegree",list);
    double rdegree=fdegree-idegree;
    double degreeincrement=1.0*rdegree/frames;
    double radianincrement=degreeincrement*3.14159/180.000;
    double iradian=idegree*3.14159/180.00;
    double fradian=fdegree*3.14159/180.00;
    double axis=1.0*check("sundistancefromaxis",list);
    double rotx=1.0*check("sunaxisx",list);
    double roty=1.0*check("sunaxisy",list);
    for (int i=0; i<frames; i++){
        double xvalue=1.0*axis*sin(1.0*iradian+radianincrement*i*1.0)+rotx;
        double yvalue=1.0*axis*cos(1.0*iradian+radianincrement*i*1.0)+roty;
        Point form=Point(xvalue,yvalue);
        center.push_back(form);
    }
    return center;
}
