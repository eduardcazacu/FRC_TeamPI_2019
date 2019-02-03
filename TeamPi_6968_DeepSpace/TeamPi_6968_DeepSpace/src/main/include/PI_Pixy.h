
#pragma once

#include <WPILib.h>
#include "PI_Pins.h"
#include <iostream>
#include <SPI.h>


class Pixy {

private:
    bool pixyConnected = false;
    frc::SPI spi;

public:

    Pixy();



};
