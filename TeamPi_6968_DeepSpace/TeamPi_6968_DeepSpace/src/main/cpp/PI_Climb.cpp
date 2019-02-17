#include "PI_Climb.h"

PI_Climb::PI_Climb(PI_Pneumatics *front, PI_Pneumatics *back, C01_PI_Victor *motorDriver)
{
    _front = front;
    _back = back;

    _motorDriver = motorDriver;

    //setup the victor with ramping.
    _motorDriver->GetVictorObject()->ConfigClosedloopRamp(rampTime);
}

void PI_Climb::extendAll()
{
    _front->OpenPiston();
    _back->OpenPiston();
}

void PI_Climb::extendFront()
{
    _front->OpenPiston();
}

void PI_Climb::extendBack()
{
    _back->OpenPiston();
}

void PI_Climb::retractAll()
{
    retractFront();
    retractBack();
}

void PI_Climb::retractFront()
{
    _front->ClosePiston();
}

void PI_Climb::retractBack()
{
    _back->ClosePiston();
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
    return _back->PistonStatus();
}

int PI_Climb::getFront()
{
    return _front->PistonStatus();
}

void PI_Climb::drive(double speed){
    _motorDriver->GetVictorObject()->Set(speed);
}