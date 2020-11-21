/*
This is our motor and sensor setup, here we define all of our sensors, the ports that they go in,
and other adjustments that we may need such as reversing motors and setting motor ratios.

This is included in our functions file, and we use this to refer to the motors that we need to move.

The reason you'd use this over graphical:
- much quicker to see which port everything is in, and what everything is called 
- ports and other adjustments can be made much quicker
- less chance for bugs or errors out of your control
Info about a motor in graphical needs you to click on the motor, which is very slow, especially if the device isnt powerful.
These advantages are very important during competition where your port might break or other adjustments need to be made
on the spot.

Take great care to name your motors sensibly, you'll be calling them a lot, and if you forget what a motor is called,
it's a massive pain to come back and check.
*/

#include "vex.h"

/*
vex::brain/motor/inertial is object type, meaning it tells the program whether you want to define a motor,
brain, controller etc. After this is the variable name, which you will be using to refer to the device

This variable must then be assigned the object, by doing = vex::motor(...) and so on. This crates the 
device object and gives it the variable name, unless it is a brain or main controller.
*/

vex::brain god; //eg our brain is called god
vex::controller MCkun;
vex::controller SCkun = vex::controller(vex::controllerType::partner); //this is the partner controller

//eg this is our left front drive motor, you can see it is assigned vex::PORT1, meaning its in port 1
vex::motor leftF = vex::motor(vex::PORT1);
//the true here means its reversed, if you dont put true the motor is not reversed by default (is false)
vex::motor rightF = vex::motor(vex::PORT6,true);
vex::motor leftB = vex::motor(vex::PORT13);
vex::motor rightB = vex::motor(vex::PORT12,true);
/*
the ratio36_1 specifies that this is a motor with a torque cassette (red one), if not specified assumes "medium" ratio 
(green, 18:1), other ratio is speed ratio ratio 6:1
*/
vex::motor mDrive = vex::motor(vex::PORT11, vex::ratio36_1);
vex::motor liftLU = vex::motor(vex::PORT7,true);
vex::motor liftLD = vex::motor(vex::PORT7,vex::ratio36_1,true);
vex::motor liftRU = vex::motor(vex::PORT8);
vex::motor liftRD = vex::motor(vex::PORT8,vex::ratio36_1);
vex::motor clamp = vex::motor(vex::PORT10,vex::ratio36_1, true);
vex::motor claw = vex::motor(vex::PORT22);

/*
this defined the inertial sensor, this is basically the gyro, for the love of god dont use the accelerometer for 
anythimg more than basic wall collision detection
*/
vex::inertial turnyBoi = vex::inertial(vex::PORT4);

/*
Below are the shaft encoders, the three wire sensors that measure the number of degrees an axle has rotated
This is usually paired with a tracking wheel, which is a non-driven wheel sprung down on the ground, to measure 
hor far the robot has moved forward, or even turned if you have two on either side. Also used for odometry

This is used in auton.

To plug this inm the shaft encoder has two wires, top and bottom, but to define the port, you specify the first port,
which must be odd, so ports A,C,E,G. The next wire must be in the next port, so if in A, next must be in B.
1 = A, 2 = B, 3 = C etc.
*/

vex::encoder track = vex::encoder(god.ThreeWirePort.C);
vex::encoder fwdTrack = vex::encoder(god.ThreeWirePort.G);

//default, make sure you include this so it works on field control
vex::competition Competition;
