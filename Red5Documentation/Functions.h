/*
This is our Functions file, here all of our functions are defined to move motors, get sensors, and all sorts of wacky stuff.
It makes writing our autonomous and driver program in the main file much less of a headache, and much easier to read.

Again, make sure that every function is named sensibly, it is a pain to find the right one, if theyre named nicely,
you can just ctrl+f and search for it.
*/
#include "Motors.h"

/*
each variable needs a data type to say what kind of information this variable holds
- int is integer, these hold whole numbers
- double and float are used for decimal numbers, double holds bigger numbers than float
- const stands for constant, and means that this variable cant be changed when the program is run
- bool is just true or false
for other types look up C++ data types
*/


/*
sometimes its a good idea to define your power variables up here, to use in any function (these are called global variables)
and change all powers in the functions really quickly

I must stress, dont use global variables for anything else unless you ABSOLUTELY have to, otherwise you wont understand
where and how theyre being changed, and when you get back to the code you cant read anything (as we found out)
*/
const int liftpow = 85;
const int clamppow = 60;
const int clawpow = 60;
float drivePow = 1;
const int Aliftpow = 60;
const int Aclamppow = 60;
const int Aclawpow = 60;
const int Adrivespe = 35;
const float drivePct = 0.9;

//These are the only other global variable we use, but can be replaced using static keyword in the function, 
//which in hindsight we would rather use
int go;
bool toggle;
float leftPow;
float rightPow;

/*
These includes and the two functions before driver control are just used to print numbers to the terminal,
useful to see sensor and motor values for testing, particularly autonomous, and checking whether functions
are being run etc.

Idk how they work, just copy paste it at the top of your programs
*/
#include <iostream>
#include <cstring>
#include <string.h>
#include "stdarg.h"
#include <sstream>
template <typename T>
std::string to_string(T value){
  std::ostringstream os;
  os << value;
  return os.str();
}

void print(double d){
    std::cout << d << std::endl;
}
// Drive Control
/*
These next three functions are designed to flip the power of the drive between 30% and 100% whenever one button button is pressed
So there there are three parts to this:
1. When the button is pressed, flip the power ONCE, there is a bit of an issue where when you press a button, the function
is called multiple times, this isnt a problem with other drive functions, but for a one button flip. This must be resolved by
creating a lock, so that when it is first pressed, the drive power is not changed any more until the button is released
2. When the button is released, the drive power must be "flippable" again, so the lock by pressing the button is released
3. Checking that whenever the power is flipped, what the power already is at to flip to the other power

There are different ways to create this, look up edge-calling for methods
*/

//this is the "bounce" function called when the button is released, this relases the lock created when the button is pressed
//the lock is relased by setting go = 1
void bounc(){
  go = 0;
}

//this is used to flip the toggle variable, which determines the power. This is flipped if go == 0, and is 
//set to 1 to act as the lock so it cant be changed anymore
void change(){
  if(go == 0){
    if(toggle){
      toggle = false;
    }
    else{
      toggle = true;
    }
    go += 1;
  }
}

//this is then put in the mainloop to set the power based on what value toggle has
void driveTog(){
  if(toggle){
    drivePow = 0.3;
  }
  else{
    drivePow = 1;
  }
}

//This is a function to make the drive wheels coast, meaning that no power is supplied to them and can move freely
//the other stop types are brake, which locks up the motor, and hold, which actively moves the motor to the braked position
//hold is most likely to overheat motors, coast is least likely to, so use appropriately
void driveCoast(){
  leftF.stop(vex::coast);
  leftB.stop(vex::coast);
  rightB.stop(vex::coast);
  rightF.stop(vex::coast);
}

//simply used to move the strafe wheel to the right when button is pressed
void fwdStrafe(){
  //vex::fwd can be changed to vex::rev to change the direction, 100 is the power, vex::pct is the percentage power
  //can use voltage instead
  mDrive.spin(vex::fwd,100,vex::pct);
}

