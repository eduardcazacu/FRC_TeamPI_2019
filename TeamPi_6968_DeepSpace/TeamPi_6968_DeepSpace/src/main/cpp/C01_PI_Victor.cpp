#include "C01_PI_Victor.h"

C01_PI_Victor::C01_PI_Victor(int CanBusDeviceID)
{
    this->PiVictor = new WPI_VictorSPX(CanBusDeviceID);
    PiVictor->ConfigFactoryDefault();
}

WPI_VictorSPX *C01_PI_Victor::GetVictorObject()
{
    return this->PiVictor;
}