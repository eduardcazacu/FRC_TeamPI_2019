#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(int pin1,int pin2, int re, int ex) //constructore (controle pin one, controle pin two, pin for retraction endswitch, pin for extention endswitch)
{
_solenoid = new frc::DoubleSolenoid(pin1,pin2);

_extended = new frc::DigitalInput(ex);
_retrected = new frc::DigitalInput(re);
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
    _solenoid->Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
    _solenoid->Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
}

int PI_Pneumatics::PistonStatus()// returns the current status of the piston
{
    if (_extended->Get()) return 1;
    if (_retrected->Get()) return 0;
    else return 2;
}


 