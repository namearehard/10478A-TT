#include "vex.h"
vex::brain god;
vex::controller MCkun;
vex::controller SCkun = vex::controller(vex::controllerType::partner);
vex::motor leftF = vex::motor(vex::PORT1);
vex::motor rightF = vex::motor(vex::PORT6,true);
vex::motor leftB = vex::motor(vex::PORT13);
vex::motor rightB = vex::motor(vex::PORT12,true);
vex::motor mDrive = vex::motor(vex::PORT11, vex::ratio36_1); //11
vex::motor liftLU = vex::motor(vex::PORT7,true);
vex::motor liftLD = vex::motor(vex::PORT7,vex::ratio36_1,true);
vex::motor liftRU = vex::motor(vex::PORT14);
vex::motor liftRD = vex::motor(vex::PORT14,vex::ratio36_1);
vex::motor clamp = vex::motor(vex::PORT15,vex::ratio36_1, true); //18, 16, 17, 19, 20
vex::motor claw = vex::motor(vex::PORT22);
vex::inertial turnyBoi = vex::inertial(vex::PORT4);

vex::encoder track = vex::encoder(god.ThreeWirePort.C);
vex::encoder fwdTrack = vex::encoder(god.ThreeWirePort.G);
vex::competition Competition;
