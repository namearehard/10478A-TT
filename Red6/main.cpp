#include "Functions.h"

 void preAuton(){
   
 }
 
 void autonomous( void ) {
  liftLD.spin(vex::fwd, -Aliftpow, vex::pct);
  liftRD.spin(vex::fwd, -Aliftpow, vex::pct);
  clamp.spin(vex::fwd, -Aclamppow, vex::pct);
  vex::task::sleep(250); //250
  liftStop();
  liftLD.resetRotation();
  liftLD.resetPosition();
  liftRD.resetRotation();
  liftRD.resetPosition();
  clamp.resetRotation();
  clamp.resetPosition();
  track.resetRotation();
  vex::task::sleep(1300);
  clampStop();
 //250
  /*
   driveForwards(50, 60);
   godsBrake();
   strafeRight(27.5, 40);
   driveForwards(24, 45);
   godsBrake();
   arm(0, Aliftpow);
   clampTime(1000, Aclamppow);
   clampStop();
   arm(17, Aliftpow);
   holdArm();
 
   driveTime(-40, 1700);
   godsBrake(); 
   driveForwards(3,100);
   arm(17, Aliftpow);
   turnLeft(-91, 10);
   strafeTime(-100, 1000);
   //strafeRight(-19.5, 100);
   //strafeTime(-100, 2100);
   strafeRight(2, 100);
   turnLeft(-91, 10);
   arm(17, Aliftpow);
   //driveTime(30, 2500);
   driveForwards(77.7, 60);
   godsBrake();

   //arm(10, Aliftpow);
   arm(3, Aliftpow);
   clampTime(500, -Aclamppow);
   clamp.stop(vex::coast);
   driveForwards(-55, 60);
 
   leftF.spin(vex::fwd,0,vex::pct);
   rightF.spin(vex::fwd,0,vex::pct);
   leftB.spin(vex::fwd,0,vex::pct);
   rightB.spin(vex::fwd,0,vex::pct);
   driveStop();
*/
//driveForwards(100,Adrivespe);
  driveForwards(12, Adrivespe);
  arm(14, Aliftpow, false, 0, true);
  driveForwards(35, Adrivespe);
  driveBackwards(2, Adrivespe);
  clampOpen(-73, Aclamppow + 40);
  //clampTime(120, -Aclamppow);
  arm(-2, Aliftpow, false, 0, true);
  clampTime(300, Aclamppow);
  //turnRight(0, 100);
  arm(51, Aliftpow-20, false, 0, true);
  driveForwards(19, Adrivespe);
  clampOpen(-72, Aclamppow + 40);
  //clampTime(200, -Aclamppow);
  arm(-2, Aliftpow + 15, false, 0, false);
  //driveBackwards(1.5, Adrivespe - 20);
  while(liftLD.isSpinning()){}
  clampTime(400, Aclamppow);

  arm(8, Aliftpow, false, 0, true);
  holdArm();
  //print(turnyBoi.rotation());
  //oldTurnRight(-110, Adrivespe-10); //130
  turnRightFor(-132, 40);
  
  
  //print(turnyBoi.rotation());
  driveForwards(122, 100);
  vex::wait(500,vex::msec);
  arm(2,Aliftpow, true, 0.8, true);
  vex::wait(500, vex::msec);
  clampOpen(-17,100);
  driveBackwards(30, 45);
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
