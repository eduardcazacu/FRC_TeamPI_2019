/*
amining the robot on a line using the Pixycame and the drivetrain sub systems

This subsystem is designed to possision the robot on top of a line(vector).
using the pixycame 

make sure the pixycame is conneced propperly and is sending the right data. 

Created by Jorn Veenendaal on 10 February 2019
Team PI 6968
*/
#include "frc/Timer.h"
#include "PI_PIDOutput.h"
#include "PI_PIDSource.h"
#include <PIDBase.h>
#include <cmath>
#include <PIDSource.h>
#include <PIDOutput.h>
#include "S01_PI_Sensors.h"

class S09_PI_Aim
{
private:
    /*FPID values */
    frc::PIDBase::PIDBase PIDCorner;
    frc::PIDBase::PIDBase PIDDistance; 

    /* PID calculation values*/
    double setangle, setDistance;


    //PID source and Output
    PI_PIDSource *CornerSource = new PI_PIDSource();
    PI_PIDOutput *CornerOutput = new PI_PIDOutput();
    PI_PIDSource *DistanceSource = new PI_PIDSource();
    PI_PIDOutput *DistanceOutput = new PI_PIDOutput();
   
    // pixy data 
    double PixyCorner;
    double PixyDistance;

    /*system variables*/ 
    double errorAngle, errorDistance;
    double maxSpeed;

    /*Place holders*/
    double PLACEHOLDER0, PLACEHOLDER2;

public:
    /*  description: constructor
        Paremeters:  pixy, drivetrain, kP,kI,kD,kF 
        output:      -
    */
    S09_PI_Aim(double _kP, double _kI, double _kD, double _kF);

    /*
        Description:  uses the  FPID value to calculate the next motor input
        Parameter:    Set angle standerd 0 [rad], _setDistance in pixels,_setErrorMargenCorner = error in %,  _setErrorMargenDistance = error in %
        output:       1 = error, 0 no error   
    */

    bool Aim(double Setangle, double SetDistance);

    /*
        Description:    Use to run the pid loop. you can set a set point but it will use it previously set setpoint and drive to wards it
        Paramter:       -
        Output:         0 not in error margen, 1 within error margen
    */
    bool UpdateAim();

    /*
        Description: this mehtod will convert the cante in angle in to a change in motor speed
        Paremeters:  Change in angle,
        Output:      chang in motor Speed.
    */
    double DrivtrainConverter(/*change in angle*/);    
};



