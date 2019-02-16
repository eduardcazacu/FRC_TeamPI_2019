/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
//#include <frc/livewindow/LiveWindow.h>

#include <iostream>
#include <frc/WPILib.h>
#include <frc/smartdashboard/SmartDashboard.h>

//frc::I2C *I2CBus;
S01_PI_Sensors *sensors;

int count = 0;

int LiftLevel = 0;

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //drivetrain:
  //initialize drivers:
  talonR = new C00_PI_Talon(1, 76.2, 1);
  victorR1 = new C01_PI_Victor(2);
  victorR2 = new C01_PI_Victor(3);
  talonL = new C00_PI_Talon(4, 76.2, 1);
  victorL1 = new C01_PI_Victor(5);
  victorL2 = new C01_PI_Victor(6);

  //setup the drivetrain:
  drivetrain = new S04_PI_Drivetrain(talonL, victorL1, victorL2, talonR, victorR1, victorR2);

  //sensors:
  sensors = new S01_PI_Sensors(); //check the cpp file for sensor definitions

  //input:
  input = new S02_PI_Input();

  //NetworkTable = new S00_PI_Network();
  lift = new S05_PI_Lift(7); //create a lift using the talon on CAN 7

  //climb system:
  frontL = new PI_Pneumatics(climb_PCMID, climb_piston_FL_channel_fwd, climb_piston_FL_channel_rev, climb_piston_FL_reed_retracted, climb_piston_FL_reed_extended);
  frontR = new PI_Pneumatics(climb_PCMID_2, climb_piston_FR_channel_fwd, climb_piston_FR_channel_rev, climb_piston_FR_reed_retracted, climb_piston_FR_reed_extended);
  backL = new PI_Pneumatics(climb_PCMID, climb_piston_BL_channel_fwd, climb_piston_BL_channel_rev, climb_piston_BL_reed_retracted, climb_piston_BL_reed_extended);
  backR = new PI_Pneumatics(climb_PCMID, climb_piston_BR_channel_fwd, climb_piston_BR_channel_rev, climb_piston_BR_reed_retracted, climb_piston_BR_reed_extended);

  climbMotor = new C01_PI_Victor(climb_victor_CANID);
  climbSystem = new PI_Climb(frontL, frontR, backL, backR, climbMotor);

  //grabbing system:
  grabber = new S06_PI_Grabber(grabber_PCMID, grabber_piston_channel_fwd, grabber_piston_channel_rev, grabber_reed_retracted, grabber_reed_extended, grabber_servo_pin);
  //manual:
  manual = new M00_PI_Manual(drivetrain,input, lift, climbSystem, grabber);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic()
{
  //std::cout << "main function\n";
  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit()
{
}

void Robot::TeleopPeriodic()
{
  sensors->refresh();

  //manual stuff:
  manual->driving();
  manual->functions();

  if (count == 50)
  {
    //execute code in here roughly once a second.

    //test the Ultrasound sensors:
    //std::cout << "Current: " << sensors->USLeft->getCurrent() << '\n';
    //std::cout << "Distance: " << sensors->USLeft->getDist() << '\n';
  }
  count = (count + 1) % 100;
}

void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
