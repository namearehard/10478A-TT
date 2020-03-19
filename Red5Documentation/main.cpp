#include "Functions.h"

 void preAuton(){
   
 }
 
 void autonomous( void ) {
  liftLD.spin(vex::fwd, -Aliftpow, vex::pct);
  liftRD.spin(vex::fwd, -Aliftpow, vex::pct);
  clamp.resetRotation();
  clamp.resetPosition();
  clamp.spin(vex::fwd, -Aclamppow-40, vex::pct);
  vex::task::sleep(300);
  liftStop();
  clampStop();
  liftLD.resetRotation();
  liftLD.resetPosition();
  liftRD.resetRotation();
  liftRD.resetPosition();
  track.resetRotation();
  clampOpen(-65, Aclamppow + 40);
  driveForwards(10, Adrivespe);
  arm(10, Aliftpow, false, 0, true);
  driveForwards(35, Adrivespe);
  driveBackwards(2.3, Adrivespe);
  arm(-2, Aliftpow, false, 0, true);
  clampTime(700, Aclamppow+40);
  clampStop();
  arm(10, Aliftpow+20, false, 0, true);
  strafeRight(1.5, 100);
  arm(52.5, Aliftpow-20, false, 0, true);
  driveForwards(20.5, Adrivespe);
  vex::task::sleep(500);
  clampOpen(-80, Aclamppow + 40);
  arm(-2, Aliftpow + 15, false, 0, false);
  while(liftLD.isSpinning()){}
  clampTime(300, Aclamppow+40);
  clampStop();

  arm(10, Aliftpow, false, 0, true);
  holdArm();
  driveBackwards(60, 100);
  turnRightFor(-107, 30);

  driveForwards(75, 100);
  vex::wait(500,vex::msec);
  arm(-2,Aliftpow, true, 0.8, true);
  driveTime(-100, 100);
  driveStop();
  arm(2,Aliftpow, true, 0.8, true);
  vex::wait(400, vex::msec);
  clampOpen(-17,100);
  driveBackwards(30, 45);
}
 
 void usercontrol( void ) {
  turnyBoi.setHeading(180, vex::deg);
  double driveOldGyro = int(floor(turnyBoi.heading()))%360;
  while (true) {

    god.Screen.clearScreen();
    god.Screen.printAt(150, 30, "clamp: %7.2f",clamp.temperature(vex::temperatureUnits::celsius));
    god.Screen.printAt(150, 50, "leftLift: %7.2f",liftLD.temperature(vex::temperatureUnits::celsius));
    god.Screen.printAt(150, 70, "rightLift: %7.2f",liftRD.temperature(vex::temperatureUnits::celsius));
    god.Screen.printAt(150, 90, "strafe: %7.2f",mDrive.temperature(vex::temperatureUnits::celsius));
    god.Screen.render();

    MCkun.ButtonL1.pressed(clampUp);
    MCkun.ButtonL1.released(clampStop);
    MCkun.ButtonL2.pressed(clampDown);
    MCkun.ButtonL2.released(clampStop);

    MCkun.ButtonR1.pressed(liftUp);
    MCkun.ButtonR1.released(liftStop);
    MCkun.ButtonR2.pressed(liftDown);
    MCkun.ButtonR2.released(liftStop);

    /*if(MCkun.Axis4.value() >= 20){
      if(MCkun.Axis3.value() >= 20){
        leftPow = (MCkun.Axis3.value() + MCkun.Axis1.value())*drivePct;
        rightPow = (MCkun.Axis3.value() - MCkun.Axis1.value())*drivePct;
      }
      else{
        leftPow = (MCkun.Axis1.value())*drivePct;
        rightPow = (MCkun.Axis1.value())*drivePct;
      }
    }
    else{
      leftPow = (MCkun.Axis3.value() + MCkun.Axis1.value())*drivePct;
      rightPow = (MCkun.Axis3.value() - MCkun.Axis1.value())*drivePct;
    }

    
    leftF.spin(fwd,leftPow,pct);
    rightF.spin(fwd,rightPow,pct);
    leftB.spin(fwd,leftPow,pct);
    rightB.spin(fwd,rightPow,pct);
    mDrive.spin(fwd,MCkun.Axis4.value(),pct);
    
    
    if(abs(MCkun.Axis1.value()) < 20){
      leftPow = (MCkun.Axis3.value() + MCkun.Axis4.value())*drivePct;
      rightPow = (MCkun.Axis3.value() - MCkun.Axis4.value())*drivePct;
    }
    else if(abs(MCkun.Axis1.value()) >= 20){
      leftPow = (MCkun.Axis3.value() + MCkun.Axis4.value()*0.13)*drivePct;
      rightPow = (MCkun.Axis3.value() - MCkun.Axis4.value()*0.13)*drivePct;
    }
    leftF.spin(fwd,leftPow,pct);
    rightF.spin(fwd,rightPow,pct);
    leftB.spin(fwd,leftPow,pct);
    rightB.spin(fwd,rightPow,pct);
    mDrive.spin(fwd,MCkun.Axis1.value(),pct);
    */
    MCkun.ButtonA.pressed(change);
    MCkun.ButtonA.released(bounc);
    driveTog();
    
    SCkun.ButtonR1.pressed(fwdStrafe);
    SCkun.ButtonR1.released(brakeStrafe);
    SCkun.ButtonL1.pressed(bkStrafe);
    SCkun.ButtonL1.released(brakeStrafe);
    
    leftF.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);
    rightF.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct);
    leftB.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);
    rightB.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct);
  }
 }
 
 
 int main() {
    preAuton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
     
    while(1) {
      vex::task::sleep(100);
    }    
 }
