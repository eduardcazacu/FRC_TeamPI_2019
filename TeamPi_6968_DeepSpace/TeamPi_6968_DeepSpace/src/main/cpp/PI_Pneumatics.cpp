#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

<<<<<<< HEAD
PI_Pneumatics::PI_Pneumatics(int pin1,int pin2, int re, int ex) //constructore (controle pin one, controle pin two, pin for retraction endswitch, pin for extention endswitch)
{
_solenoid = new frc::DoubleSolenoid(pin1,pin2);

_extended = new frc::DigitalInput(ex);
_retrected = new frc::DigitalInput(re);
=======
PI_Pneumatics::PI_Pneumatics(int PCMID, int one,int two, int re, int ex) //constructore (controle pin one, controle pin two, pin for retraction endswitch, pin for extention endswitch)
{
int _one = one;
int _two = two;
_ex =  new frc::DigitalInput(ex);
_re =  new frc::DigitalInput(re);

solenoid = new frc::DoubleSolenoid(PCMID, one, two);
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
<<<<<<< HEAD
    _solenoid->Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
=======
    solenoid->Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
<<<<<<< HEAD
    _solenoid->Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
=======
    solenoid->Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
}

int PI_Pneumatics::PistonStatus()// returns the current status of the piston
{
<<<<<<< HEAD
    if (_extended->Get()) return 1;
    if (_retrected->Get()) return 0;
    else return 2;
=======
    //the digital pin is pulled up so when the switch reads an action
    //the digital pin becomes 0:
    if (!_ex->Get()) return 1;
    if (!_re->Get()) return -1;
    else return 0;
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
}


 