//moves the strafe in the other direction, instead of rev we just used -100 because its easier
void bkStrafe(){
  mDrive.spin(vex::fwd,-100,vex::pct);
}

//this stops the strafe moving when the strafe button is released
void brakeStrafe(){
  mDrive.stop(vex::coast);
}

//this turns the robot on the spot for an old experimental drive we were using, useful for arcade control
void turn(float b){
  leftF.spin(vex::fwd,b,vex::pct);
  rightF.spin(vex::fwd,-b,vex::pct);
  leftB.spin(vex::fwd,b,vex::pct);
  rightB.spin(vex::fwd,-b,vex::pct);
}

//moves lift up when button is pressed (and draws a circle on the brain!)
void liftUp(){
  liftLU.spin(vex::fwd, liftpow, vex::pct);
  liftRU.spin(vex::fwd, liftpow, vex::pct);
  liftLD.spin(vex::fwd, liftpow, vex::pct);
  liftRD.spin(vex::fwd, liftpow, vex::pct);
  god.Screen.drawCircle(260, 120, 100);
}

//moves lift down when button is played
void liftDown(){
  liftLU.spin(vex::fwd, -liftpow, vex::pct);
  liftRU.spin(vex::fwd, -liftpow, vex::pct);
  liftLD.spin(vex::fwd, -liftpow, vex::pct);
  liftRD.spin(vex::fwd, -liftpow, vex::pct);
  god.Screen.drawCircle(260, 120, 100);
}

//stops lift moving when button released
void liftStop(){
  liftLU.stop(vex::hold);
  liftRU.stop(vex::hold);
  liftLD.stop(vex::hold);
  liftRD.stop(vex::hold);
}

//closes clamp when buttons pressed (shuold probably be called clampClose or smth)
void clampUp(){
  clamp.spin(vex::fwd, clamppow, vex::pct);
}

//open clamp when button pressed
void clampDown(){
  clamp.spin(vex::fwd, -clamppow, vex::pct);
}

//brake clamp when closed
void clampStop(){
  clamp.stop(vex::hold);
}

//move claw, not actually on our robot
void clawUp(){
  claw.spin(vex::fwd, clawpow, vex::pct);
}

void clawDown(){
  claw.spin(vex::fwd, -clawpow, vex::pct);
}

void clawStop(){
  claw.stop(vex::brake);
}

//This function was an attempt to have the drive ramp up to its speed, instead of jolting to its speed right away
//This was discontinues as max prefered the jolty movement, and this wasnt an issue with overheats, port blowing etc.
//DO NOT study this closely, this was an abandoned piece of work early in the season, and is riddled with logical errors
void ramp(){
  //This variable is the difference between the right joystick value and the velocity of the right drive
  //fabs turns the number from a negative to a positive, if its already positive it stays positive
  //this is used to see whether there is a need to ramp to the different velocity
  double dR = fabs(MCkun.Axis2.value() - rightF.velocity(vex::pct));

  //this is the target velocity of the right drive, which is dictated by the right joystick value
  double rightTarget = MCkun.Axis2.value();

  //this is the left drive and joystick difference, identical to the right difference
  double dL = fabs(MCkun.Axis3.value() - leftF.velocity(vex::pct));
  
  //target velocity of the left drive
  double leftTarget = MCkun.Axis3.value();

  //if the target was less than 3, the drive was set to coast
  //this was because max didnt want the drive to ramp down, he wanted it to stop immediately, only wanted the ramp
  //to activate when its moving backwards or forwards
  if(fabs(rightTarget) < 3){
    double rightSpd = 0;
    rightB.stop(vex::coast);
    rightF.stop(vex::coast);
  }
  //here the ramp takes place, if the difference between the joystick and the drive was greater than 5, the power would
  //increase by 5 or decrease by 5 depending on the direction of the joystick.
  else if(dR > 5){ //check if difference is significant enough for ramp
    if(rightTarget > rightF.velocity(vex::pct)){ //check if it needs to ramp up
      //rightSpd += 5;
    }
    else{ //otherwise ramp down
      //rightSpd -= 5;
    }
    //rightB.spin(vex::fwd,rightSpd,vex::pct);
    //rightF.spin(vex::fwd,rightSpd,vex::pct);
  }

  //same logic for left side
  if(fabs(leftTarget) < 3){ // anywhere to 0
    //leftSpd = 0;
    leftB.stop(vex::coast);
    leftF.stop(vex::coast);
  }
  else if(dL > 5){ // anywhere to forwards
    if(leftTarget > leftF.velocity(vex::pct)){
      //leftSpd += 5;
    }
    else{
      //leftSpd -= 5; //anywhere to backwards
    }
    //leftB.spin(vex::fwd,leftSpd,vex::pct);
    //leftF.spin(vex::fwd,leftSpd,vex::pct);
  }
  
  //idek
  else{
    leftF.spin(vex::fwd,leftTarget,vex::pct);
    rightF.spin(vex::fwd,rightTarget,vex::pct);
    leftB.spin(vex::fwd,leftTarget,vex::pct);
    rightB.spin(vex::fwd,rightTarget,vex::pct);
    //leftSpd = leftTarget;
    //rightSpd = rightTarget;
  }
}

