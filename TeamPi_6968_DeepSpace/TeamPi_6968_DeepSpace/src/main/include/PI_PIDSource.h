/*
    This class overrides the PIDSource class to allow the variables to be set by other sources

    created by Eduard Cazacu on 14 February 2019
    Team Pi 6968
*/
#pragma once

#include "frc/PIDSource.h"

class PI_PIDSource : public frc::PIDSource{
public:

//returns the value of the input.
double PIDGet ();

//Set the value of the PID input
void Set(double value);

private:
//the value to be returned on PID request.
double _value;
};