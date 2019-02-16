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
    if (_input->driver->gripperExtendBtn->Get())
    {
        if (!_input->driver->lastGripperExtendBtn)
        {
            std::cout << "Extend gripper \n";
            _input->driver->lastGripperExtendBtn = 1;
            //extend gripper arm:
            _grabber->extendGripper();
        }
    }
    else
    {
        _input->driver->lastGripperExtendBtn = 0;
    }

    if (_input->driver->gripperRetractBtn->Get())
    {
        if (!_input->driver->lastGripperRetractBtn)
        {
            std::cout << "Retract gripper \n";
            //retract gripper arm:
            _grabber->retractGripper();
            _input->driver->lastGripperRetractBtn = 1;
        }
    }
    else
    {
        _input->driver->lastGripperRetractBtn = 0;
    }

    if (_input->driver->gripBtn->Get())
    {
        if (!_input->driver->lastGripBtn)
        {
            std::cout << "gripper actuated \n";

            if (_grabber->getGripper() == -1)
            {
                //not gripping. grip:
                _grabber->grip();
            }
            else
            {
                _grabber->release();
            }
            _input->driver->lastGripBtn = 1;
        }
    }
    else
    {
        _input->driver->lastGripBtn = 0;
    }
    
    if(_grabber->getArm()==-1){
        std::cout<<"Gripper arm is retracted \n";
    }
    if(_grabber->getArm() ==1){
        std::cout<<"Gripper arm is extended \n";
    }
    
}