#include "M00_PI_Manual.h"

M00_PI_Manual::M00_PI_Manual(S02_PI_Input *input, S05_PI_Lift *lift, bool verbose)
{
    //initialize drivers:
    talonR = new C00_PI_Talon(1, 76.2, 1);
    victorR1 = new C01_PI_Victor(2);
    victorR2 = new C01_PI_Victor(3);
    talonL = new C00_PI_Talon(4, 76.2, 1);
    victorL1 = new C01_PI_Victor(5);
    victorL2 = new C01_PI_Victor(6);

    //setup the drivetrain:
    drivetrain = new S04_PI_Drivetrain(talonL, victorL1, victorL2, talonR, victorR1, victorR2);

    this->_lift = lift;
    this->_input = input;
}

void M00_PI_Manual::driving()
{
    //drive:
    drivetrain->drive(_input->driver->m_stick->GetY(), _input->driver->m_stick->GetX());
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
}