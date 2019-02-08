/*
This class handles all the user input coming from the driver station.

the driver and navigator are separated into two objects.

Created by Eduard Cazacu on 05 February 2019
Team Pi 6968
*/

#pragma once

#include "PI_Constants.h"
#include "PI_Driver.h"
#include "PI_Navigator.h"

class S02_PI_Input
{
  private:
  public:
    S02_PI_Input();

    PI_Driver *driver;
    PI_Navigator *navigator;

    /*
Description:    Get all the input the needs to be refreshed periodically
Input:          None;
Output:         None;
*/
    void refresh();
};
