/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

//our libraries:
#include "S01_PI_Sensors.h"
#include "Adafruit_INA219.h"
#include "ArduinoI2C.h"
#include "S02_PI_Input.h"
#include "C01_PI_Victor.h"
#include "C00_PI_Talon.h"
#include "S04_PI_Drivetrain.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;


  //frc::I2C *I2CBus;
  S01_PI_Sensors *sensors;
  
  //motors:
  C00_PI_Talon* talonL;
  C00_PI_Talon* talonR;
  C01_PI_Victor* victorL1;
  C01_PI_Victor* victorL2;
  C01_PI_Victor* victorR1;
  C01_PI_Victor* victorR2;

  //drivetrain:
  S04_PI_Drivetrain *drivetrain;

  //input:
  S02_PI_Input *input;

  

};
