#include "S09_PI_Aim.h"

S09_PI_Aim::S09_PI_Aim(double _maxSpeed, double _kPcorn, double _kIcorn, double _kDcorn, double _kFcorn,double _kPdis, double _kIdis, double _kDdis, double _kFdis)
{
    this->PIDCorner = new PIDBase(_kPcorn,_kIcorn,_kDcorn, this->CornerSource, this->CornerOutput);
    this->PIDDistance = new PIDBase(_kPdis,_kIdis,_kDdis, this->DistanceSource, this->DistanceOutput);
}

bool S09_PI_Aim::Aim(double _Setangle, double _SetDistance, double _setErrorMargenCorner, double _setErrorMargenDistance)
{
    this->PIDCorner->SetSetpoint(_Setangle);
    this->PIDDistance->SetSetpoint(_SetDistance);

    this->PIDCorner->SetPercentTolerance(_setErrorMargenCorner);
    this->PIDDistance->SetPercentTolerance(_setErrorMargenDistance);



    this->PIDCorner->Calculate();
    this->PIDDistance->Calculate();

    this->errorAngle  = this->PIDCorner->get();
    this->errorDistance = this->PIDDistance->get();
}
bool S09_PI_Aim::UpdateAim(){
    // read new values:
    this->CornerSource->set(this->PixyCorner);
    this->DistanceSource->set(this->PixyDistance);

    this->PIDCorner->Calculate();
    this->PIDDistance->Calculate();
}

double S09_PI_Aim::DrivtrainConverter(/*change in angle*/)
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