//this was also discontinued, and was to try and correct any turning when using the strafe drive using the gyro
//The issue with this was that it wasnt possible to get a reliable gyro value when turning and strafing at the same time
//limiting max to using only strafe by itself, which wasnt a limitation he was happy with
//overall resolving this issue would take a lot more work with very little benefit
//the logic used here is a PID, which will be annotated in the autonomous functions that incorporate it
//so this will not be annotated
void driveStrafeCorrect(double oldGyro, double newGyro, double d1){
  //double dr = d1-d2;
  /*
  if (dr > 6){
    //integral = 0;
  }
  if(d1 >= 1){
      if(newGyro > oldGyro){
        //turn(-d1*2.3 + dr*1.5 - integral * 0.000001);
      }
      else{
        //turn(d1*2.3 - dr*1.5 + integral * 0.000001);
      }
    }
    else{
      driveCoast();
    }
  //integral = d1 + integral;
  double d2 = d1;
  */
}

//Autonomous Control
/*
These are our autonomous functions that we use in our 15 second and skills autonomous
These are called whenever we write that function in the autonomous function of our main file
*/

//stop drive when called
void driveStop(){
  leftF.stop(vex::brake);
  rightF.stop(vex::brake);
  leftB.stop(vex::brake);
  rightB.stop(vex::brake);
}

/*
PLEASE LOOK AT MOST UPDATED SKILLS CODE ON THE LAPTOP FOR THE FULLY WORKING VERSION, THIS FUNCTION HAS SOME ISSUES
AND DIFFERENCES, AND UNFORTUNATELY HAVENT UPDATED SKILLS TO GITHUB AS OF YET

This was a successful attempt to resolve an issue where, when the robot was to move forward, it would veer to the side

This uses the gyro value to get a measure of how much the robot has turned, and move the left drive accoding to that
value to compensate for this

This uses a technique called PID control loops. This stands for Proportional, Integral, and Derivative. Here only proportional is used
*/
//function takes in gyro value from the start of moving forwards, current gyro value, and the velocity of moving forwards
float fwdCorrect(float oldGyro, float newGyro, float v){
  double leftPow = v; //baseline left power
  double error = oldGyro; //defines error
  
  //diameter of wheel = 10.5cm
  //one rotation of motor = 32.98672cm

  //rotates depending on variable y, which is calculated above
  newGyro = turnyBoi.rotation(); //fetches gyro value
  error = oldGyro-newGyro; //defines error as difference between reference value and current value

  if(fabs(error) >= 0.2){ //change power if error is significant, after testing we chose 0.2 degrees
    leftPow = v + error*1 + dE*10; //change power according to error
  }
  return leftPow;
}

