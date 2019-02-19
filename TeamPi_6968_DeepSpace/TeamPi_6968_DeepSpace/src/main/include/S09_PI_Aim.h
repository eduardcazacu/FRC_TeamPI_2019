/*
amining the robot on a line using the Pixycame and the drivetrain sub systems

This subsystem is designed to possision the robot on top of a line(vector).
using the pixycame 

make sure the pixycame is conneced propperly and is sending the right data. 

Created by Jorn Veenendaal on 10 February 2019
Team PI 6968
*/

#pragma once

#include "frc/Timer.h"
#include "PI_PIDOutput.h"
#include "PI_PIDSource.h"
#include <frc/PIDController.h>
#include <cmath>
#include "S01_PI_Sensors.h"
#include "S04_PI_Drivetrain.h"
#include "S04_PI_Pixy.h"

class S09_PI_Aim
{
  private:
    //debugging:
    bool verbose=true;

    //pid constants:
    const double tolerance = 0.2;

    //for getting the robot parallel with the line
    const double kPAngle = 0.2;
    const double kIAngle = 0.1;
    const double KDAngle = 1.2;
    //the min max that it can write to the motors:
    const double angleMax = 0.2;
    const double angleMin = -0.2;

    //for getting the robot on top of the target point
    const double kPDist = 0.2;
    const double kIDist = 0.5;
    const double kDDist = 1;
    //the min max that it can write to the motors:
    const double distMax = 0.6;
    const double distMin = -0.6;

    //drive angle for getting the robot on top of the target point
    //this should be bigger so that it can overcome the alignment PID in the beginning.
    const double kPDriveAngle = 0.6;  
    const double kIDriveAngle = 0.9;
    const double KDDriveAngle = 0.2;
    //the min max that it can write to the motors:
    const double driveAngleMax = 0.6;
    const double driveAngleMin = -0.6;

    /*FPID values */
    frc::PIDController *PIDAngle;
    frc::PIDController *PIDDistance;
    frc::PIDController *PIDDistanceAngle;

    /* PID calculation values*/
    bool PIDStarted;
    double distanceError;
    double intersectionError;
    double driveSpeed;
    double driveAngle;

    //PID source and Output
    PI_PIDSource *AngleSource = new PI_PIDSource();
    PI_PIDOutput *AngleOutput = new PI_PIDOutput();
    PI_PIDSource *DistanceSource = new PI_PIDSource();
    PI_PIDOutput *DistanceOutput = new PI_PIDOutput();
    PI_PIDSource *DistanceAngleSource = new PI_PIDSource();
    PI_PIDOutput *DistanceAngleOutput = new PI_PIDOutput();

    /*system variables*/
    double errorAngle, errorDistance;
    double maxSpeedPercentage;

    /*Place holders*/
    double PLACEHOLDER0, PLACEHOLDER2;

    //for driving:
    S04_PI_Drivetrain *drivetrain;


  public:
    /*  description: constructor
        Paremeters:  maxSpeedPercentage, drivetrain object (pointer)
        output:      -
    */
    S09_PI_Aim(double _maxSpeedPercentage, S04_PI_Drivetrain *drivetrain);

    /*
       Description: Aligns the robot to a vector given by a starting point and an angle.
       Input:       targetAngle [double] - the angle of the line relative to the robot.
                    targetX [double] - the x position of the target point
                    targetY [double] - the y coordinate of the position of the target point
        Return:     Is completed? true for there, false for not there yet.
    */

    bool Aim(double targetAngle, double targetX, double targetY);

    /*
        change the PID values on the fly for testing:
    */
    void changePID();
};
