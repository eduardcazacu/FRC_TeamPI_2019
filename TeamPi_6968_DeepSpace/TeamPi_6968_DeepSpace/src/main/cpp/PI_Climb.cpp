#include "PI_Climb.h"

PI_Climb::PI_Climb(PI_Pneumatics *LFront, PI_Pneumatics *RFront, PI_Pneumatics *LBack, PI_Pneumatics *RBack, C01_PI_Victor *motorDriver)
{
    _LFront = LFront;
    _RFront = RFront;
    _LBack = LBack;
    _RBack = RBack;

    _motorDriver = motorDriver;

    //setup the victor with ramping.
    _motorDriver->GetVictorObject()->ConfigClosedloopRamp(rampTime);
}

void PI_Climb::extendAll()
{
    _LFront->OpenPiston();
    _RFront->OpenPiston();
    _LBack->OpenPiston();
    _RBack->OpenPiston();
}

void PI_Climb::extendFront()
{
    _LFront->OpenPiston();
    _RFront->OpenPiston();
}

void PI_Climb::extendBack()
{
    _LBack->OpenPiston();
    _RBack->OpenPiston();
}

void PI_Climb::retractAll()
{
    retractFront();
    retractBack();
}

void PI_Climb::retractFront()
{
    _LFront->ClosePiston();
    _RFront->ClosePiston();
}

void PI_Climb::retractBack()
{
    _LBack->ClosePiston();
    _RBack->ClosePiston();
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
    return _LBack->PistonStatus();
}

int PI_Climb::getFront()
{
    return _LFront->PistonStatus();
}

void PI_Climb::drive(double speed)
{
    _motorDriver->GetVictorObject()->Set(speed);
}