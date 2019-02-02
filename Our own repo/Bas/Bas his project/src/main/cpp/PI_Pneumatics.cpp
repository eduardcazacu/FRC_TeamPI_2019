#ifndef SRC_PI_PNEUMATICS_CPP_
#define SRC_PI_PNEUMATICS_CPP_

#include "PI_Pneumatics.h"

PI_Pneumatics::PI_Pneumatics()
{
     
}

void PI_Pneumatics::OpenPiston()
{
pistons.Set(DoubleSolenoid::Value::kForward);
}

void PI_Pneumatics::ClosePiston()
{
pistons.Set(DoubleSolenoid::Value::kReverse);
}

#endif