/*
This class compiles together all the code needed for the mnaual functions of the robot
such as driving or moving robot parts

include all the code that has to do with manual controls here.

created by Eduard Cazacu on 13 February 2019
Team PI 6968

*/

#pragma once

#include "S05_PI_Lift.h"
#include "C00_PI_Talon.h"
#include "C01_PI_Victor.h"
#include "S04_PI_Drivetrain.h"
#include "S02_PI_Input.h"
#include "PI_Climb.h"
#include "S06_PI_Grabber.h"

class M00_PI_Manual
{
public:
  /*
  When this in true, all automatic functions are skipped and reset and the driver regains manual controll
  */
  bool manualOverride = false;

  /*
        Description:    Constructor.
    */
  M00_PI_Manual(S04_PI_Drivetrain *drivetrain, S02_PI_Input *input, S05_PI_Lift *lift, /*PI_Climb *climbSystem,*/ S06_PI_Grabber *grabber, bool verbose = 0);

  void init();
  void driving();
  void functions();

private:
  double turnSpeedMultiplier = 0.7;
  double minimumAcceleration = 0.2;
  double maxAcceleration = 2;

  S04_PI_Drivetrain *_drivetrain;

  //input:
  S02_PI_Input *_input;

  //special functions:
  S05_PI_Lift *_lift;

  //climb system:
  PI_Climb *_climbSystem;

  //gripping system
  S06_PI_Grabber *_grabber;

  bool *calibrated;
  double map(double x, double xMin, double xMax, double yMin, double yMax);


};