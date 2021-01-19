C++ Project

Demonstration 1: https://www.youtube.com/watch?v=RNa9RGkrOsE&feature=youtu.be

Demonstration 2: https://www.youtube.com/watch?v=jbBvDUT0DKo&feature=youtu.be

(b)
The animation consists of a simple weather simulation. The scene is an ocean environment with a boat in the foreground, clouds and rain in the background. 
The color of the rain, the clouds, the boat, the mast of the boat, the ocean, the sky, and the sun can be manipulated. The dimensions of the boat, the waves, the sun, the clouds, and the rain 
can also be manipulated as well through the configuration file. The wind can be manipulated, but for the purposes of this program, they only change the 
direction of the wind.

(c)
The algorithms in the project include the same method to create the files needed for the animation as the circle animation project with the same two methods
except that the BMP files are put into a separate folder instead. To rotate objects, mainly the boat, a rotation matrix is used for two-dimensional space.
To change the color of the sky, the area that the clouds are occupying as a percentage of the screen is calculated, and the sky is darker if the clouds are occupying a higher
percentage of space. This same technique is used for darkening clouds. For drawing rain, a certain number of raindrops is randomly formed in the space that a cloud occupies.
After forming, the coordinates of all the points that raindrops occupies later is calculated first. After moving off the screen, the raindrop is not updated to the next frame.
Then, the raindrops are drawn later. Similarly, the points for all the clouds are calculated first then later drawn. There is an array of frames used for the animation, each with a width and a height of a certain, constant number of frames.
The raindrops and clouds must be drawn on every single individual frame in a loop of some kind for them to drawn on that frame. To create clouds, a number of circles of a fixed size are 
drawn at random points in a fixed rectangle. The points of the centers of the circles are kept in a vector. The shape of the clouds is fixed and to change the shape of the clouds,
a new cloud must be created. For drawing the sun, a point of rotation is used to rotate the sun around the point at a certain angular speed. For the wind, a logistical function is used (which maxes at an angle of 45 degrees)
to determine how much the wind affects the direction of the rain.

(d)
A folder called BMPFolder must be created, in the same file where the cpp file and all of the h files are located, before running the program.                        
ffmpeg must be usable on the command-line interpretor for the animation to be created and g++ to compile the program.
To compile the program, all of the files must be present: finalproject.cpp, Cloud.h, Color.h,Configuration.h,Graphics.h,Point.h,Tornado.h,Wave.h.
The configuration file, config_file.txt, is absolutely essential to the program and it also must be typed in as a command-line argument whenever running the program.
Type in this: 

g++ -o finalproject finalproject.cpp

finalproject config_file.txt

Can be used to create JPEG files

mogrify -format jpeg *.bmp

Example with framerate of 25, resolution of 600x500:

ffmpeg -framerate 25 -i %05dweatherproject.bmp -s:v 600x500 -c:v libx264 -profile:v high -crf 18 -pix_fmt yuv420p weatheranimation.mp4

ffmpeg -framerate 25 -i %05dweatherproject.jpeg -s:v 600x500 -c:v libx264 -profile:v high -crf 18 -pix_fmt yuv420p weatheranimation.mp4

These two lines can be used to compile the program. After the program has been successfully run, there will be two lines at the end of the program 
indicating how to create the animation, which varies on the frames per second and the resolution is needed depending on the variables of the configuration file.
The first step of the two would always be to go into the BMPFolder folder, generally by inputting "cd BMPFolder". mogrify can be used to convert the large BMP files
into smaller JPEG files. The animation can be created using either the BMP files or the JPEG files but the instructions use BMP files for the animation.
The animation should be called weatherproject.mp4 if all goes well.

Warning: The program takes a very long time to run. Not well optimized. Expect up to twenty minutes for the BMP files to be successfully created.


Here is a description of all of the manipulatable variables that is located in the configuration file

frames: the total number of frames or pictures in the animation.

