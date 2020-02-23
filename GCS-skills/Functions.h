#include "Motors.h"

const int liftpow = 85;
const int clamppow = 60;
const int clawpow = 60;
float drivePow = 1;
const int Aliftpow = 60;
const int Aclamppow = 60;
const int Aclawpow = 60;
const int Adrivespe = 35;
const float drivePct = 0.9;

int go;
bool toggle;
float leftPow;
float rightPow;

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
void bounc(){
  go = 0;
}

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

void driveTog(){
  if(toggle){
    drivePow = 0.3;
  }
  else{
    drivePow = 1;
  }
}

void driveCoast(){
  leftF.stop(vex::brake);
  leftB.stop(vex::brake);
  rightB.stop(vex::brake);
  rightF.stop(vex::brake);
}

void fwdStrafe(){
  mDrive.spin(vex::fwd,100,vex::pct);
  turnyBoi.setHeading(180, vex::deg);
  int driveOldGyro = int(floor(turnyBoi.heading()))%360;
  //print(driveOldGyro);
}

void bkStrafe(){
  mDrive.spin(vex::fwd,-100,vex::pct);
  turnyBoi.setHeading(180, vex::deg);
  int driveOldGyro = int(floor(turnyBoi.heading()))%360;
  ///print(driveOldGyro);
}

void brakeStrafe(){
  mDrive.stop(vex::coast);
  driveCoast();
}

void turn(float b){
  leftF.spin(vex::fwd,b,vex::pct);
  rightF.spin(vex::fwd,-b,vex::pct);
  leftB.spin(vex::fwd,b,vex::pct);
  rightB.spin(vex::fwd,-b,vex::pct);
}

void liftUp(){
  liftLU.spin(vex::fwd, liftpow, vex::pct);
  liftRU.spin(vex::fwd, liftpow, vex::pct);
  liftLD.spin(vex::fwd, liftpow, vex::pct);
  liftRD.spin(vex::fwd, liftpow, vex::pct);
  god.Screen.drawCircle(260, 120, 100);
}

void liftDown(){
  liftLU.spin(vex::fwd, -liftpow, vex::pct);
  liftRU.spin(vex::fwd, -liftpow, vex::pct);
  liftLD.spin(vex::fwd, -liftpow, vex::pct);
  liftRD.spin(vex::fwd, -liftpow, vex::pct);
  god.Screen.drawCircle(260, 120, 100);
}

void liftStop(){
  if(liftLD.rotation(vex::deg) < 25){
    liftLU.stop(vex::coast);
    liftRU.stop(vex::coast);
    liftLD.stop(vex::coast);
    liftRD.stop(vex::coast);
  }
  else{
    liftLU.stop(vex::hold);
    liftRU.stop(vex::hold);
    liftLD.stop(vex::hold);
    liftRD.stop(vex::hold);
  }
}

void clampUp(){
  clamp.spin(vex::fwd, clamppow, vex::pct);
}

void clampDown(){
  clamp.spin(vex::fwd, -clamppow, vex::pct);
}

void clampStop(){
  clamp.stop(vex::hold);
}

void clawUp(){
  claw.spin(vex::fwd, clawpow, vex::pct);
}

void clawDown(){
  claw.spin(vex::fwd, -clawpow, vex::pct);
}

void clawStop(){
  claw.stop(vex::brake);
}

void rightRamp(){
  
}

void ramp(){

  double dR = fabs(MCkun.Axis2.value() - rightF.velocity(vex::pct));

  double rightTarget = MCkun.Axis2.value();

  double dL = fabs(MCkun.Axis3.value() - leftF.velocity(vex::pct));

  double leftTarget = MCkun.Axis3.value();

  if((leftTarget > 3 && rightTarget > 3)  || (leftTarget < -3 && rightTarget < -3) ){
    if(fabs(rightTarget) < 3){
      double rightSpd = 0;
      rightB.stop(vex::coast);
      rightF.stop(vex::coast);
    }
    else if(dR > 5){
      if(rightTarget > rightF.velocity(vex::pct)){
        //rightSpd += 5;
      }
      else{
        //rightSpd -= 5;
      }
      //rightB.spin(vex::fwd,rightSpd,vex::pct);
      //rightF.spin(vex::fwd,rightSpd,vex::pct);
      vex::task::sleep(10);
    }

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
      vex::task::sleep(10);
    }
  }
  else{
    leftF.spin(vex::fwd,leftTarget,vex::pct);
    rightF.spin(vex::fwd,rightTarget,vex::pct);
    leftB.spin(vex::fwd,leftTarget,vex::pct);
    rightB.spin(vex::fwd,rightTarget,vex::pct);
    //leftSpd = leftTarget;
    //rightSpd = rightTarget;
  }
}

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

void driveStop(){
  leftF.stop(vex::brake);
  rightF.stop(vex::brake);
  leftB.stop(vex::brake);
  rightB.stop(vex::brake);
}

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

void strafeCorrect(double oldGyro, double newGyro, double target, double dE, double error, double lastError){
  if(fabs(error) >= 0.0){
    newGyro = turnyBoi.rotation();
    double pow = error*1.8 + dE*22;
    rightB.spin(vex::fwd, -pow, vex::pct);
    rightF.spin(vex::fwd, -pow, vex::pct);
  }
  else{
    rightB.stop(vex::coast);
    rightF.stop(vex::coast);
  }
}

void strafeRight(double x, double v){
  float y=-(x/31.548*16/13)*360;
  double dE = 0;
  double lastError = 0;
  float target = track.rotation(vex::deg) + y;
  double oldGyro = turnyBoi.rotation();
  double newGyro = turnyBoi.rotation();
  double error = oldGyro - newGyro;
  while(fabs(track.rotation(vex::deg) - target) > 8){
    print(track.rotation(vex::deg) - target);
    newGyro = turnyBoi.rotation();
    error = oldGyro - newGyro;
    dE = error - lastError;
    if(y > 0){
      mDrive.spin(vex::fwd, -v, vex::velocityUnits::pct);
    }  
    else{
      mDrive.spin(vex::fwd, v, vex::velocityUnits::pct);
    }
    strafeCorrect(oldGyro, newGyro, target, dE, error, lastError);
    lastError = error;
    vex::task::sleep(20);
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

void turnRight(float d, int v){
  double lastError = d - turnyBoi.rotation(vex::deg);
  double error = d - turnyBoi.rotation(vex::deg);
  double t = god.Timer.value();
  double dE = 0;
  double iE = 0;
  double speed = 0;
  while(fabs(error) >= 0.4  && t - god.Timer.value()< 1.8){
    error = d - turnyBoi.rotation();
    dE = error - lastError;
    iE += error;
    if(fabs(error) >= 3){
      iE = 0;
    }
    speed = error*0.8 + 4*dE + iE*0.005;
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

void arm(float d, float v){
  d = (d+3)*7;
  liftLU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftRU.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftLD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  liftRD.startRotateTo(d, vex::deg, v, vex::velocityUnits::pct);
  while(liftRD.isSpinning()){}
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
