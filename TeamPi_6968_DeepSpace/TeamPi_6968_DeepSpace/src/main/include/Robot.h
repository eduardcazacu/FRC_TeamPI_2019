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
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

//our libraries:
#include "PI_Pins.h"
#include "ArduinoI2C.h"
#include "S02_PI_Input.h"
#include "C03_PI_Camera.h"
#include "S00_PI_Network.h"
#include "S05_PI_Lift.h"
#include "M00_PI_Manual.h"
#include "S01_PI_Sensors.h"
#include "S02_PI_Input.h"
#include "M01_PI_Auto.h"

class Robot : public frc::TimedRobot
{
 public:
   void RobotInit() override;
   void RobotPeriodic() override;
   //void AutonomousInit() override;
   //void AutonomousPeriodic() override;
   void TeleopInit() override;
   void TeleopPeriodic() override;
   //void TestPeriodic() override;

 private:
   frc::SendableChooser<std::string> m_chooser;
   const std::string kAutoNameDefault = "Default";
   const std::string kAutoNameCustom = "My Auto";
   std::string m_autoSelected;


   //drivetrain:
   //motors:
   C00_PI_Talon *talonL;
   C00_PI_Talon *talonR;
   C01_PI_Victor *victorL1;
   C01_PI_Victor *victorL2;
   C01_PI_Victor *victorR1;
   C01_PI_Victor *victorR2;

   S04_PI_Drivetrain *drivetrain;

   //frc::I2C *I2CBus;
   S01_PI_Sensors *sensors;

   //manual:
   M00_PI_Manual *manual;

   //camera
   C03_PI_Camera *camera;

   S00_PI_Network *NetworkTable;

   //input:
   S02_PI_Input *input;

   //lift:
   S05_PI_Lift *lift;

   //climb system
   PI_Pneumatics *frontL;
   PI_Pneumatics *frontR;
   PI_Pneumatics *backL;
   PI_Pneumatics *backR;

   PI_Climb *climbSystem;
   C01_PI_Victor *climbMotor;

   //grabber:
   S06_PI_Grabber *grabber;

   //positioning:
   S03_PI_Positioning *positioning;

   //auto functions:
  M01_PI_Auto *autoFunctions;


  void readUserInput();

};