framespersecond: the number of frames advancing per second.

xaxis: the width of the frame

yaxis: the length or height of the frame

initialwind: the initial wind speed, an arbituary factor

maxwind: the maximum wind speed, an arbituary factor

timeofmaxwind: the percentage of frames through when the max wind speed is found

finalwind: the final wind speed for the final frame, generally increasing and decreasing at a linear rate

initwaveheight: the wave height at the initial frame

finalwaveheight: the wave height at the final frame, advancing at a linear rate

wavetoyaxisratio: the percentage of the yaxis, starting from the bottom of the frame, that the ocean occupies

wavewidth: the width of the waves

boatinitialx: the initial position of the boat on the waves, the percentage of the width of the xaxis from left to right

boatfinalx: the final position of the boat on the waves, the percentage of the width of the xaxis from left to right

shipheight: the height of the boat from the base to the top

shipwidth: the width of the boat and the base

shipdepth: the maximum distance from the base to the bottom of boat

shipwidthmast: the width of the mast on the boat

rainspeed: the speed of the rain in pixels per frame

minrainpercentage: the minimum percentage, used to describe how heavy the rain is (combined diameter of raindrops compared to width of cloud)

maxrainpercentage: the maximum percentage, used to describe how heavy the rain is (combined diameter of raindrops compared to width of cloud)

numberofclouds: the total number of clouds. Rain can heavily stack up if too many clouds are located in the same position.

mincirclespercloud: the minimum number of circles that are overlapping in a cloud

maxcirclespercloud: the maximum number of circles that are overlapping in a cloud

cloudslefttoright: whether clouds definitely move from the left to the right

cloudminxspawn: the minimum x value where clouds can spawn

cloudminyspawn: the minimum y value where clouds can spawn

cloudmaxxspawn: the maximum x value where clouds can spawn

cloudmaxyspawn: the maximum x value where clouds can spawn

cloudminyfinal: the minimum y value where clouds end up and disappear

cloudmaxyfinal: the maximum y value where clouds end up and disappear

cloudminwidthtoheightratio: the minimum allowable ratio of the cloud's width to height

cloudmaxwidthtoheightratio: the maximum allowable ratio of the cloud's width to height

cloudmaxwidth: the maximum width of the cloud, the minimum width is one-third of this

cloudmaxheight: the maximum height of the cloud, the minimum height is one-third of this

cloudfactor: how large clouds grow after forming

shipr: color of ship: red,green, and blue components

shipg:

shipb 

mastr: color of mast: red,green, and blue components

mastg 

mastb 

cloudrmin: minimum color of cloud, randomly chosen red, green, and blue components. Remains constant for each cloud. Do not make minimum and maximum values the same

cloudrmax 

cloudgmin 

cloudgmax 

cloudbmin 

cloudbmax 

rainthreshold: This is to determine the radius of the raindrops. The radius increases if the area of the cloud is rainthreshold*sizethreshold and increases by 1 more unit if area of cloud is rainthreshold*sizethreshold*sizethreshold and so on

sizethreshold: This is to determine the radius of the raindrops

raincolorr:  color of rain: red, green, and blue components

raincolorg 

raincolorb 

oceanr: color of ocean: red, green, and blue components 

oceang 

oceanb 

skycolorr  color of sky: red, green, and blue components

skycolorg

skycolorb 

skydarknessfactor a factor to determien how dark the skies when get it gets cloudy

waveperiodfactor  the minimum period, an arbituary factor

waveperiodmaxfactor the maximum period

sunradius: the radius of the sun

suncolorr: color of sun: red, green, and blue components

suncolorg

suncolorb 

suninitialdegree: the starting angle of the sun

sunfinaldegree: the final angle of the sun, advances from initial to final at linear rotational speed

sunaxisx: the axis of rotation 

sunaxisy:

sundistancefromaxis: the sun's distance from the axis of rotation 


