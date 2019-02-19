/*
An class which houses all the sensors used by the robot.

Created by Eduard Cazacu on 05 February 2019
Team Pi 6968

licensed under the FIRST BSD license
*/

#pragma once

#include "PI_Constants.h"

//Add the headers for all the sensors here:
#include "C05_PI_Ultrasoon.h"
#include "PI_IR.h"
#include "C04_PI_Pixy.h"
#include "C03_PI_Camera.h"

const double ULTRASONICWIDTH = 232;

class S01_PI_Sensors
{
private:

public:
//constructor:
S01_PI_Sensors();

//refresh all sensors that need to be periodically refreshed 
void refresh();

double GetUltrasonicAngle();

//create a pointer for each object here and initialize it in the constructor  
//ultrasound sensors:
C05_PI_Ultrasoon *USLeft;
C05_PI_Ultrasoon *USRight;
//Ir sensors:
PI_IR *IRFront;
PI_IR *IRBack;
//Pixy cams:
C04_PI_Pixy *PixyDown; //For lines on the ground
//C04_PI_Pixy *PixyUp; //For the lines on the rocket

//camera
C03_PI_Camera *camera;
};