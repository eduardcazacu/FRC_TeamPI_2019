<<<<<<< HEAD
#include "PI_Pneumatics.h"//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(int one,int two, int re, int ex)
{
int _one = one;
int _two = two;
int _ex = ex;
int _re = re;
=======
#include <PI_Pneumatics.h> //include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(uint8_t fwd, uint8_t rev)
{

    //create the object:
    this->piston = new frc::DoubleSolenoid(fwd, rev);
>>>>>>> f0e9bb8107631b7c1f0ae5e62eb79c7e8c217fa7
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
<<<<<<< HEAD
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}

void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
    frc::DoubleSolenoid(_one,_two).Set(frc::DoubleSolenoid::Value::kReverse);//comand close piston
=======
    piston->Set(frc::DoubleSolenoid::Value::kForward); //comand open piston
}

void PI_Pneumatics::ClosePiston() //function to fully close a piston
{
    piston->Set(frc::DoubleSolenoid::Value::kReverse); //comand close piston
>>>>>>> f0e9bb8107631b7c1f0ae5e62eb79c7e8c217fa7
}

bool PI_Pneumatics::PistonStatus()
{
<<<<<<< HEAD
    if (frc::DigitalInput(_ex).Get()) return frc::DigitalInput(_ex).Get();
    if (frc::DigitalInput(_re).Get()) return frc::DigitalInput(_re).Get();
=======
    //return the state of the solenoid:

    return piston->Get();
>>>>>>> f0e9bb8107631b7c1f0ae5e62eb79c7e8c217fa7
}

 