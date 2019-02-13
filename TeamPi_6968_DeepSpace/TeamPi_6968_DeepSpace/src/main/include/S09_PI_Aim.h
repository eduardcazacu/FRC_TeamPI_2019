/*
amining the robot on a line using the Pixycame and the drivetrain sub systems

This subsystem is designed to possision the robot on top of a line(vector).
using the pixycame 

make sure the pixycame is conneced propperly and is sending the right data. 

Created by Jorn Veenendaal on 10 February 2019
Team PI 6968
*/
#include "frc/Timer.h"
#include <cmath>

class S09_PI_Aim
{
private:
    /*FPID values */
    double kP, kI, kD, kF;
    double OldError;
    double errorInter;
    double Error;
    double AngleChange;

    /*system variables*/
    int quadrent;
    double currentAngle;
    //timer
    int pixyWidth = 200;
    int Xcenter = pixyWidth/2;

public:
    /*  description: constructor
        Paremeters:  pixy, drivetrain, kP,kI,kD,kF 
        output:      -
    */
    S09_PI_Aim(double _kP, double _kI, double _kD, double _kF);

    /*
        Description:  uses the  FPID value to calculate the next motor input
        Parameter:    Set angle standerd 0 [rad]
        output:       1 = error, 0 no error   
    */

    bool Aim(double SetAngle);

    /*
        Description: this mehtod will convert the cante in angle in to a change in motor speed
        Paremeters:  Change in angle,
        Output:      chang in motor Speed.
    */
    double DrivtrainConverter(/*change in angle*/);    
};



