/*
    Keeping track of the robot's position on the field based on the readings from the encoders.
    Driving for long distances and turning will increase the absolute error of the positioning data.
    It is recommended that the position is reset as often as possible at known positions(rockets etc)

    Created by Eduard Cazacu on 09 February 2019
    Team PI 6968
*/

#pragma once

#define DRIVETRAIN_WIDTH 40

//the custom talon class that also has the encoder distance calculations:
#include "C00_PI_Talon.h"
#include "PiTransform.h"

class S03_PI_Positioning
{
public:
    /*
        Description:    Constructor
        Input:          Left and Right Talon objects with encoder support [C00_PI_Talon]
        Output:         None
    */
    S03_PI_Positioning(C00_PI_Talon* leftEnc, C00_PI_Talon* rightEnc, double drivetrainWidth = DRIVETRAIN_WIDTH);
    /*
        Description:    Get the transform object that stores the position, speed etc of the robot
        Input:          None
        Output:         [PiTransform] robot transform (position, orientation, speed etc)
    */
    PiTransform* Get();
    /*
        Description:    some methods need to be called regularly to know the current position. These
                        methods are being called by calling refresh()
        Input:          None
        Output:         none;
    */

   /*
        Description:    return the distance traveled in any direction
        input:          none
        Output:         [double] total distance travelled.
   */
   double getDistance();
    void refresh();
    /*
        Description:    reset the current position of the robot to a new known one to remove the error
        Input:          (Optional, by default 0,0) [PiTransform] newPos - the new position of the robot.
        Output:         None
    */
    void reset(PiTransform newPos);
    void reset();
private:
    double _drivetrainWidth;
    //store the robot position
    PiTransform *_pos;
    //encoder objects:
    C00_PI_Talon *_lEnc;
    C00_PI_Talon *_rEnc;

    double totalDistance;

};