
#include "S07_PI_AutoClimb.h"

//////////Sub Climb
PI_Sub_Climb::PI_Sub_Climb(PI_Pneumatics _leftPnue, PI_Pneumatics _rightPnue,
                           C01_PI_Victor _leftMotor, C01_PI_Victor _rightMotor,
                           PI_IR _infrared)
{
    leftPnue = &_leftPnue;
    rightPnue = &_rightPnue;

    leftMotor = &_leftMotor;
    rightMotor = &_rightMotor;

    infrared = &_infrared;
}

bool PI_Sub_Climb::Drive(double speed)
{
    leftMotor->GetVictorObject()->Set(speed);
    rightMotor->GetVictorObject()->Set(speed);
    return infrared->objectInRange();
}

bool PI_Sub_Climb::PneuOut()
{
    leftPnue->OpenPiston();
    rightPnue->OpenPiston();
    return (leftPnue->PistonStatus() && rightPnue->PistonStatus());///Fix me!!!!!
}

bool PI_Sub_Climb::PneuIn()
{
    leftPnue->ClosePiston();
    rightPnue->ClosePiston();
    return (!leftPnue->PistonStatus() && !rightPnue->PistonStatus());///Fix me!!!!!
}

/////////////////////////////////////////////////////////////

S07_PI_AutoClimb::S07_PI_AutoClimb()
{
    //back = new PI_Sub_Climb(.............);
    //front = new PI_Sub_Climb(............)
}

bool S07_PI_AutoClimb::climb()
{

    if (oldIndex != index)
    {
        if (index != 0)
        {
            index = 0;
        }
        else
        {
            index = 1;
        }
    }

    if (NextOption())
    {
        index++;
        oldIndex = index;
        return true;
    }
    return false;
}

bool S07_PI_AutoClimb::NextOption()
{
    
    switch (index)
    {
    case 0:
        //do nothing
        return false;
    case 1:
        //turn 180 degree
        return drivetrain.Rotate();
    case 2:
        //use ultrasonic to get straight in front of wall
        return false;
    case 3:
        return (front->PneuOut() && back->PneuOut());
    case 4:
        return (front->Drive(speed));
    case 5:
        return (back->PneuIn());
    case 6:
        //move drivetrain here
        return (front->Drive(speed));
    case 7:
        return (front->PneuIn());
    case 8:
        //drive forward
        return false;
    }

}