#include "M00_PI_Manual.h"
#include <iostream>

float speedLimit = 0.75;

M00_PI_Manual::M00_PI_Manual(S04_PI_Drivetrain *drivetrain, S02_PI_Input *input, S05_PI_Lift *lift, /*PI_Climb *climbSystem,*/ S06_PI_Grabber *grabber, bool verbose)
{

    _drivetrain = drivetrain;
    this->_lift = lift;
    this->_input = input;

    //_climbSystem = climbSystem;

    _grabber = grabber;
    calibrated = new bool();
    *calibrated = false;
}

void M00_PI_Manual::init(){
    *calibrated = false;
}

void M00_PI_Manual::driving()
{
    //drive:
    _drivetrain->drive(-_input->driver->m_stick->GetY(), _input->driver->m_stick->GetZ()*turnSpeedMultiplier);
    double throttle = _input->driver->m_stick->GetThrottle();
    throttle = map(throttle,1,-1,minimumAcceleration,maxAcceleration);
    
    _drivetrain->rampTimeOpenLoop = throttle;
    _drivetrain->rampTimeClosedloop =throttle;
    //std::cout<<"throttle "<<throttle<<"\n";
}

void M00_PI_Manual::functions()
{
    
    /*if(!*calibrated){
        std::cout<<"calibrated is false \n";
        *calibrated = _lift->reset();
        return;
    }*/

    //lift:
    //read buttons. set lift target to that:
    // /if(_input->navigator->)
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

    if(_input->navigator->liftOff()){
        //turn off the lift motor:
        _lift->TurnOff();
    }


    //climb system:
    //manual climb:
    /*
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

    if(_input->navigator->manualClimbDrive()){
        _climbSystem->drive(_input->navigator->manualClimbDrive());
    }
*/
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

double M00_PI_Manual::map(double x, double xMin, double xMax, double yMin, double yMax){
    return (yMin + (x - xMin) * (yMax - yMin) / (xMax - xMin));
}