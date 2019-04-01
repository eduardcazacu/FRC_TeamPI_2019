#include "PI_Climb.h"

PI_Climb::PI_Climb(PI_Pneumatics *Front,  PI_Pneumatics *Back, C01_PI_Victor *motorDriver)
{
    _Front = Front;
    _Back = Back;

    _motorDriver = motorDriver;

    //setup the victor with ramping.
    _motorDriver->GetVictorObject()->ConfigClosedloopRamp(rampTime);
}

void PI_Climb::extendAll()
{
    _Front->OpenPiston();
    _Back->OpenPiston();
}

void PI_Climb::extendFront()
{
    _Front->OpenPiston();
}

void PI_Climb::extendBack()
{
    _Back->OpenPiston();
}

void PI_Climb::retractAll()
{
    retractFront();
    retractBack();
}

void PI_Climb::retractFront()
{
    _Front->ClosePiston();
}

void PI_Climb::retractBack()
{
    _Back->ClosePiston();
}

int PI_Climb::getAll()
{
    if (getFront() == 1 && getBack() == 1)
        return 1;
    else if (getFront() == -1 && getBack() == -1)
        return -1;
    else
        return 0;
}

int PI_Climb::getBack()
{
    return _Back->PistonStatus();
}

int PI_Climb::getFront()
{
    return _Front->PistonStatus();
}

void PI_Climb::drive(double speed)
{
    _motorDriver->GetVictorObject()->Set(speed);
}