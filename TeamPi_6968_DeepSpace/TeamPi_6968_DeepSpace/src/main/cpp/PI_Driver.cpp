#include "PI_Driver.h"


PI_Driver::PI_Driver(uint8_t joystickID)
{

    m_stick = new frc::Joystick(joystickID);
    lvl0Btn = new frc::JoystickButton(m_stick,11);
    lvl1Btn = new frc::JoystickButton(m_stick,9);
    lvl2Btn = new frc::JoystickButton(m_stick,7);

}