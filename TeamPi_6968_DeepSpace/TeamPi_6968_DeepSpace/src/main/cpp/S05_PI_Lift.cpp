#include "S05_PI_Lift.h"
#include <iostream>
S05_PI_Lift::S05_PI_Lift(uint8_t talonCAN)
{
    //initialize the driver to work with pid positioning control:
    winch = new C00_PI_Talon(talonCAN, 1, WINCH_RADIUS, KP, KI, KD, KF);

    winch->GetTalonObject()->ConfigClosedloopRamp(RAMP_T);
}

void S05_PI_Lift::goTo(double pos)
{
    winch->closedLoopControl(pos);
    //std::cout<<"closed loop control called. \n";
    //std::cout<<"target position: "<<pos<<"\n";
    //std::cout<<"current encoder position: "<<std::dec<<winch->GetTalonObject()->GetSelectedSensorPosition()/4096<<"\n";
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