#include "S06_PI_Grabber.h"

S06_PI_Grabber::S06_PI_Grabber(int moduleID, int fwdID, int revID, int retractedReedPin, int extendedReedPin, int servoPin)
{
    _piston = new frc::DoubleSolenoid(moduleID, fwdID, revID);
    _servo = new frc::Servo(servoPin);
    _retractedReed = new frc::DigitalInput(retractedReedPin);
    _extendedReed = new frc::DigitalInput(extendedReedPin);

    motorType = 0;
}

S06_PI_Grabber::S06_PI_Grabber(int moduleID, int fwdID, int revID, int retractedReedPin, int extendedReedPin, int servoPin, int forceSensorPin)
{
    S06_PI_Grabber(moduleID, fwdID, revID, retractedReedPin, extendedReedPin, servoPin);
    _pressureSensor = new frc::AnalogInput(forceSensorPin);
    usePressureSensor = 1;

    motorType = 0;
}

S06_PI_Grabber::S06_PI_Grabber(int moduleID, int fwdID, int revID, int retractedReedPin, int extendedReedPin, C01_PI_Victor *victor)
{
    _piston = new frc::DoubleSolenoid(moduleID, fwdID, revID);
    this->_victor = victor;
    _retractedReed = new frc::DigitalInput(retractedReedPin);
    _extendedReed = new frc::DigitalInput(extendedReedPin);

    motorType = 1;
}
S06_PI_Grabber::S06_PI_Grabber(int moduleID, int fwdID, int revID, int retractedReedPin, int extendedReedPin, C01_PI_Victor *victor, int forceSensorPin)
{
    S06_PI_Grabber(moduleID, fwdID, revID, retractedReedPin, extendedReedPin, victor);

    _pressureSensor = new frc::AnalogInput(forceSensorPin);
    usePressureSensor = 1;

    motorType = 1;
}

void S06_PI_Grabber::extendGripper()
{
    _piston->Set(frc::DoubleSolenoid::Value::kForward);

    pistonPos = 1;
}

void S06_PI_Grabber::retractGripper()
{
    _piston->Set(frc::DoubleSolenoid::Value::kReverse);

    pistonPos = 0;
}
void S06_PI_Grabber::toggleArm()
{
    if (pistonPos)
    {
        //retract:
        retractGripper();
    }
    else
    {
        extendGripper();
    }
}

int S06_PI_Grabber::getArm()
{
    if (!_retractedReed->Get())
    {
        return -1;
    }
    else if (!_extendedReed->Get())
        return 1;

    return 0;
}

void S06_PI_Grabber::grip(double ratio)
{
    if (!motorType)
    {
        //in case of servo:
        _servo->Set(ratio);

        if (ratio > 0)
        {
            gripState = 1;
        }
        else
        {
            gripState = 0;
        }
    }
    else
    {
        //for dc motor:
    }
}
void S06_PI_Grabber::grip()
{
    if (!motorType)
    {
        //in case of servo:
        _servo->Set(SERVO_FULL_GRIP);
        gripState = 1;
    }
    else
    {
        //for dc motor:
    }
}

void S06_PI_Grabber::release()
{
    if (!motorType)
    {
        //in case of servo:
        _servo->Set(SERVO_FULL_RELEASE);
        gripState = 0;
    }
    else
    {
        //for dc motor:
    }
}

int S06_PI_Grabber::getGripper()
{
    if (gripState)
    {
        //grabbing
        if (_servo->Get() < 1)
            return _servo->Get();
        else
            return -2;
    }
    else
    {
        //not grabbing
        return -1;
    }
}

bool S06_PI_Grabber::hatchSecured()
{
    //if no sensor pray to the gods that all is good
    if (!usePressureSensor)
        return false;

    return _pressureSensor->GetValue() < GRAB_SENSOR_THRESHOLD;
}
