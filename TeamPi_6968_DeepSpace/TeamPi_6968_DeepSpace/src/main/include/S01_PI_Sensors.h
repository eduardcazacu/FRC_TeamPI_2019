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
#include "PI_Pixy.h"

class S01_PI_Sensors
{
private:

public:
//constructor:
S01_PI_Sensors();

//refresh all sensors that need to be periodically refreshed 
void refresh();

//create a pointer for each object here and initialize it in the constructor  
//ultrasound sensors:
C05_PI_Ultrasoon *USLeft;
C05_PI_Ultrasoon *USRight;
//Ir sensors:
PI_IR *IRFront;
PI_IR *IRBack;
//Pixy cams:
};