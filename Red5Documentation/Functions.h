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
- double and float are used for decimal numbers,double holds bigger numbers than float
- const stands for constant, and means that this variable cant be changed when the program is run
- bool is just true or false
for other types look up C++ data types
*/


/*
sometimes its a good idea to defined your power variables up here, to use in any function (these are called global variables)
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
these includes and the two functions before driver control are just used to print numbers to the terminal,
useful to see sensor and motor values for testing, particularly autonomous, and chacking whether functions
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
These next thre functions are designed to flip the power of the drive between 30% and 100% whenever one button button is pressed
So there there are three parts to this:
1. When the button is pressed, flip the power ONCE, there is a bit of an issue where when you press a button, the function
is called multiple times, this isnt a problem with other drive functions, but for a one button flip. this must be resolved by
creating a lock, so that when it is first pressed, the drive power is not changed any more until the button is released
2. When the button is released, the drive power must be "flippable" again, so the lock by pressing the button is released
3. Checking that whenever the power is flipped, what the power already is at to flip to the other power

There are different ways to create this, look up edge calling for methods
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
This was a successful attempt to resolve an issue where, when the robot was to move forward, it would veer to the side
This uses the gyro value to get a measure of how much the robot has turned, and move the left drive accoding to that
value to compensate for this
This uses a technique called PID control loops. This stands for Proportional, Integral, and Derivative. Here the
integral is not used.
*/
float fwdCorrect(float oldGyro, float newGyro, float v){
  double leftPow = v;
  double dE = 0;
  double error = oldGyro;
  double lastError = error;
  //diameter of wheel = 10.5cm
  //one rotation of motor = 32.98672cm

  //rotates depending on variable y, which is calculated above
  newGyro = turnyBoi.rotation();
  error = oldGyro-newGyro;
  dE = error - lastError;

  if(fabs(error) >= 0.2){
    leftPow = v + error*1 + dE*10;
  }
  lastError = error;
  return leftPow;
}

void fwdTo(double x, double v, float e){
  float y= -(x/34.9098*16/13)*360;
  float target = y;
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

void driveForwards(float x, float v){
    float y=(x/31.548)*360; //changes distance needed into degrees turn for motor
    double oldGyro = turnyBoi.rotation();
    rightB.resetRotation();
    double rightPow = v;
    double leftPow = v;
    double dE = 0;
    double newGyro = turnyBoi.rotation();
    double error = oldGyro;
    double lastError = error;
    //diameter of wheel = 10.5cm
    //one rotation of motor = 32.98672cm

    //rotates depending on variable y, which is calculated above
    while(rightB.rotation(vex::deg) < y){
      newGyro = turnyBoi.rotation();
      error = oldGyro-newGyro;
      dE = error - lastError;

      rightF.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftF.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      rightB.spin(vex::fwd, rightPow, vex::velocityUnits::pct);
      leftB.spin(vex::fwd, leftPow, vex::velocityUnits::pct);
      if(fabs(error) >= 0.2){
        //print(error);
        //print(leftPow);
        leftPow = v + error*1 + dE*10;
      }
      lastError = error;
      vex::task::sleep(20);
    }
    driveStop();

}

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

void strafeCorrect(double oldGyro, double newGyro, double target){
  double d = fabs(newGyro - oldGyro);
  while(d >= 1){
    d = fabs(newGyro - oldGyro);
    newGyro = turnyBoi.rotation();
    if(fabs(track.rotation(vex::deg) - target) < 8){
      break;
    }
    if(newGyro > oldGyro){
      turn(-d*2.2);
    }
    else{
      turn(d*2.2);
    }
  }
}

void strafeRight(double x, double v){
  float y=-(x/31.548*16/13)*360;
  float target = track.rotation(vex::deg) + y;
  double oldGyro = turnyBoi.rotation();
  while(fabs(track.rotation(vex::deg) - target) > 8){
    double newGyro = turnyBoi.rotation();
    if(y > 0){
      mDrive.spin(vex::fwd, -v, vex::velocityUnits::pct);
    }  
    else{
      mDrive.spin(vex::fwd, v, vex::velocityUnits::pct);
    }
    //strafeCorrect(oldGyro, newGyro, target);
  }
  mDrive.stop(vex::coast);
}

void strafeTime(float v, float t){
  mDrive.spin(vex::fwd, v, vex::pct);
  vex::task::sleep(t);
  mDrive.stop(vex::coast);
}

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

void turnRightFor(float d, int v){
  double target = turnyBoi.rotation(vex::deg) + d;
  double lastError = target - turnyBoi.rotation(vex::deg);
  double error = target - turnyBoi.rotation(vex::deg);
  double t = god.Timer.value();
  double dE = 0;
  double iE = 0;
  int counter = 0;
  double speed = 0;
  while(fabs(error) >= 0.4  && -t + god.Timer.value()< 1.8 && counter < 10){
    error = target - turnyBoi.rotation();
    dE = error - lastError;
    iE += error;
    speed = error*0.8 + 4*dE + iE*0.002;
    if(speed > v){
      speed = v;
      iE = 0;
    }
    else if(speed < -v){
      speed = -v;
      iE = 0;
    }
    if(fabs(error) <= 0.4){
      counter += 1;
    }
    else{
      counter = 0;
    }
    turn(speed);
    lastError = error;
    print(error);
    vex::wait(20, vex::msec);
  }
  driveStop();
}

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

void arm(float d, float v, bool time, float timeThresh, float drive){
  d = (d+3)*7;
  double t1 = god.Timer.value();
  liftLU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftRU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftLD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftRD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  if(drive){
  while(liftRD.isSpinning()){
    if(time && god.Timer.value() - t1 < timeThresh){
      print(god.Timer.value() - t1);
      break;
    }
    }
  }
}

void holdArm(){
  liftLU.stop(vex::hold);
  liftRU.stop(vex::hold);
  liftLD.stop(vex::hold);
  liftRD.stop(vex::hold);
}

void clampTime(int t, int v){
  // where t is only 1 or -1
  //t= t*3;
  //clamp.startRotateFor(t, vex::deg, clamppow, vex::velocityUnits::pct);
  clamp.spin(vex::fwd, -v, vex::pct);
  vex::task::sleep(t);
  //while(clamp.isSpinning()){}
}

void clampOpen(float d, float v){
  d = d*5;
  clamp.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  while(clamp.isSpinning()){}
}

void godsBrake(){
  driveStop();
  clampStop();
  liftStop();
  clawStop();
}