/*
PLEASE LOOK AT MOST UPDATED SKILLS CODE ON THE LAPTOP FOR THE FULLY WORKING VERSION, THIS FUNCTION HAS SOME ISSUES
AND DIFFERENCES, AND UNFORTUNATELY HAVENT UPDATED SKILLS TO GITHUB AS OF YET

This was a function used to dictate how far the robot should move using a tracking wheel and proportional value.
The target to move to was based on the rotational degrees of the tracking wheel.

This incorporates the function above to accurately move to the target whilst correcting to move straight
*/
//takes in x, the number of cm to move to from start position, v velocity, and e error margin.
void fwdTo(double x, double v, float e){
  float y= -(x/34.9098*16/13)*360; //converts cm to tracking wheel degrees
  float target = y; //target
  double rightPow = v; //set powers to velocities
  double leftPow = v;
  double oldGyro = turnyBoi.rotation(); //defines starting gyro position for fwdCorrect
  float error = fwdTrack.rotation(vex::deg) - target; //error is defined as difference in degrees of wheel and target
  while(fabs(error) > e){ //while greater than error margin.. chosen based on short/long distances
    error = fwdTrack.rotation(vex::deg) - target; //error defined at start of loop
    double newGyro = turnyBoi.rotation(); //new gyro value for fwdCorrect
    print(error); //print for testing
    rightPow = error*0.8; //proportional to error
    if(fabs(rightPow) > fabs(v)){ //cap velocity to v so it isnt higher than specified
      if(error>0){
        rightPow = v;
      }
      else{
        rightPow = -v;
      }
    }
    leftPow = rightPow; //set sides to match
    leftPow = fwdCorrect(oldGyro, newGyro, leftPow); //change leftPow according to values
    if(y > 0){ //set powers
      rightF.spin(vex::fwd, -rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, -leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, -rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, -leftPow, vex::velocityUnits::pct);
    }  
    else{
      rightF.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
    }
    vex::task::sleep(20); //sleep to have roughly constant loop runtime
  }
  driveStop(); //stop afterwards
}

/*
PLEASE LOOK AT MOST UPDATED SKILLS CODE ON THE LAPTOP FOR THE FULLY WORKING VERSION, THIS FUNCTION HAS SOME ISSUES
AND DIFFERENCES, AND UNFORTUNATELY HAVENT UPDATED SKILLS TO GITHUB AS OF YET

Exactly the same as the fwdTo function, the only difference is the target is the addition of the x from its position
Therefore I will not annotate this, simply refer to the previous function.
*/
void fwd(double x, double v, float e){
  float y= -(x/34.9098*16/13)*360;
  float target = fwdTrack.rotation(vex::deg) + y;
  double rightPow = v;
  double leftPow = v;
  double oldGyro = turnyBoi.rotation();
  float error = fwdTrack.rotation(vex::deg) - target;
  while(fabs(error) > e){
    error = fwdTrack.rotation(vex::deg) - target;
    double newGyro = turnyBoi.rotation();
    print(error);
    rightPow = error*0.8;
    if(fabs(rightPow) > fabs(v)){
      if(error>0){
        rightPow = v;
      }
      else{
        rightPow = -v;
      }
    }
    leftPow = rightPow;
    if(y > 0){
      rightF.spin(vex::fwd, -rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, -leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, -rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, -leftPow, vex::velocityUnits::pct);
    }  
    else{
      rightF.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
    }
    vex::task::sleep(20);
    leftPow = fwdCorrect(oldGyro, newGyro, leftPow);
  }
  driveStop();
}

