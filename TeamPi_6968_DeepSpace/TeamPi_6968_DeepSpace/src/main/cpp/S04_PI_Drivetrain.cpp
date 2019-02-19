#include "S04_PI_Drivetrain.h"
#include <iostream>
#include "cmath"

/*  TODO    
    to add to drive train this is the open loop or closed loop command for ramping the talons (smooth acceleration) 
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

    //set the followers:
    this->_victorL1->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorL2->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorR1->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));
    this->_victorR2->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));

    //set open loop ramp rates
    this->TalonL->getTalonObject->configOpenloopRamp(rampTimeOpenLoop, timeOutMS );
    this->VictorL1->GetVictorObject->ConfigOpenloopRamp(rampTimeOpenLoop, timeOutMS);
    this->VictorL2->GetVictorObject->ConfigOpenloopRamp(rampTimeOpenLoop, timeOutMS);

    this->TalonR->getTalonObject->configOpenloopRamp(rampTimeOpenLoop, timeOutMS);
    this->VictorR1->GetVictorObject->ConfigOpenloopRamp(rampTimeOpenLoop, timeOutMS);
    this->VictorR2->GetVictorObject->ConfigOpenloopRamp(rampTimeOpenLoop, timeOutMS);

    this->_diffDrive = new frc::DifferentialDrive(*(_talonL->GetTalonObject()), *(_talonR->GetTalonObject()));

    usingPositioning = false;
}

S04_PI_Drivetrain::S04_PI_Drivetrain(C00_PI_Talon *talonL, C01_PI_Victor *victorL1, C01_PI_Victor *victorL2, C00_PI_Talon *talonR, C01_PI_Victor *victorR1, C01_PI_Victor *victorR2, S03_PI_Positioning *robotPos)
{

    //assign the drivers:
    _talonL = talonL;
    _talonR = talonR;
    _victorL1 = victorL1;
    _victorL2 = victorL2;
    _victorR1 = victorR1;
    _victorR2 = victorR2;

    //set the followers:
    this->_victorL1->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorL2->GetVictorObject()->Follow(*(_talonL->GetTalonObject()));
    this->_victorR1->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));
    this->_victorR2->GetVictorObject()->Follow(*(_talonR->GetTalonObject()));

    this->_diffDrive = new frc::DifferentialDrive(*(_talonL->GetTalonObject()), *(_talonR->GetTalonObject()));

    usingPositioning = true;
    _robotPos = robotPos;

    input = new PI_PIDSource();
    output = new PI_PIDOutput();

    pidRotation = new frc::PIDController(KP_R, KI_R, KD_R, input, output);
    pidRotation->SetOutputRange(-0.5, 0.5);
    pidRotation->Disable(); //don;t run it until needed.
}

void S04_PI_Drivetrain::drive(double speed, double rotation)
{
    _diffDrive->ArcadeDrive(speed, rotation);
}

bool S04_PI_Drivetrain::Rotate(double angle)
{
    if (!usingPositioning)
    {
        std::cout << "ERROR: Cannot auto rotate. Drive train has not been initialized with a positioning object \n";
        return false;
    }
    if (angle < -360 || angle > 360)
    {
        std::cout << "ERROR: Angle out of bounds. range is (-360,360) \n";
        return false;
    }
    //if first call:
    if (!pidRotationStarted)
    {
        pidRotationStarted = true;
        targetAngle = _robotPos->Get()->rotation->z + angle;
        //normalize the target to [0,360]
        targetAngle = normalizeAngle(targetAngle);

        //determine which way should the robot turn to get there the quickest:
        if (sqrt(pow((targetAngle - _robotPos->Get()->rotation->z),2)) < 180)
        {
            //turn counter clockwise
            turnDirection = -1;
        }
        else
        {
            //turn clockwise;
            turnDirection = 1;
        }

        //start the pid loop:
        input->Set(_robotPos->Get()->rotation->z);
        pidRotation->SetSetpoint(targetAngle);
        pidRotation->Enable();

        std::cout << "PID rotaion initiated. current angle is: " << _robotPos->Get()->rotation->z << '\n';
        std::cout << "target angle is: " << targetAngle << "\n";
        std::cout << "To get there the robot should turn ";
        if (turnDirection == -1)
            std::cout << "left \n";
        else if (turnDirection == 1)
        {
            std::cout << "right \n";
        }
    }
    std::cout<<"Current robot rotation: "<<_robotPos->Get()->rotation->z<<"\n";

    //calculate the angle error:
    input->Set(_robotPos->Get()->rotation->z);
    
    //write the output of the pid loop to the drivetrain:
    drive(0, sqrt(pow(pidRotation->Get(),2)) * turnDirection);

    //check if it got there
    if (pidRotation->OnTarget())
    {
        //disable the loop and let the caller know that we got there
        pidRotation->Reset();
        pidRotationStarted = false;
        return true;
    }

    //determine the best direction to rotate in (1 = CW, 0 = CCW):
    /*double diff = (angle - robotPos->Get()->rotation->z);
    bool dir = ((diff > 0 && diff > 180) || (diff < 0 && diff < 180));
    int dirVector = dir ? 1 : -1;
*/

    return false;
}

//normalizes the angle to (0,359);
double S04_PI_Drivetrain::normalizeAngle(double angle)
{
    while(angle<0){
        angle+=360;
    }
    while(angle>360){
        angle-=360;
    }
    return angle;
}

bool S04_PI_Drivetrain::driveDist(double distance)
{
    if (!autoDriveStarted)
    {
        autoDriveStarted = true;
        targetDistance = _robotPos->getDistance() + distance;
    }

    double diff = targetDistance - _robotPos->getDistance();
    int dist = diff / (abs(diff));

    drive(dist * autoDriveSpeed, 0);

    if (abs(targetDistance - _robotPos->getDistance()) < 1)
    {
        autoDriveStarted = false;
        return true;
    }
    return false;
}

//_talon.openloopRamp = 1.023000;
//_talon.closedloopRamp = 1.705000;
// //set open loop ramp rates
/*
    this->TalonL->getTalonObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS );
    this->VictorL1->GetVictorObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS);
    this->VictorL2->GetVictorObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS);

    this->TalonR->getTalonObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS);
    this->VictorR1->GetVictorObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS);
    this->VictorR2->GetVictorObject->configClosedloopRamp(rampTimeClosedloop, timeOutMS);
    */