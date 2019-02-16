
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
        //do nothing
        return false;
    case 1:
<<<<<<< HEAD
        //turn 180 degree
        return drivetrain.Rotate();
=======
        return (_climbSystem->extendAll());
>>>>>>> 94db83807c2b83bee2b768eca62fbbf93c68784e
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

*/