/*
This function was used in our 15 second auton without using the tracking wheels. This simply usses a PD to correct for
any turning whilst driving, and the forward does not have a PID.
*/
void driveForwards(float x, float v){
    float y=(x/31.548)*360; //changes distance needed into degrees turn for motor based on circumference of wheel
    double oldGyro = turnyBoi.rotation(); //gets base gyro value at start of forward
    rightB.resetRotation(); //reset to check whether target (y) is reached
    double rightPow = v;
    double leftPow = v; //set powers
    double dE = 0; //defined serivative function
    double newGyro = turnyBoi.rotation(); //define new gyro
    double error = oldGyro; //define error to be updated in loop
    double lastError = error; //define last error
    //diameter of wheel = 10.5cm
    //one rotation of motor = 32.98672cm

    //rotates depending on variable y, which is calculated above
    while(rightB.rotation(vex::deg) < y){ //loop active while right back wheel has not yet reached target
      newGyro = turnyBoi.rotation(); //store degrees of gyro
      error = oldGyro-newGyro; //store how much turned
      dE = error - lastError; //store difference in error

      rightF.spin(vex::fwd, rightPow, vex::velocityUnits::pct); //go forwards
      leftF.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      if(fabs(error) >= 0.2){ //if turned more than two degrees...
        //print(error);
        //print(leftPow);
        leftPow = v + error*1 + dE*10; //set powr based on error and change of error
      }
      lastError = error; //set last error to error at this loop for future rates
      vex::task::sleep(20); //sleep for 20ms to keep looptime constant
    }
    driveStop();//stop at end
}

//same as driveForwards but backwards and without turning correct
void driveBackwards(float x, float v){
    float y=(x/31.548)*360; //changes distance needed into degrees turn for motor
    double oldGyro = turnyBoi.rotation();
    rightB.resetRotation();
    double rightPow = -v;
    double leftPow = -v;
    //diameter of wheel = 10.5cm
    //one rotation of motor = 32.98672cm

    //rotates depending on variable y, which is calculated above
    while(rightB.rotation(vex::deg) > -y){
      double newGyro = turnyBoi.rotation();
      double error = oldGyro-newGyro;
      rightF.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      /*if(fabs(error) >= 0.5){
        print(error);
        if(error > 0){
          leftPow = -v + v*error*0.02;
        }
        else{
          leftPow = -v - v*error*0.02;
        }
        print(leftPow);
      }*/
    }
    driveStop();

}

/*
PLEASE LOOK AT MOST UPDATED SKILLS CODE ON THE LAPTOP FOR THE FULLY WORKING VERSION, THIS FUNCTION HAS SOME ISSUES
AND DIFFERENCES, AND UNFORTUNATELY HAVENT UPDATED SKILLS TO GITHUB AS OF YET

This was a function implementing a proportional loop to correct for angle change in the robot when using the strafe
*/
void strafeCorrect(double oldGyro, double newGyro, double target){
  double d = fabs(newGyro - oldGyro); //define error
  if(d >= 1){ //while degree change is 1 or more degrees
    d = fabs(newGyro - oldGyro); //set error
    if(newGyro > oldGyro){ //check if turned to the right
      turn(-d*2.2); //turned to the left proportional to error
    }
    else{
      turn(d*2.2); //otherwise turn right
    }
  }
}

/*
This was used to strafe to a certain distance using a tracking wheel and the above pid to ensure that it is accurate
x would set the distance in cm, and v the velocity of the strafe wheel in pct
*/
void strafeRight(double x, double v){
  float y=-(x/31.548*16/13)*360; //set target based on circumference of tracking wheel
  float target = track.rotation(vex::deg) + y; //target based on tracking wheel value
  double oldGyro = turnyBoi.rotation(); //get old gyro value
  while(fabs(track.rotation(vex::deg) - target) > 8){ //check if within 89 degrees of tracking wheel
    double newGyro = turnyBoi.rotation(); //update degree value
    if(y > 0){ //if target positive
      mDrive.spin(vex::fwd, -v, vex::velocityUnits::pct); //run forward (negative because strafe and tracking were different directions
    }  
    else{
      mDrive.spin(vex::fwd, v, vex::velocityUnits::pct); //else run other direction
    }
    strafeCorrect(oldGyro, newGyro, target); //correct in loop
    vex::task::sleep(20); //set sleep for correction
  }
  mDrive.stop(vex::coast); //stop after
}

