#include "S09_PI_Aim.h"

S09_PI_Aim::S09_PI_Aim(double _maxSpeed, double _kPcorn, double _kIcorn, double _kDcorn, double _kFcorn, double _kPdis, double _kIdis, double _kDdis, double _kFdis)
{
    this->PIDCorner = new PIDBase(_kPcorn, _kIcorn, _kDcorn, this->CornerSource, this->CornerOutput);
    this->PIDDistance = new PIDBase(_kPdis, _kIdis, _kDdis, this->DistanceSource, this->DistanceOutput);
}

bool S09_PI_Aim::Aim(double _Setangle, double _SetDistance, double _setErrorMargenCorner, double _setErrorMargenDistance)
{
    this->PIDCorner->SetSetpoint(_Setangle);
    this->PIDDistance->SetSetpoint(_SetDistance);

    this->PIDCorner->SetPercentTolerance(_setErrorMargenCorner);
    this->PIDDistance->SetPercentTolerance(_setErrorMargenDistance);

     return UpdateAim();
}
bool S09_PI_Aim::UpdateAim()
{
    // TODO make aiming part 
    // read new values:
    // error angle = 90 -pixy angle 
    this->PixyCorner = 90-(S01_PI_Sensors->PixyDown->BestVector ()->Angle());
    this->PixyDistance = 208 - (S01_PI_Sensors->PixyDown->LatestVector()->y0);

    //setting source values
    this->CornerSource->Set(this->PixyCorner);
    this->DistanceSource->Set(this->PixyDistance);

    //caluclating pid Values
    this->PIDCorner->Calculate();
    this->PIDDistance->Calculate();

    this->Angle = this->CornerOutput->Get(); 
    this->speed = map(this->DistanceOutput->Get(), 0,200, 0,MaxSpeed);
    return PIDCorner->OnTarget();
}


    


double S09_PI_Aim::map(double x, double xMin, double xMax, double yMin, double yMax)
{
    return (yMin + (x - xMin) * (yMax - yMin) / (xMax - xMin));
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