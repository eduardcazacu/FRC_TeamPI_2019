#include "PI_Driver.h"

/* to add to drive train this is the open loop or closed loop command for ramping the talons (smooth acceleration) 
    if using it make sure you only use it for the master and give the followers ther own ramp up and put it in th open or clossed loop of the drive train system 
    TalonR->getTalonObject->configOpenloopRamp([Time to ramp up], [amount of follwors]); // {time to ramp up in seconds, this is the time it takes to go to the set speed in this case 2s } 
                                                                            // [amount of followers is the amount of followers for the tallon(master)]
    TalonL->getTalonObject->configOpenloopRamp([Time to ramp up], [amount of follwors]); 

PI_Driver::PI_Driver(uint8_t joystickID)
{
}