//simple function to run strafe wheel for amount of time
void strafeTime(float v, float t){ //takes in velocity and time
  mDrive.spin(vex::fwd, v, vex::pct); //spin middle wheel
  vex::task::sleep(t); //spin for this amount of time
  mDrive.stop(vex::coast); //stop
}

//drive for specified time (without stop)
void driveTime(float x, int t){
  leftF.spin(vex::fwd, x, vex::pct);
  rightF.spin(vex::fwd, x, vex::pct);
  leftB.spin(vex::fwd, x, vex::pct);
  rightB.spin(vex::fwd, x, vex::pct);
  vex::task::sleep(t);  
}

/*
void driveBackwards(float x){
    float y=(-x/16.4779)*360; //changes distance needed into degrees turn for motor
        //one rotation of motor = 23.069cm forwards
        rightF.startRotateFor(y,vex::deg, 50, vex::velocityUnits::pct);
        leftF.startRotateFor(y,vex::deg, 50, vex::velocityUnits::pct);
        rightB.startRotateFor(y,vex::deg, 50, vex::velocityUnits::pct);
        leftB.startRotateFor(y,vex::deg, 50, vex::velocityUnits::pct);
        //rotates depending on variable y, which is calculated above
    while(leftB.isSpinning()){}
}*/

/*
old function that would turn based on rotations of a motor, before we used the gyro

the change in the multiple of the target y was based purely on percentage change after testing. eg if turns for 160 degrees
instead of 180, multiply it by 180/160 as it needs to turn more
*/
void oldTurnRight(float w, float v){ //turns right, just add number in degree for turn
    float y=(w*1.30949*2);
    //26.3 cm turning circle
    //41.312 each wheel to cover full circle
    //1.3095 rotation for full circle
    //471.2 = full circle
    leftF.startRotateFor(y,vex::rotationUnits::deg, v, vex::velocityUnits::pct);
    rightF.startRotateFor(-y,vex::rotationUnits::deg, v, vex::velocityUnits::pct);
    leftB.startRotateFor(y,vex::rotationUnits::deg, v, vex::velocityUnits::pct);
    rightB.startRotateFor(-y,vex::rotationUnits::deg, v, vex::velocityUnits::pct);
    //all turns wheels UNTIL while command is no longer met
    while(rightB.isSpinning()){}
}

/*
most recent turn command using the gyro, turning for an amount as opposed to a target, using a full PID loop.

we used turn for only in the 15 second auton simply because calibrating at the start of an alliance match is unreliable, as
we couldn't spare the time to recalibrate, we did spare this time for our 1 minute skills autonomous.

Much less accurate than turn to and with calibration, but good for when turns only need to be quick and dirty.
*/
void turnRightFor(float d, int v){ //take in degrees and velocity
  double target = turnyBoi.rotation(vex::deg) + d; //target is degrees on top of current orientation
  double lastError = target - turnyBoi.rotation(vex::deg); //define last error
  double error = target - turnyBoi.rotation(vex::deg); //deine error
  double t = god.Timer.value(); //get time at function call to ensure loop doesnt take too long
  double dE = 0; //define derivative
  double iE = 0; //define integral
  int counter = 0; //used to adjust how long you need to be in target for
  double speed = 0; //define power to motors
  /*
  the loop ends in two conditions:
  1. That the error is less than or equal to 0.4 degrees for 10 consecutive loops - this made sure it corrected after overshooting
  2. That the loop takes more than 1.8 seconds to end - this made sure the loop didnt get stuck at, eg, 0.41 error
  */
  while(fabs(error) >= 0.4  && god.Timer.value()-t < 1.8 && counter < 10){
    error = target - turnyBoi.rotation(); //error updated
    dE = error - lastError; //derivative updated
    iE += error; //error added to integral
    speed = error*0.8 + 4*dE + iE*0.002; //set power (doesnt matter if before or after integral adjustment as so miniscule, best after)
    if(speed > v){ //if speed was higher than velocity input..
      speed = v; //set speed at input max
      iE = 0; //reset integral
    }
    else if(speed < -v){ //if speed was too high but other direction..
      speed = -v; //cap speed
      iE = 0; //reset integral
    }
    if(fabs(error) <= 0.4){ //if target met..
      counter += 1; //increment counter...
    }
    else{ //else reset counter
      counter = 0;
    }
    turn(speed); //set turn speed as defined
    lastError = error; //update lasterror
    print(error); //print just for testing :P
    vex::wait(20, vex::msec); //wait for loop to be roughly constant
  }
  driveStop(); //stop when done
}

