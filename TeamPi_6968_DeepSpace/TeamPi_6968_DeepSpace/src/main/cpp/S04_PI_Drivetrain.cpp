#include "S04_PI_Drivetrain.h"

S04_PI_Drivetrain::S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2)
{
    //assign the drivers:
    _talonL = talonL;
    _talonR = talonR;
    _victorL1 = victorL1;
    _victorL2 = victorL2;
    _victorR1 = victorR1;
    _victorR2 = victorR2;

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
    this->_victorL1->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorL2->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorR1->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));
    this->_victorR2->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));

    this->_diffDrive = new frc::DifferentialDrive(*(_talonL->GetTalonObject()), *(_talonR->GetTalonObject()));
}

void S04_PI_Drivetrain::drive(double speed, double rotation){
    _diffDrive->ArcadeDrive(speed,rotation);
}