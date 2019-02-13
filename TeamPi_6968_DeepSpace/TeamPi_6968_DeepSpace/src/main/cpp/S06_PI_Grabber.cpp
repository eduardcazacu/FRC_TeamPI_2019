#include "S06_PI_Grabber.h"

S06_PI_Grabber::S06_PI_Grabber(/*pneumaticValveCanbusID, Servo*/)
{
    this->Cylinder;
    //this->Servo;
}

//S06_PI_Grabber::S06_PI_Grabber(/*pneumaticValveCanbusID,*/ VictorCanbusID)
/*{
    this->Cylinder;
    this->VictorDC = new C01_PI_Victor(VictorCanbusID);
}
*/
/*
void S06_PI_Grabber::ExtendGripper()
{
    this->Cylinder;
    this->CylinderPosition = 0;
}

void S06_PI_Grabber::RetectGripper()
{
    this->Cylinder;
    this->CylinderPosition = 1;
}

void S06_PI_Grabber::clamping(int _servoPosition)
{
    if (_servoPosition == -1)
    {
        this->servo; // = this->ServoStandardClosed
    }
    else if (_servoPosition == -2)
    {
        this->servo; // = this->ServoStandartOpen;
    }
    else
    {
        this->servo; //_servoPosition
    }
    this->ServoPosition = _servoPosition;
}

void S06_PI_Grabber::toggle()
{
    if (this->ServoPosition == -1)
    {
        this->servo; // this->ServoStandartOpen;
        this->ServoPosition = this->ServoStandartOpen;
    }
    else if (this->ServoPosition == -2)
    {
        this->servo; // this->ServoStandardClosed;
        this->ServoPosition = this->ServoStandartClosed;
    }
    else
    {
        if (this->ServoPosition < this->ServoStandardOpen)
        {
            this->servo; // this->ServoStandardClosed;
            this->ServoPosition = this->ServoStandartClosed;
        }
        else
        {
            this->servo; // this->ServoStandartOpen;
            this->ServoPosition = this->ServoStandartOpen;
        }
    }
}

bool S06_PI_Grabber::getGrippercylender()
{
    return this->CylinderPosition;
}
bool S06_PI_Grabber::getClampPosition()
{
    if (this->motorType = 0)
    {
        return this->ServoPosition();
    }
    else{
        return this->VictorStatus;
    }
}
*/