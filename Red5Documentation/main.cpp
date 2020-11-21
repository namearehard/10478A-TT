#include "Functions.h" //includes all functions and motor definitions we're gonna use

 void preAuton(){
   //stuff you might wanna do before auton starts
 }
 
 void autonomous( void ) {  //our autonomous routine is paetially defined using functions in functions.h
  //this first portion releases all mechanisms, like hinging claw, at the same time to make auton faster
  liftLD.spin(vex::fwd, -Aliftpow, vex::pct); //start lifting the arm but dont brake it yet, Aliftpow is defined in functions.h
  liftRD.spin(vex::fwd, -Aliftpow, vex::pct);
  clamp.resetRotation(); //reset claw position to refer to claw rotations later
  clamp.resetPosition();
  clamp.spin(vex::fwd, -Aclamppow-40, vex::pct) //open claw while lift is being lifted
  vex::task::sleep(300); //wait 0.3 secs
  liftStop();
  clampStop(); //stop moving claw and lift after 0.3 secs
  liftLD.resetRotation(); //rest position of list to refer to later, we do it here because its good enough
  liftLD.resetPosition();
  liftRD.resetRotation();
  liftRD.resetPosition();
  track.resetRotation();  //reset tracking wheel of strafe to 0 rotations/degrees

  //now we properly start routine by manipulating objects, pretty much everything used here are functions from functions.h
  //these will be movement functions we created specifically to make autonomous code easy to write, and implement more complex movement like PID
  clampOpen(-65, Aclamppow + 40);  //move clamp using clampOpen in functions, by 65 degrees, and real fast so we add 40 to the speed
  driveForwards(10, Adrivespe);  //drive forwards 10cm as defined in functions.h
  arm(10, Aliftpow, false, 0, true);  //move arm to 10 degrees, (this is why we reset position) refer to arm function
  driveForwards(35, Adrivespe);  //drive forwards 35cm
  driveBackwards(2.3, Adrivespe);  //drive backwards 2.3cm
  arm(-2, Aliftpow, false, 0, true);  //move arm to -2 degrees of the arm from when we reset position
  clampTime(700, Aclamppow+40); //open clamp for 7 secs
  clampStop();  //stop clamp
  arm(10, Aliftpow+20, false, 0, true);  //raise arm to 10 degrees
  strafeRight(1.5, 100); //strafe 1.5cm to the right, full speed
  arm(52.5, Aliftpow-20, false, 0, true);  //raise arm to 52.5 degrees above the stack
  driveForwards(20.5, Adrivespe);  //drice 20.5cm to approach stack
  vex::task::sleep(500);  //little break to stop any momentum swings
  clampOpen(-80, Aclamppow + 40);  //open clamp fast
  arm(-2, Aliftpow + 15, false, 0, false);  //put arm to -2 degrees
  while(liftLD.isSpinning()){}  //loop to make sure lift finishes movement
  clampTime(300, Aclamppow+40);  //closes clamp for 0.3 secs quickly
  clampStop();

  arm(10, Aliftpow, false, 0, true);  //lifts stack up
  holdArm();  //brake the lift using hold function to not sag
  driveBackwards(60, 100);  //drive backwards 60cm full speed
  turnRightFor(-107, 30); //turn left 107 degrees, at 30% speed

  driveForwards(75, 100);  //go forwards 75cm, full speed
  vex::wait(500,vex::msec);  //wait a bit to control momentum swings
  arm(-2,Aliftpow, true, 0.8, true);  //put lift down
  driveTime(-100, 100);  //drive backwards for 0.1 secs
  driveStop();  //stop drive
  arm(2,Aliftpow, true, 0.8, true);  //raise arm a bit
  vex::wait(400, vex::msec);  //wait for momentum swings
  clampOpen(-17,100);  //open clamp
  driveBackwards(30, 45); // drive backwards
}
 
 void usercontrol( void ) { //driver control is defined here
  turnyBoi.setHeading(180, vex::deg);  //sets where the gyro is facing as 180 degrees
  double driveOldGyro = int(floor(turnyBoi.heading()))%360; //old exeprimental code, not used at all, only in commented block
  while (true) { //all driver code is in loop so robot can continuously respond to controller

    god.Screen.clearScreen(); //clear screen to rewrite things on
    god.Screen.printAt(150, 30, "clamp: %7.2f",clamp.temperature(vex::temperatureUnits::celsius)); //prints temps of the claw on the brain screen
    god.Screen.printAt(150, 50, "leftLift: %7.2f",liftLD.temperature(vex::temperatureUnits::celsius));
    god.Screen.printAt(150, 70, "rightLift: %7.2f",liftRD.temperature(vex::temperatureUnits::celsius));
    god.Screen.printAt(150, 90, "strafe: %7.2f",mDrive.temperature(vex::temperatureUnits::celsius));
    god.Screen.render(); //renders the screen/shows actual text

    MCkun.ButtonL1.pressed(clampUp); //when buttonL1 is pressed, it calls and executes the clampUp function in our functions file
    MCkun.ButtonL1.released(clampStop); //when same button is let go, calls clampStop, which brakes the clamp
    MCkun.ButtonL2.pressed(clampDown); //calls clampDown so it moves in other dorection for L2
    MCkun.ButtonL2.released(clampStop); //brakes claw when L2 is let go by calling clampStop

    MCkun.ButtonR1.pressed(liftUp); //same idea as above but with lift and different buttons, just define lift movement functions and put their names in the brackets
    MCkun.ButtonR1.released(liftStop);
    MCkun.ButtonR2.pressed(liftDown);
    MCkun.ButtonR2.released(liftStop);

    //experimental trash code, doesnt work and if it does, we didnt like it, tried basic acceleration but it wasnt nice to use
    //dont worry about anything in here
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


    MCkun.ButtonA.pressed(change);  //this calls the change function when A is pressed, to change speed of the base
    MCkun.ButtonA.released(bounc);  //calls bounc function so changing behaves properly (explained in functions.h)
    driveTog();  //set speed of the base
    
    SCkun.ButtonR1.pressed(fwdStrafe);  //same idea when button is pressed use strafe wheel functions
    SCkun.ButtonR1.released(brakeStrafe);
    SCkun.ButtonL1.pressed(bkStrafe);
    SCkun.ButtonL1.released(brakeStrafe);
    
    leftF.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);  //left front wheel spins with power = joystickValue*basePower, where base power depends on driveTog/change function
    rightF.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct); //basically power depends on joystick, and to slow it down we multiply it by drivePow, which is usually less than 1
    leftB.spin(vex::fwd,MCkun.Axis3.value()*drivePow,vex::pct);
    rightB.spin(vex::fwd,MCkun.Axis2.value()*drivePow,vex::pct);
  }
 }
 
 
 int main() { //main function, just copy this, its necessary to work in comps and in general
    preAuton();
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
     
    while(1) {
      vex::task::sleep(100);
    }    
 }
