#include "S04_PI_Drivetrain.h"
#include <iostream>
/* to add to drive train this is the open loop or closed loop command for ramping the talons (smooth acceleration) 
    if using it make sure you only use it for the master and give the followers ther own ramp up and put it in th open or clossed loop of the drive train system 
    TalonR->getTalonObject->configOpenloopRamp([Time to ramp up], [amount of follwors]); // {time to ramp up in seconds, this is the time it takes to go to the set speed in this case 2s } 
                                                                            // [amount of followers is the amount of followers for the tallon(master)]
    TalonL->getTalonObject->configOpenloopRamp([Time to ramp up], [amount of follwors]); 
    */



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

    usingPositioning = false;
}

S04_PI_Drivetrain::S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2, S03_PI_Positioning *robotPos)
{
    S04_PI_Drivetrain(talonL, victorL1, victorL2, talonR, victorR1, victorR2);
    usingPositioning = true;
    this->robotPos = robotPos;

    input= new PI_PIDSource();
    output = new PI_PIDOutput();

    pid = new frc::PIDController(KP_R, KI_R,KD_R,input, output);
}

void S04_PI_Drivetrain::drive(double speed, double rotation)
{
    _diffDrive->ArcadeDrive(speed, rotation);
}

bool S04_PI_Drivetrain::rotateTo(double angle)
{
    if(!usingPositioning){
        std::cout<<"ERROR: Cannot auto rotate. Drive train has not been initialized with a positioning object \n";
        return false;
    }
    //normalize the target to [0,360]
    //angle = (int)(angle + 360) % 360;

    //determine the best direction to rotate in (1 = CW, 0 = CCW):
    /*double diff = (angle - robotPos->Get()->rotation->z);
    bool dir = ((diff > 0 && diff > 180) || (diff < 0 && diff < 180));
    int dirVector = dir ? 1 : -1;
*/



    return false;
}