//asme as above but turn to, and without counter
void turnRight(float d, int v){
  double lastError = d - turnyBoi.rotation(vex::deg);
  double error = d - turnyBoi.rotation(vex::deg);
  double t = god.Timer.value();
  double dE = 0;
  double iE = 0;
  double speed = 0;
  while(fabs(error) >= 0.4  && t- god.Timer.value()< 1.8){
    error = d - turnyBoi.rotation();
    dE = error - lastError;
    iE += error;
    speed = error*1.3 + 4*dE + iE*0.002;
    if(speed > v){
      speed = v;
      iE = 0;
    }
    else if(speed < -v){
      speed = -v;
      iE = 0;
    }
    turn(speed);
    lastError = error;
    print(error);
    vex::wait(20, vex::msec);
  }
  driveStop();
}

//basic gyro turn, simply turn left until the target is met and then stop, no pid so not accurate at all
void turnLeft(float d, int v){
  while(turnyBoi.rotation() > d){
    turn(-v);
  }
  driveStop();
}

void oldTurnLeft(float w){ //turns right, just add number in degree for turn
    float y=((-w*360)/63.96326);
        leftF.startRotateFor(y,vex::deg, 60, vex::velocityUnits::pct);
        rightF.startRotateFor(-y,vex::deg, 60, vex::velocityUnits::pct);
        leftB.startRotateFor(y,vex::deg, 60, vex::velocityUnits::pct);
        rightB.startRotateFor(-y,vex::deg, 60, vex::velocityUnits::pct);
            //all turns wheels UNTIL while command is no longer met
    while(rightB.isSpinning()){}
}

//Our simple arm command, as we decided the precision of a PID is not necessary
//d is input for degrees, v for velocity
//time is a true or false variable that is used to use or not use a timegate
//timeThresh is the maximum amoount of time the arm should be running for iof time is True, 
//and if it runs for too long than to exit the loop
//We only used this when the lift would bottom out or get stuck
void arm(float d, float v, bool time, float timeThresh){
  d = (d+3)*7; //convert degrees of arm to degrees of arm, and make baseline 3 degrees of arm
  double t1 = god.Timer.value(); //timer for timegating
  liftLU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct); //rotate arms
  liftRU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftLD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftRD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  while(liftRD.isSpinning()){ //dont let code move on if not finished
    if(time && god.Timer.value() - t1 < timeThresh){ //timegate if appropriate
      print(god.Timer.value() - t1); //for testing
      break; //break if ran too long
    }
  }
}

//our main method of braking the arm, to hold it in place
void holdArm(){
  liftLU.stop(vex::hold);
  liftRU.stop(vex::hold);
  liftLD.stop(vex::hold);
  liftRD.stop(vex::hold);
}

//run clamp for some amount of time
//t is time, v is velocity
void clampTime(int t, int v){
  clamp.spin(vex::fwd, -v, vex::pct);
  vex::task::sleep(t);
  clampStop();
}

//move clamp to a certain position
//d is degree of clamp, v is velocity at which it opens
void clampOpen(float d, float v){
  d = d*5; //convert claw degree to motor degree
  clamp.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct); //rotate to a certain degree position
  while(clamp.isSpinning()){} //let finish without anything else interrupting
}

//brake EVERYTHING
void godsBrake(){
  driveStop();
  clampStop();
  liftStop();
  clawStop();
}
