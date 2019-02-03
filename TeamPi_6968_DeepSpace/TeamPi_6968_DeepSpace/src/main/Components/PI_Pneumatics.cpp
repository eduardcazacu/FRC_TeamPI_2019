#include "PI_Pneumatics.h"
#include <DigitalInput.h>

PI_Pneumatics::PI_Pneumatics(int Pneu_pin)
{
    OpenPin = Pneu_pin;
     
}

void PI_Pneumatics::OpeningValve()
{

    DigitalWrite(OpenPin, true);
}