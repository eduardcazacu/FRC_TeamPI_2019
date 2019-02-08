/*
    this is the Pi Victor class in this class will inhered all the functions
    of the CTRE victor class but will be have extra functions specific to team pi
    the folwing mehtots can be found in this class 
    -*constructor
    -*GetVictorObject()
*/
#pragma one
#include "ctre/Phoenix.h"


class C01_PI_Victor : public WPI_VictorSPX
{
private:
    WPI_VictorSPX *PiVictor;
public:
    C01_PI_Victor(int CanBusDeviceID));
    void GetVictorObject()
};

