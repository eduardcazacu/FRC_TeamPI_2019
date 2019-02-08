/*
This class handles all the user input coming from the driver station.

Created by Eduard Cazacu on 05 February 2019
Team Pi 6968
*/

#pragma once

#include <Joystick.h>

class S02_PI_Input
{
private:


public:
frc::Joystick m_stick { 0 };	//main joystick for driving;

/*
Description:    Get all the input the needs to be refreshed periodically
Input:          None;
Output:         None;
*/
void refresh();

};