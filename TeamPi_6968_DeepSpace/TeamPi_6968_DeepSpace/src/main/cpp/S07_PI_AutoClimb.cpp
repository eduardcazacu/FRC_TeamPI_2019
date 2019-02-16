
#include "S07_PI_AutoClimb.h"


S07_PI_AutoClimb::S07_PI_AutoClimb(PI_Climb *_climbSystem, S04_PI_Drivetrain *_drivetrain)
{
    climbSystem = _climbSystem;
    drivetrain = _drivetrain;
}
/*

bool S07_PI_AutoClimb::climb()
{

    

    if (NextOption())
    {
        if(index<9)
        index++;
        else
        index = 0;
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
        //do nothing
        return false;
    case 2:
        r
    case 3:
        return (climbSystem->extendAll());
    case 4:
        return (front->PneuOut() && back->PneuOut());
    case 5:
        return (front->Drive(speed));
    case 6:
        return (back->PneuIn());
    case 7:
        //move drivetrain here
        return (front->Drive(speed));
    case 8:
        return (front->PneuIn());
    case 9:
        //drive forward
        return false;
    }

}*/

