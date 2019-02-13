#include <PI_Pneumatics.h> //include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics(uint8_t fwd, uint8_t rev)
{

    //create the object:
    this->piston = new frc::DoubleSolenoid(fwd, rev);
}

void PI_Pneumatics::OpenPiston() //function to fully open a piston
{
    piston->Set(frc::DoubleSolenoid::Value::kForward); //comand open piston
}

void PI_Pneumatics::ClosePiston() //function to fully close a piston
{
    piston->Set(frc::DoubleSolenoid::Value::kReverse); //comand close piston
}

bool PI_Pneumatics::PistonStatus()
{
    //return the state of the solenoid:

    return piston->Get();
}
