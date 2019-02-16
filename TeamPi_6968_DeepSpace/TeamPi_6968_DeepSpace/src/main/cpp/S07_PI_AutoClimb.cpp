
#include "S07_PI_AutoClimb.h"


S07_PI_AutoClimb::S07_PI_AutoClimb(PI_Climb *climbSystem, S04_PI_Drivetrain *drivetrain)
{
    _climbSystem = climbSystem;
    _drivetrain = drivetrain;
}

/*
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

//No breaks? :
bool S07_PI_AutoClimb::NextOption()
{
    switch (index)
    {
    case 0:
        return false;
    case 1:
        return (_climbSystem->extendAll());
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

*/