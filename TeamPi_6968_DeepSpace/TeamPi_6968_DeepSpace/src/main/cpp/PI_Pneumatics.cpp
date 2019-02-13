#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(int one,int two, int re, int ex)
{
int _one = one;
int _two = two;
int _ex = ex;
int _re = re;
}

void PI_Pneumatics::OpenPiston()//function to fully open a piston 
{
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
}

bool PI_Pneumatics::PistonStatus()
{
    if (frc::DigitalInput(_ex).Get()) return frc::DigitalInput(_ex).Get();
    if (frc::DigitalInput(_re).Get()) return frc::DigitalInput(_re).Get();
}

 