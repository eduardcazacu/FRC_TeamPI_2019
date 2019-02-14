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

class M00_PI_Manual
{
  public:
    /*
        Description:    Constructor.
    */
    M00_PI_Manual(S02_PI_Input *input,S05_PI_Lift *lift, bool verbose = 0);

    void driving();
    void functions();

  private:
    //motors:
    C00_PI_Talon *talonL;
    C00_PI_Talon *talonR;
    C01_PI_Victor *victorL1;
    C01_PI_Victor *victorL2;
    C01_PI_Victor *victorR1;
    C01_PI_Victor *victorR2;

    S04_PI_Drivetrain *drivetrain;

    //input:
    S02_PI_Input *_input;

    //special functions:
    S05_PI_Lift *_lift;
};