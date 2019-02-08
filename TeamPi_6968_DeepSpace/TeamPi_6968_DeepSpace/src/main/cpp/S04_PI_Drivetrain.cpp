#include "S04_PI_Drivetrain.h"

S04_PI_Drivetrain::S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2,
                                     C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2)

{
    //assign the drivers:
    this->_talonL = talonL;
    this->_talonR = talonR;
    this->_victorL1 = victorL1;
    this->_victorL2 = victorL2;
    this->_victorR1 = victorR1;
    this->_victorR2 = victorR2;

    //set the defaults:
    //TODO: add in their coresponding constructors
    /*
    this->_talonL->ConfigFactoryDefault();
    this->_talonR->ConfigFactoryDefault();
    this->_victorL1->ConfigFactoryDefault();
    this->_victorL2->ConfigFactoryDefault();
    this->_victorR1->ConfigFactoryDefault();
    this->_victorR2->ConfigFactoryDefault();
    */

    //set the followers:
    this->_victorL1->Follow(_talonL);
    this->_victorL2->Follow(_talonL);
    this->_victorR1->Follow(_talonR);
    this->_victorR2->Follow(_talonT);

    _diffDrive = new DifferentialDrive(_talonL, _talonR);
}

void S04_PI_Drivetrain::drive(double speed, double rotation);