#include "PI_Driver.h"

PI_Driver::PI_Driver(uint8_t joystickID)
{

    m_stick = new frc::Joystick(joystickID);

    climbUpBtn = new frc::JoystickButton(m_stick, 8);
    climbFrontDownBtn = new frc::JoystickButton(m_stick, 10);
    climbBackDownBtn = new frc::JoystickButton(m_stick, 12);


}