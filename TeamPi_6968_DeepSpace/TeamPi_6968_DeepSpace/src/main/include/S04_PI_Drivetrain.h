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
#include "S01_PI_Sensors.h"

#define timeOutMS 10

class S04_PI_Drivetrain
{
  public:
    /*
    
            Description:    Constructor. 
            Input:          TalonL, TalonR, Victor L1, Victor L2, Victor L3, Victor R1, Victor R2, Victor R3
            output:         none
        */
    S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2, S01_PI_Sensors *_sensors);
    S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2, S01_PI_Sensors *_sensors, S03_PI_Positioning *robotPos);
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
        output:         [bool] target reached? false for no , true for got there.
    */
    bool Rotate(double angle);

    /*
        Description:    Drive a certain distance. No fancy PID yet.
        Input:          [double] distance in mm;
        Output:         [bool] reached the target? false=  not yet.       
    */
    bool driveDist(double distance);

    bool AimToWall();

    //Ramp rate variabels
    int rampTimeOpenLoop= 0.8;
    int rampTimeClosedloop =0.8;

  private:

    //pid constants:
    const double KP_R = 0.005;
    const double KD_R = 0.001;
    const double KI_R = 0.001;
    const double KF_R = 0;
    const double errorTolerance = 1;

    //the differential drive used:
    frc::DifferentialDrive *_diffDrive;

    C00_PI_Talon *_talonL;
    C00_PI_Talon *_talonR;
    C01_PI_Victor *_victorL1;
    C01_PI_Victor *_victorL2;
    C01_PI_Victor *_victorR1;
    C01_PI_Victor *_victorR2;

    S01_PI_Sensors *sensors;

    //auto rotation:
    bool usingPositioning;
    bool pidRotationStarted = false;
    S03_PI_Positioning *_robotPos;

    frc::PIDController *pidRotation;
    PI_PIDSource *input;
    PI_PIDOutput *output;

    double targetAngle;
    int turnDirection; //which way should the robot turn. -1 =  counter clockwise

    //normalize the angle to 0,359
    double normalizeAngle(double angle);

    //auto drive forward:
    double targetDistance;
    bool autoDriveStarted = false;

    const double autoDriveSpeed = 0.2;

    bool AimIndex = true;
    double AimAngle = 0;
};
