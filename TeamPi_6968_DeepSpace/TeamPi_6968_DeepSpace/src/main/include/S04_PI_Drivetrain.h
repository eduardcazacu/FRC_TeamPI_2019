/*
    The code needed to drive the 2019 robot. 
    Drive system used is differential with 3 motors per side.

    The motor configuration consists of one Talon_SRX and 2 Victor_SPXs per side

    created by Eduard Cazacu on 08 February 2019
    Team PI 6968
*/

#pragma once

#include "C00_PI_Talon.h"
#include "C01_PI_Victor.h"
#include <frc/drive/DifferentialDrive.h>
#include "PiVector3.h"
#include "frc/PIDController.h"
#include "PI_PIDSource.h"
#include "PI_PIDOutput.h"
#include "S03_PI_Positioning.h"


#define KP_R    0.005   
#define KD_R    0.001   
#define KI_R    0.001
#define KF_R    0


class S04_PI_Drivetrain
{
  public:
    /*
    
            Description:    Constructor. 
            Input:          TalonL, TalonR, Victor L1, Victor L2, Victor L3, Victor R1, Victor R2, Victor R3
            output:         none
        */
    S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2);
    S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2, S03_PI_Positioning *robotPos);
    /*
            Description:    Differential drive.
            Input:          Y [double][-1,1] - speed
                            Z [double][-1,1] - rotation 
            output:         none
    */
    void drive(double speed, double rotation);

    /*
        Description:    Rotates the robot with PID to the target orientation. Makes use of positioning 
        Input:          [PiVector3] target orientations in absolute values. e.g: you read the current position
                        of the robot and you mak the target that value + 180 to turn around.
                        Use Z axis for orientation.
        output:         [bool] target reached? falese for no , true for got there.
    */
    bool rotateTo(PiVector3 target);

  private:
    //the differential drive used:
    frc::DifferentialDrive *_diffDrive;

    C00_PI_Talon *_talonL;
    C00_PI_Talon *_talonR;
    C01_PI_Victor *_victorL1;
    C01_PI_Victor *_victorL2;
    C01_PI_Victor *_victorR1;
    C01_PI_Victor *_victorR2;

    bool usingPositioning;
    S03_PI_Positioning *robotPos;

    frc::PIDController *pid;
    PI_PIDSource *input;
    PI_PIDOutput *output;
};
