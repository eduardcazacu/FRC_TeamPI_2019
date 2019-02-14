
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
        return false;
    case 1:
        return (front->PneuOut() && back->PneuOut());
    case 2:
        front->Drive(speed);
        return (back->Drive(speed));
    case 3:
        return (back->PneuIn());
    case 4:
        //move drivetrain here
        return (front->Drive(speed));
    case 5:
        return (front->PneuIn());
    case 6:
        //drive forward
        return false;
    }

}