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
  frc::JoystickButton *aimBtn; //button for aiming
  //lift buttons:
  frc::JoystickButton *lvl0Btn;
  frc::JoystickButton *lvl1Btn;
  frc::JoystickButton *lvl2Btn;

  //manual climb buttons:
  frc::JoystickButton *climbUpBtn;        //extend pistons
  frc::JoystickButton *climbFrontDownBtn; //retract front pistons
  frc::JoystickButton *climbBackDownBtn;  //retract back pistons

  frc::JoystickButton *gripperExtendBtn;
  frc::JoystickButton *gripperRetractBtn;

  //auto:
  frc::JoystickButton *autoPlaceBtn;
  frc::JoystickButton *autoGrabBtn;
  frc::JoystickButton *autoAimBtn;
private:
};