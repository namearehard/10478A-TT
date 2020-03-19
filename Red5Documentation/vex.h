/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

//#include "robot-config.h"
/*
The line above is included by default in new projects, but in order to use our own Motors file,
we note it out because we deleted that file. That file allows you to use the graphical motor
setup, but we much prefer to use our own custom one. 
Unnote this if you want graphical, benefits of text over graphical setup are detailed in Motors.h file.
*/

//dont worry about anything else here, we dont need to know what it does either, just dont delete it
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
