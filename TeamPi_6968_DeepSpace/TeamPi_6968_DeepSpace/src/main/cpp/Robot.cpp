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
#include "frc/DigitalInput.h"

//frc::I2C *I2CBus;
S01_PI_Sensors *sensors;

int count = 0;

int LiftLevel = 0;

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  network =  new S00_PI_Network();

  //input:
  input = new S02_PI_Input();

  //drivetrain:
  //initialize drivers:
  talonR = new C00_PI_Talon(1, 76.2, 1);
  victorR1 = new C01_PI_Victor(2);
  victorR2 = new C01_PI_Victor(3);
  talonL = new C00_PI_Talon(4, 76.2, 1);
  victorL1 = new C01_PI_Victor(5);
  victorL2 = new C01_PI_Victor(6);

  //positioning:
  positioning = new S03_PI_Positioning(network,talonL, talonR);

  //setup the drivetrain:
  drivetrain = new S04_PI_Drivetrain(talonL, victorL1, victorL2, talonR, victorR1, victorR2, positioning);

  //sensors:
  sensors = new S01_PI_Sensors(); //check the cpp file for sensor definitions

  //NetworkTable = new S00_PI_Network();
  lift = new S05_PI_Lift(7); //create a lift using the talon on CAN 7

  //climb system:
  frontPneu = new PI_Pneumatics(PCMID, climb_piston_F_channel_fwd, climb_piston_F_channel_rev, climb_piston_F_reed_retracted, climb_piston_F_reed_extended);
  backPneu = new PI_Pneumatics(PCMID, climb_piston_B_channel_fwd, climb_piston_B_channel_rev, climb_piston_B_reed_retracted, climb_piston_B_reed_extended);
  
  climbMotor = new C01_PI_Victor(climb_victor_CANID);
  climbSystem = new PI_Climb(frontPneu, backPneu, climbMotor);

  //grabbing system:
  grabber = new S06_PI_Grabber(PCMID, grabber_piston_channel_fwd, grabber_piston_channel_rev, grabber_reed_retracted, grabber_reed_extended, grabber_servo_pin);
  //manual:
  manual = new M00_PI_Manual(drivetrain, input, lift, climbSystem, grabber);

  autoFunctions = new M01_PI_Auto(grabber);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
}
void Robot::AutonomousInit()
{
}
void Robot::AutonomousPeriodic()
{
}
void Robot::TeleopInit()
{
}

void Robot::TeleopPeriodic()
{
  //handle user input here:
  //go to the function bellow for more info.
  readUserInput();

  sensors->refresh();

  //manual stuff:
  if (!autoFunctions->on || manual->manualOverride)
  {
    //if no auto operations happening or override is on
    manual->driving();
    manual->functions();
  }

  if (!manual->manualOverride)
  {
    //take care of auto function here if needed:
    //the auto functions here will be activated only by calling their corresponding enable/disable commands
    autoFunctions->functions();
  }
  else
  {
    //reset auto functions here:
    autoFunctions->reset();
  }

  //positioning update:
  positioning->refresh();

  //for testing:
  if (count == 50)
  {

    if(autoFunctions->on){
      std::cout<<"Auto action happening now \n";
    }
    //execute code in here roughly once a second.

    //test the Ultrasound sensors:
    //std::cout << "Distance L: " << sensors->USLeft->getDist() << '\n';
    //std::cout << "Distance R: " << sensors->USRight->getDist() << '\n';

    std::cout<<"current coordinates: x:"<<positioning->Get()->position->x<<" y:"<<positioning->Get()->position->y<<'\n';
    std::cout<<"current orientation: "<<positioning->Get()->rotation->z<<'\n';

  }
  count = (count + 1) % 100;
}

void Robot::readUserInput()
{
  
  //handle all the button presses and function calls here:
 
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
