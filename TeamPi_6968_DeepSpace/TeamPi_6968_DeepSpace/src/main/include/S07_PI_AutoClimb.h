
#pragma once

#include "PI_IR.h"
#include "S04_PI_Drivetrain.h"
#include "PI_Climb.h"
#include "S01_PI_Sensors.h"

class S07_PI_AutoClimb
{

  private:
    PI_Climb *climbSystem;
    S04_PI_Drivetrain *drivetrain;
    S01_PI_Sensors *sensors;

    int oldIndex = index;
    bool NextOption();
    double extraTurnAngle;
    double speed = 0.2;


  public:
    /*
      Description:  Create an auto climb object based ine 
    */
    S07_PI_AutoClimb(PI_Climb *_climbSystem, S04_PI_Drivetrain *_drivetrain, S01_PI_Sensors *_sensors);
    int index = 0;
    bool climb();
};
