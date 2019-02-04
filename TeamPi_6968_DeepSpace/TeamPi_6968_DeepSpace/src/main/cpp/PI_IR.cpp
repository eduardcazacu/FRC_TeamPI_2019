#include "PI_IR.h"

PI_IR::PI_IR(int pin, int triggerValue)
{
    this->_analogInput = new frc::AnalogInput(pin);
    if (triggerValue)
    {
        if (triggerValue >= 0 && triggerValue <= 1023)
        {
            //make sure it's within the ADC range
            this->_triggerValue = triggerValue;
        }
    }
    else
    {
        triggerValue = 500; //magic numbers yoo-hoo
    }

    //analog setup:
    frc::AnalogInput::SetSampleRate(62500);
}

bool PI_IR::objectInRange(int triggerValue)
{
    return (analogReadIR() > triggerValue);
}

bool PI_IR::objectInRange()
{
    return (analogReadIR() > this->_triggerValue);
}

int PI_IR::analogReadIR(void)
{
    return this->_analogInput->GetValue();
}

void PI_IR::setTRiggerValue(int triggerValue)
{
    if (triggerValue >= 0 && triggerValue <= 1023)
    {
        this->_triggerValue = triggerValue;
    }
}