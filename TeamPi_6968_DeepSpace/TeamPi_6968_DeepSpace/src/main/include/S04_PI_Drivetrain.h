/*
    The code needed to drive the 2019 robot. 
    Drive system used is differential with 3 motors per side.

    The motor configuration consists of one Talon_SRX and 2 Victor_SPXs per side

    created by Eduard Cazacu on 08 February 2019
    Team PI 6968
*/

#pragma once

#include "frc/WPILib.h"
#include "C00_PI_Talon.h"
#include "C01_PI_Victor.h"

class S04_PI_Drivetrain
{
  public:
    /*
            Description:    Constructor. 
            Input:          TalonL, TalonR, Victor L1, Victor L2, Victor L3, Victor R1, Victor R2, Victor R3
            output:         none
        */
    S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2);

    /*
            Description:    Differential drive.
            Input:          Y [double][-1,1] - speed
                            Z [double][-1,1] - rotation 
            output:         none
    */
   void drive(double speed, double rotation);

  private:

    //the differential drive used:
  DifferentialDrive *_diffDrive =  new DifferentialDrive();

  C00_PI_Talon *_talonL,_talonR;
  C01_PI_Victor *_victorL1,*_victorL2,*_victorR1,*_victorR2;

};
