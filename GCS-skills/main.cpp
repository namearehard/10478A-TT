#include "Functions.h"

 void preAuton(){
   
 }
 
 void autonomous( void ) {
  turnyBoi.calibrate();
  vex::task::sleep(2000);

  liftLD.spin(vex::fwd, -Aliftpow, vex::pct);
  liftRD.spin(vex::fwd, -Aliftpow, vex::pct);
  vex::task::sleep(250); //250
  liftStop();
  liftLD.resetRotation();
  liftLD.resetPosition();
  liftRD.resetRotation();
  liftRD.resetPosition();
  leftF.resetRotation();
  leftB.resetRotation();
  rightF.resetRotation();
  rightB.resetRotation();
  clamp.resetRotation();
  clamp.resetPosition();
  track.resetRotation();

  clampTime(1550, Aclamppow);
  clampStop();
//fwd(100,Adrivespe);
  fwd(12, Adrivespe, 8);
  arm(14, Aliftpow);
  fwd(35, Adrivespe, 8);
  //vex::task::sleep(200);
  driveBackwards(2.5, Adrivespe);
  clampOpen(-73, Aclamppow);
  arm(-2, Aliftpow);
  clampTime(300, Aclamppow);
  turnRight(0, 100);
  arm(51, Aliftpow-20);
  fwdTo(73, Adrivespe, 8);
  clampOpen(-75, Aclamppow);
  //clampTime(200, -Aclamppow);
  arm(-2, Aliftpow);
  clampTime(400, Aclamppow);
  arm(10, Aliftpow);
  holdArm();
  strafeRight(10, 60);
  fwdTo(12, Adrivespe, 8);
  //fwdTo(28, Adrivespe, 8);
  //print(turnyBoi.rotation());
  turnRight(90, Adrivespe-10);
  strafeRight(22, 60);
  turnRight(90, Adrivespe-10);
  //fwd(10, Adrivespe, 8);
  //strafeRight(50, 60);
  //fwd(3.5, Adrivespe, 8);
  //clampOpen(-67, Aclamppow);
  //arm(3, Aliftpow);
  //clampTime(800, Aclamppow);
  //arm(14, Aliftpow);
  //strafeRight(34, 60);

  //print(turnyBoi.rotation());
  fwd(72, Adrivespe, 8);
  vex::wait(500,vex::msec);
  arm(2,Aliftpow);
  clampOpen(-17,100);
  fwd(-30, -45, 8);
  strafeRight(-28, 60);
  turnRight(-90, Adrivespe-10);
  fwd(53, Adrivespe, 8);
  clampTime(1500, Aclamppow);
  fwd(-3, Adrivespe, 8);
  arm(60, Aliftpow);
  fwd(5, Adrivespe, 8);
  clampOpen(-30, Aclamppow);
}
 
 void usercontrol( void ) {
  turnyBoi.setHeading(180, vex::deg);
  double driveOldGyro = int(floor(turnyBoi.heading()))%360;
  while (true) {

    god.Screen.clearScreen();
    /*
    MCkun.Screen.setCursor(0, 0);
    MCkun.Screen.clearScreen();
    MCkun.Screen.print("Clamp: %.0f", clamp.temperature(vex::temperatureUnits::celsius));
    MCkun.Screen.ne
  turnRight(90, 35);
  fwd(50,40);
  fwd(-50,-40);
}
 
 void usercontrol( void ) {
  turnyBoi.setHeading(180, vex::deg);
  double driveOldGyro = int(floor(turnyBoi.heading()))%360;
  while (true) {

    god.Screen.clearScreen();
    /*
    MCkun.Screen.setCursor(0, 0);
    MCkun.Screen.clearScreen();
    MCkun.Screen.print("Clamp: %.0f", clamp.temperature(vex::temperatureUnits::celsius));
    MCkun.Screen.newLine();
    MCkun.Screen.print("LL: %.0f", liftLD.temperature(vex::temperatureUnits::celsius));
    MCkun.Screen.newLine();
    MCkun.Screen.print("LR: %.0f",liftRD.temperature(vex::temperatureUnits::celsius));
    MCkun.Screen.setCursor(1, 10);
    MCkun.Screen.print("strafe: %.0f", mDrive.temperature(vex::temperatureUnits::celsius));
    */
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
    
    /*if((SCkun.ButtonR1.pressing()||SCkun.ButtonL1.pressing()) && (abs(MCkun.Axis2.value()) < 2 && abs(MCkun.Axis3.value()) < 2)){
      double newGyro = int(floor(turnyBoi.heading()))%360;
      double d1 = fabs(newGyro - driveOldGyro);
      if(d1 > 10){
        driveStrafeCorrect(driveOldGyro, newGyro, d1);
      }
    }
    else{
      print(2);*/
      leftF.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);
      rightF.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct);
      leftB.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);
      rightB.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct);
      //turnyBoi.setHeading(180, vex::deg);
    //}
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
