#include "S09_PI_Aim.h"

S09_PI_Aim::S09_PI_Aim(double _maxSpeedPercentage, S04_PI_Drivetrain *drivetrain)
{

    this->drivetrain = drivetrain;
    this->PIDAngle = new frc::PIDController(kPAngle, kIAngle, KDAngle, *AngleSource, *AngleOutput);
    this->PIDDistance = new frc::PIDController(kPDist, kIDist, kDDist, *DistanceSource, *DistanceOutput);
    this->PIDDistanceAngle = new frc::PIDController(kPDriveAngle, kIDriveAngle, KDDriveAngle, *DistanceAngleSource, *DistanceAngleOutput);
    PIDStarted = false;

    PIDAngle->SetOutputRange(angleMin, angleMax);
    PIDDistance->SetOutputRange(distMin, distMax);
    PIDDistanceAngle->SetOutputRange(driveAngleMin, driveAngleMax);

    //disable until needed
    PIDAngle->Disable();
    PIDDistance->Disable();
    PIDDistanceAngle->Disable();
}

bool S09_PI_AIM::SimpleAim(double error, double turnRate, double currentDistance, double maxDistance, double speed){

    double distance = maxDistance-currentDistance;
    double driveSpeed = distance * speed;

    if (distance < 1){
        return true;
    }

    double driveAngle = error*turnRate;

    drivetrain->drive(driveSpeed, driveAngle);

    return false;
}

bool S09_PI_Aim::Aim(double _angle, double targetX, double targetY)
{
    // _angle = angle-90; // convert the  the pixy angle in the angle usefull for the aiming class
    /*
    The angle PID will fight to get the angle parallel and the distance PID will fight to get the angle and speed so that
    it can get on top of the target point.


    This is done by calculating the distance between the target point and the intersection point of the robot vector and
    the line vector.

    */

    //check if this is the first time it is called and setup the pid loop:
    if (!PIDStarted)
    {
        //we want to be parallel and exactly on the line:
        this->PIDAngle->SetSetpoint(0);
        this->PIDDistance->SetSetpoint(0);
        //the target error between the intersection point and the target point
        this->PIDDistanceAngle->SetSetpoint(0);

        std::cout << "SetPoint checks: PIDAngle" << '\n';

        this->PIDAngle->SetPercentTolerance(tolerance);
        this->PIDDistance->SetPercentTolerance(tolerance);
        this->PIDDistanceAngle->SetPercentTolerance(tolerance);

        PIDAngle->Enable();
        PIDDistance->Enable();
        PIDDistanceAngle->Enable();

        PIDStarted = true;
        if (verbose)
            std::cout << "Aiming PID started \n";
    }

    //update the errors:
    AngleSource->Set(_angle);

    //calculate the intersection point error relative to the target point;
    intersectionError = (targetX - PIXY_WIDTH) / sin(_angle);
    DistanceAngleSource->Set(intersectionError); //don't forget to multiply the output with -1 for correct turn direction
    std::cout<<"\ntargetX: "<<targetX<<" targetY:"<<targetY<<"\n \n";
    //calculate the distance error:
    distanceError = -sqrt(pow(targetX - PIXY_WIDTH / 2, 2) + pow(PIXY_HEIGHT - targetY, 2));
    DistanceSource->Set(distanceError);

    //set the current inputs:
    driveSpeed = PIDDistance->Get();
    driveAngle = -(PIDAngle->Get() - PIDDistanceAngle->Get());
    drivetrain->drive(driveSpeed, driveAngle);
    //value voor PID check make sure that the drive class gets censable values

    if (verbose)
    {
        std::cout << "writing to drive: Y=" << driveSpeed << "   |   X" << driveAngle << "\n";
        std::cout << "line angle " << _angle << " ,distance error: " << distanceError << " ,intersection error: " << intersectionError << "\n";
        std::cout << "Aiming drive values: speed = " << driveSpeed << " ,angle = " << driveAngle << '\n';
    }

    //check if made it:
    if (/*PIDAngle->OnTarget() &&*/ PIDDistance->OnTarget() /*&& PIDDistanceAngle->OnTarget()*/)
    {
        if (verbose)
        {
            std::cout << "Aiming PID done \n";
        }

        //reset the pid for next use:
        PIDAngle->Reset();
        PIDDistance->Reset();
        PIDDistanceAngle->Reset();
        PIDStarted = false;

        return true;
    }

    return false;
}

void S09_PI_Aim::changePID()
{
}
/*
old functions Jorn want sto keep for a bit dont look if you are not interessed

double teta;
    if (teta < 90)
    {
        this->currentAngle = 90 - teta;
        this->quadrent = 2;
    }
    else if (teta > 90)
    {
        this->currentAngle = 90 - teta;
         this->quadrent = 1;
    }
    else if (teta = -1)
    {
        this->currentAngle = 20;
         this->quadrent = 5;
    }
    this->Error = currentAngle;

    PidValues 
    double Prop = this->kP * this->Error;
    double Intr = this->kI * (this->OldError + this->Error);
    double Def = this->kD * (this->OldError - this->Error);

    final motor value
    AngleChange = Prop + Intr + Def;

    this->OldError = this->Error;
    this->errorInter += this->Error;
    if(quadrent == 1){
*/