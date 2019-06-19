#ifndef SRC_PIAIM_H_
#define SRC_PIAIM_H_

#include "PiMovement.h"
#include "C04_PI_Pixy.h"

class PiAim{
    private:

        PiMovement * driveStation;
        C04_PI_Pixy * pixy;

        double errorSum = 0;

    public:

    PiAim(PiMovement *driveStation, C04_PI_Pixy *pixy);
    bool EasyAim();
    bool CalculateMovement(uint8_t *info);
};



#endif