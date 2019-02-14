#include "S05_PI_Lift.h"

S05_PI_Lift::S05_PI_Lift(uint8_t talonCAN)
{
    //initialize the driver to work with pid positioning control:
    winch = new C00_PI_Talon(talonCAN, 1, WINCH_RADIUS, KP, KI, KD, KF);
}

void S05_PI_Lift::goTo(double pos)
{
    winch->closedLoopControl(pos);
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