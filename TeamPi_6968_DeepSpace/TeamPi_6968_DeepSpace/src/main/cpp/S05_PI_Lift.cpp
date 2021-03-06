#include "S05_PI_Lift.h"
#include <iostream>
S05_PI_Lift::S05_PI_Lift(uint8_t talonCAN, uint8_t limitSwitchID)
{
    //initialize the driver to work with pid positioning control:
    winch = new C00_PI_Talon(talonCAN, 1, WINCH_RADIUS, kp, ki, kd, kf);

    winch->GetTalonObject()->ConfigClosedloopRamp(RAMP_T);

    limitSwitch = new frc::DigitalInput(limitSwitchID);

    _pos = new double(0);

    winch->GetTalonObject()->SetSelectedSensorPosition(0, 0, 0);
    oldValue = new double();
    *oldValue = limitSwitch->Get();
    liftOff = new bool();
    *liftOff = true;

    //set current limit to prevent burning (again)
    winch->GetTalonObject()->ConfigPeakCurrentLimit(30, 10);       
    winch->GetTalonObject()->ConfigPeakCurrentDuration(1000, 10);   
    winch->GetTalonObject()->ConfigContinuousCurrentLimit(18, 10);
    winch->GetTalonObject()->EnableCurrentLimit(true);            
}

void S05_PI_Lift::goTo(double pos)
{
    /*if(*liftOff){
        std::cout<<"calibrated is false \n";
        this->reset();
        return;
    }*/
    winch->closedLoopControl(pos);
    //save the current position:

    *_pos = pos;

    if (verbose)
    {
        std::cout << "Lift target position: " << pos << "\n";
        std::cout << "current lift encoder position: " << std::dec << winch->GetTalonObject()->GetSelectedSensorPosition() << "\n";
    }
}

void S05_PI_Lift::goToLvl(uint8_t index)
{
    switch (index)
    {
    case 0:
        goTo(LVL0);
        break;
    case 1:
        goTo(LVL1);
        break;
    case 2:
        goTo(LVL2);
    }
}

bool S05_PI_Lift::reset()
{
    double currentValue = limitSwitch->Get();
    std::cout << currentValue << "\n";
    if (*oldValue != currentValue)
    {
        //reached zero point
        winch->GetTalonObject()->SetSelectedSensorPosition(0, 0, 0);
        //stay there:
        *_pos = 0;
        *liftOff = false;
        goTo(0);
        return true;
    }
    else
    {
        if (currentValue)
        {
            goTo(*_pos - resetIncrement);
        }
        else
        {
            goTo(*_pos + resetIncrement);
        }
        return false;
    }

    *oldValue = currentValue;



    /*
    if (!limitSwitch->Get())
    {
        //if limit switch is hit:
        //reset
        //winch->GetTalonObject()->SetSelectedSensorPosition(0, 0, 0);
        //stay there:
        *_pos = 0;
        goTo(0);
        if (verbose)
        {
            std::cout << "lift reset done! \n";
        }
        return true;
    }

    goTo(*_pos - resetIncrement);
    return false;*/
}

void S05_PI_Lift::adjustPos(double value)
{
    if ((*_pos + value >= liftMin) && (*_pos + value) <= liftMax)
        goTo(*_pos + value * 20);
}

C00_PI_Talon *S05_PI_Lift::GetTalonObject()
{
    return winch;
}

bool S05_PI_Lift::TurnOff()
{
    *liftOff = true;
    //disable the PID control and let the lift drop to gravity.
    winch->GetTalonObject()->Set(ControlMode::PercentOutput, 0);

    return false;
}