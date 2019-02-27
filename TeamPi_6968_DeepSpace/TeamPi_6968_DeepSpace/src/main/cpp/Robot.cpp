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

<<<<<<< HEAD
//our libraries:
#include "S01_PI_Sensors.h"
#include "Adafruit_INA219.h"
#include "ArduinoI2C.h"
#include "S02_PI_Input.h"
#include "PI_Servo.h"
=======
//frc::I2C *I2CBus
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7

int networkTest = 0;
int networkTestID;

int count = 0;

void Robot::RobotInit()
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  network = new S00_PI_Network();

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
  positioning = new S03_PI_Positioning(network, talonL, talonR);

  
<<<<<<< HEAD
  camera = new C03_PI_Camera();

  Servo1 = new PI_Servo(0);

  //pixy = new PI_Pixy(frc::I2C::Port::kOnboard, 8);
=======
  //sensors:
  sensors = new S01_PI_Sensors(); //check the cpp file for sensor definitions

  //setup the drivetrain:
  drivetrain = new S04_PI_Drivetrain(talonL, victorL1, victorL2, talonR, victorR1, victorR2, sensors, positioning);
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7

  //NetworkTable = new S00_PI_Network();
  lift = new S05_PI_Lift(7, liftLimitSwitchId); //create a lift using the talon on CAN 7

  //climb system:
  lFrontPneu = new PI_Pneumatics(PCMID, climb_piston_FL_channel_fwd, climb_piston_FL_channel_rev, climb_piston_FL_reed_retracted, climb_piston_FL_reed_extended);
  rFrontPnue = new PI_Pneumatics(PCMID, climb_piston_FR_channel_fwd,  climb_piston_FR_channel_rev, climb_piston_FR_reed_retracted, climb_piston_FR_reed_extended);
  lBackPneu = new PI_Pneumatics(PCMID, climb_piston_BL_channel_fwd, climb_piston_BL_channel_rev, climb_piston_BL_reed_retracted, climb_piston_BL_reed_extended);
  rBackPnue = new PI_Pneumatics(PCMID, climb_piston_BR_channel_fwd, climb_piston_BR_channel_rev, climb_piston_BR_reed_retracted, climb_piston_BR_reed_extended);


  climbMotor = new C01_PI_Victor(climb_victor_CANID);
  climbSystem = new PI_Climb(lFrontPneu, rFrontPnue, lBackPneu, rBackPnue, climbMotor);

  //grabbing system:
  grabber = new S06_PI_Grabber(GRAB_PCMID, grabber_piston_channel_fwd, grabber_piston_channel_rev, grabber_reed_retracted, grabber_reed_extended, grabber_servo_pin);
  //manual:
  manual = new M00_PI_Manual(drivetrain, input, lift, climbSystem, grabber);

  aiming = new S09_PI_Aim(1, drivetrain);

  autoFunctions = new M01_PI_Auto(grabber, lift, drivetrain, aiming, sensors->PixyDown);

  //network test:
  networkTestID = network->GetEntryId("/test");

  ledArduino = new ArduinoI2C(frc::I2C::Port::kOnboard, 10); //using address 10
  ledArduino->write(ledData, 1);                             //default design
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
  //let the led arduino know teleop is starting:
  *ledData = 3;
  ledArduino->ArduinoI2C::write(ledData, 1); //default design

  manual->init();
}

void Robot::TeleopPeriodic()
{

  sensors->refresh();
  //std::cout << "\nPIXY: " << sensors->PixyDown->BestVector().NearestY() << "\n \n";
  //std::cout<<"winch pos: "<<lift->GetTalonObject()->GetTalonObject()->GetSelectedSensorPosition()<<'\n';
  
  
  //handle user input here:
  //go to the function bellow for more info.
  readUserInput();
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
<<<<<<< HEAD
}

void Robot::TeleopInit() 
{

}
=======
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7

  //positioning update:
  positioning->refresh();

<<<<<<< HEAD
  //drive:
  //drivetrain->drive(input->driver->m_stick->GetY(),input->driver->m_stick->GetX());
  //talonR->GetTalonObject()->Set(ControlMode::PercentOutput, input->driver->m_stick->GetY());
  if (count == 50)
  {
    Servo1->TurnClockwise();
    servo1->AngleControle(0);
    std::this_thread::sleep_for(1s);
    Servo1->TurnCounterClockwise();
    std::this_thread::sleep_for(1s);
    Servo1->AngleControle(180);
    //execute code in here roughly once a second.

    //sensors->refresh();
    //pixy->Update();
    //std::cout << pixy->latestVector->x0;
=======
  //for testing:
  if (count == 50)
  {
    std::cout<<"Pixy X: "<<sensors->PixyDown->LatestVector().NearestX()<<"\n";
    std::cout<<"Pixy Y: "<<sensors->PixyDown->LatestVector().NearestY()<<"\n \n";

    if (autoFunctions->on)
    {
      std::cout << "Auto action happening now \n";
    }

    network->changeValue(networkTestID, networkTest);
    networkTest++;
    //execute code in here roughly once a second.

>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
    //test the Ultrasound sensors:
    //std::cout << "Distance L: " << sensors->USLeft->getDist() << '\n';
    //std::cout << "Distance R: " << sensors->USRight->getDist() << '\n';

    //std::cout << "current coordinates: x:" << positioning->Get()->position->x << " y:" << positioning->Get()->position->y << '\n';
    //std::cout << "current orientation: " << positioning->Get()->rotation->z << '\n';
  }
  count = (count + 1) % 100;
}

void Robot::readUserInput()
{

  //handle all the button presses and function calls here:

  //auto rotate 90 degrees:
  if (input->driver->m_stick->GetTriggerPressed())
  {
    //trigger the rotation:
    std::cout << "trigger pressed \n";
    autoFunctions->autoAimStart();
  }

  if(input->driver->rocketDistance->Get()){
      std::cout<<"Drive to rocket with ultrasound requested \n";
      autoFunctions->ultrasoundDriveRocket();
  }
    if(input->driver->cargoDistance->Get()){
      std::cout<<"Drive to cargo with ultrasound requested \n";
      autoFunctions->ultrasoundDriveCargo();
  }
}

void Robot::TestPeriodic()
{
//Servo1.TurnClockwise();
//std::this_thread::sleep_for(1s);

//std::this_thread::sleep_for(1s);
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
