
#include "S07_PI_AutoClimb.h"


S07_PI_AutoClimb::S07_PI_AutoClimb(PI_Climb *_climbSystem, S04_PI_Drivetrain *_drivetrain, S01_PI_Sensors *_sensors)
{
    climbSystem = _climbSystem;
    drivetrain = _drivetrain;
    sensors = _sensors;
}

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

//No breaks? : Breaking takes time
bool S07_PI_AutoClimb::NextOption()
{
    
    switch (index)
    {
    case 0:
        //do nothing
        return false;
    case 1:
        extraTurnAngle = sensors->GetUltrasonicAngle();
        return true;
    case 2:
        //get straight in front 
        return drivetrain->Rotate(180+extraTurnAngle);
    case 3:
        climbSystem->extendAll();
        return (climbSystem->getAll()==1);
    case 4:
        climbSystem->drive(speed);
        return (sensors->IRBack->objectInRange());
    case 5:
        climbSystem->drive(0);
        climbSystem->retractBack();
        return (climbSystem->getBack()==-1);
    case 6:
        drivetrain->drive(speed,0);
        return (sensors->IRFront->objectInRange());
    case 7:
        drivetrain->drive(0,0);
        climbSystem->retractFront();
        return (climbSystem->getFront()==-1);
    case 8:
        return drivetrain->driveDist(60);
    }

}

