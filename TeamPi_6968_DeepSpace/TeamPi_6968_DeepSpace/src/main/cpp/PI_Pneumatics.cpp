#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(int one,int two, int re, int ex) //constructore (controle pin one, controle pin two, pin for retraction endswitch, pin for extention endswitch)
{
int _one = one;
int _two = two;
int _ex = ex;
int _re = re;
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
}

int PI_Pneumatics::PistonStatus()// returns the current status of the piston
{
    if (frc::DigitalInput(_ex).Get()) return 1;
    if (frc::DigitalInput(_re).Get()) return 0;
    else return 2;
}


 