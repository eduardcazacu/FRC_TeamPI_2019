/*
Input that concerns the movement of the drivetrain

created by Eduard Cazacu on 08 February 2019
*/


#pragma once

#include <frc/Joystick.h>
#include <frc/buttons/Button.h>
#include <frc/buttons/JoystickButton.h>

#define DEFAULT_JOYSTICK_ID 0

class PI_Driver
{
  public:
    PI_Driver(uint8_t joystickID=DEFAULT_JOYSTICK_ID);
    
    frc::Joystick *m_stick;         //main joystick for driving;
    frc::JoystickButton *aimBtn;    //button for aiming
  private:
};