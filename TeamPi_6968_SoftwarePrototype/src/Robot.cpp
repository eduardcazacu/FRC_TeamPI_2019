/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <IterativeRobot.h>
#include <Joystick.h>

//Our own libraries
#include <iostream>
#include "PiMovement.h"
#include "PiPowerUp.h"

class Robot: public frc::IterativeRobot {

	//driving:
	PiMovement *piMovement = new PiMovement();

	//functions:
	PiPowerUp *power = new PiPowerUp();

	//tele op:
	frc::Joystick m_stick { 0 };
	frc::Joystick boxStick { 1 };	//second controller for box pickup

	//box pickup:
	bool armState = false, lastButtonValue = false;

	//auto:

public:
	void TeleopPeriodic() {
		// drive with arcade style
		piMovement->move(m_stick.GetY(), m_stick.GetX());

		//handle the intake system for the box
		power->moveBox(boxStick.GetY());
		power->intakeBox(boxStick.GetY());

		//open close arms:
		bool buttonValue = boxStick.GetRawButton(1);

		if (buttonValue == true) {
			armState = !armState;

			//only do this once:
			if (lastButtonValue == false) {
				std::cout << "The state of the arms is" << armState;
				if (armState) {
					//if 1, then open:
					power->openPistons();
				} else {
					//close:
					power->closePistons();
				}
			}
			lastButtonValue = true;

		} else {
			lastButtonValue = false;
		}

	}

	void RobotInit()
	{
	piMovement->init();
	}
};

START_ROBOT_CLASS(Robot)
