/*
Overrided the PIDOutput class to use variables.

created by Eduard Cazacu on 14 February 2019
Team I 6968
*/

#pragma once

#include "frc/PIDOutput.h"

class PI_PIDOutput : public frc::PIDOutput
{
  public:
  //store the pid output in this object. USed by the PID loop
    void PIDWrite(double output);

    /*
    Get the PID output
    */
    double Get();

    private:
    double _output;
};