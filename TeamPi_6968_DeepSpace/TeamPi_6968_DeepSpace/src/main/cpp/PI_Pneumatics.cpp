#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(int PCMID, int one,int two, int re, int ex) //constructore (controle pin one, controle pin two, pin for retraction endswitch, pin for extention endswitch)
{
int _one = one;
int _two = two;
_ex =  new frc::DigitalInput(ex);
_re =  new frc::DigitalInput(re);

solenoid = new frc::DoubleSolenoid(PCMID, one, two);
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
    solenoid->Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
    solenoid->Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
}

int PI_Pneumatics::PistonStatus()// returns the current status of the piston
{
    if (_ex->Get()) return 1;
    if (_re->Get()) return -1;
    else return 0;
}


 