#include "PI_Climb.h"

PI_Climb::PI_Climb(PI_Pneumatics *frontL, PI_Pneumatics *frontR, PI_Pneumatics *backL, PI_Pneumatics *backR, C01_PI_Victor *motorDriver)
{
    _frontL = frontL;
    _frontR = frontR;
    _backL = backL;
    _backR = backR;

    _motorDriver = motorDriver;

    //setup the victor with ramping.
    _motorDriver->GetVictorObject()->ConfigClosedloopRamp(rampTime);
}

void PI_Climb::extendAll()
{
    _frontL->OpenPiston();
    _frontR->OpenPiston();
    _backL->OpenPiston();
    _backR->OpenPiston();
}

void PI_Climb::retractAll()
{
    retractFront();
    retractBack();
}

void PI_Climb::retractFront()
{
    _frontL->ClosePiston();
    _frontR->ClosePiston();
}

void PI_Climb::retractBack()
{
    _backL->ClosePiston();
    _backR->ClosePiston();
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
    if (_backL->PistonStatus() == 1 && _backR->PistonStatus() == 1)
    {
        return 1;
    }
    else if (_backL->PistonStatus() == -1 && _backR->PistonStatus() == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int PI_Climb::getFront()
{
    if (_frontL->PistonStatus() == 1 && _frontR->PistonStatus() == 1)
    {
        return 1;
    }
    else if (
        _frontL->PistonStatus() == -1 && _frontR->PistonStatus() == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}