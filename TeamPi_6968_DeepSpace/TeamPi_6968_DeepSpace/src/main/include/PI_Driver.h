/*
Input that concerns the movement of the drivetrain

NOT TO BE CONFUSED WITH PI_DRIVETRAIN

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
  PI_Driver(uint8_t joystickID = DEFAULT_JOYSTICK_ID);

  frc::Joystick *m_stick;      //main joystick for driving;

  //manual climb buttons:
  frc::JoystickButton *climbUpBtn;        //extend pistons
  frc::JoystickButton *climbFrontDownBtn; //retract front pistons
  frc::JoystickButton *climbBackDownBtn;  //retract back pistons
  frc::JoystickButton *rocketDistance;
  frc::JoystickButton *cargoDistance;

private:
};