#include <PI_Pneumatics.h>//include the .h file of PI_Pneumatics

PI_Pneumatics::PI_Pneumatics()
{
    
}
 


void PI_Pneumatics::OpenPiston()//function to fully open a piston 
{
pistons.Set(frc::DoubleSolenoid::Value::kForward);//comand open piston
}


void PI_Pneumatics::ClosePiston()//function to fully close a piston
{
pistons.Set(frc::DoubleSolenoid::Value::kForward);//comand close piston
}

void PI_Pneumatics::PistonStatus()
{
 virtual value frc::DoubleSolenoid::Get ()const;   
}
