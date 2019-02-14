
#pragma once

#include "PI_IR.h"
#include "S04_PI_Drivetrain.h"
#include "PI_Pneumatics.h"
#include "C01_PI_Victor.h"

class PI_Sub_Climb
{

  private:
    PI_Pneumatics *leftPnue;
    PI_Pneumatics *rightPnue;

    C01_PI_Victor *leftMotor;
    C01_PI_Victor *rightMotor;

    PI_IR *infrared;

  public:
    PI_Sub_Climb(PI_Pneumatics _leftPnue, PI_Pneumatics _rightPnue,
                 C01_PI_Victor _leftMotor, C01_PI_Victor _rightMotor,
                 PI_IR _infrared);
    bool PneuOut();
    bool PneuIn();
    bool Drive(double speed);
};

class S07_PI_AutoClimb
{

  private:
    PI_Sub_Climb* back;
    PI_Sub_Climb* front;
    int oldIndex = index;
    bool NextOption();
    double speed = 0.2;

  public:
    S07_PI_AutoClimb();
    int index = 0;
    bool climb();
};
