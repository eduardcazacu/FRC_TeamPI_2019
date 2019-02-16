#include "M00_PI_Manual.h"

M00_PI_Manual::M00_PI_Manual(S04_PI_Drivetrain *drivetrain, S02_PI_Input *input, S05_PI_Lift *lift, PI_Climb *climbSystem,S06_PI_Grabber *grabber, bool verbose)
{

    _drivetrain = drivetrain;
    this->_lift = lift;
    this->_input = input;

    _climbSystem = climbSystem;

    _grabber = grabber;
}

void M00_PI_Manual::driving()
{
    //drive:
    _drivetrain->drive(_input->driver->m_stick->GetY(), _input->driver->m_stick->GetX());
}

void M00_PI_Manual::functions()
{
    //lift:
    //read buttons. set lift target to that:
    if (_input->driver->lvl0Btn->Get())
        _lift->goToLvl(0);
    else if (_input->driver->lvl1Btn->Get())
        _lift->goToLvl(1);
    else if (_input->driver->lvl2Btn->Get())
        _lift->goToLvl(2);

    //climb system:
    //manual climb:
    if (_input->driver->climbUpBtn->Get())
    {
        _climbSystem->extendAll();
    }
    else if (_input->driver->climbFrontDownBtn->Get())
    {
        _climbSystem->retractFront();
    }
    else if (_input->driver->climbBackDownBtn->Get())
    {
        _climbSystem->retractBack();
    }

    //grabber:
    if (_input->driver->gripperExtendBtn->Get())
    {
        //extend gripper arm:
        _grabber->extendGripper();
    }
    else if (_input->driver->gripperRetractBtn->Get())
    {
        //extend gripper arm:
        _grabber->retractGripper();
    }
}