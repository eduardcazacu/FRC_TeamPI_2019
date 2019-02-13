#include "S09_PI_Aim.h"

S09_PI_Aim::S09_PI_Aim(double _kP, double _kI, double _kD, double _kF)
{
}

bool S09_PI_Aim::Aim(double Setangle)
{
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

    /*PidValues */
    double Prop = this->kP * this->Error;
    double Intr = this->kI * (this->OldError + this->Error);
    double Def = this->kD * (this->OldError - this->Error);

    /*final motor value*/
    AngleChange = Prop + Intr + Def;

    this->OldError = this->Error;
    this->errorInter += this->Error;
    if(quadrent == 1){
        
    }
}

double S09_PI_Aim::DrivtrainConverter(/*change in angle*/)
{
}