#include "M00_PI_Manual.h"
#include <iostream>
M00_PI_Manual::M00_PI_Manual(S04_PI_Drivetrain *drivetrain, S02_PI_Input *input, S05_PI_Lift *lift, PI_Climb *climbSystem, S06_PI_Grabber *grabber, bool verbose)
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
    _drivetrain->drive(-_input->driver->m_stick->GetY(), _input->driver->m_stick->GetZ());
}

void M00_PI_Manual::functions()
{
    //lift:
    //read buttons. set lift target to that:
    if (_input->navigator->lvl0Btn())
    {
        std::cout << "Go to level 0 button pressed \n";
        _lift->goToLvl(0);
    }
    else if (_input->navigator->lvl1Btn())
    {
        std::cout << "Go to level 1 button pressed \n";
        _lift->goToLvl(1);
    }

    else if (_input->navigator->lvl2Btn())
    {
        std::cout << "Go to level 2 button pressed \n";
        _lift->goToLvl(2);
    }

    //climb system:
    //manual climb:
    if (_input->driver->climbUpBtn->Get())
    {
        std::cout << "Extend all climb pistons \n";
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
    if (_input->navigator->extendGrabber())
    {
        std::cout << "Extend gripper btn pressed \n";
        //extend gripper arm:
        _grabber->extendGripper();
    }

    if (_input->navigator->retractGrabber())
    {
        std::cout << "Retract gripper btn pressed\n";
        //retract gripper arm:
        _grabber->retractGripper();
    }

    if (_input->navigator->grip())
    {
        std::cout << "Gripping initiated by navigator\n";
        _grabber->grip();
    }
    if (_input->navigator->release())
    {
        std::cout << "grip released by navigator\n";
        _grabber->release();
    }

    //gradual gripper control:
    if (_input->navigator->manualGrip()>0.01)
    {
        std::cout<<"Grip a ratio of: "<<_input->navigator->manualGrip()<<" \n";
        _grabber->grip(_input->navigator->manualGrip());
    }

    if (_grabber->getArm() == -1)
    {
        std::cout << "Gripper arm is fully retracted \n";
    }
    if (_grabber->getArm() == 1)
    {
        std::cout << "Gripper arm is fully extended \n";
    }

    if((_input->navigator->ManualLift()>0.02)||(_input->navigator->ManualLift()<(-0.02))){
        //when not zero, so moved:
        std::cout<<"Adjusting lift pos by: "<<_input->navigator->ManualLift()<<"\n";
        _lift->adjustPos(_input->navigator->ManualLift());
    }
}