/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <IterativeRobot.h>
#include <Joystick.h>
#include <WPILib.h>
#include <CameraServer.h>

#include <DigitalInput.h>
#include <DigitalOutput.h>

//Our own libraries
#include <iostream>
#include "PiMovement.h"
#include "PiPowerUp.h"
#include "PiPosition.h"
#include "PiEncoder.h"
#include "PiUltrasoon.h"
#include "PiMap.h"
#include "PiDashboard.h"
#include "TimedRobot.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

class Robot: public frc::IterativeRobot {
public:

	WPI_TalonSRX * _rEncoder = new WPI_TalonSRX(4);
	WPI_TalonSRX * _lEncoder = new WPI_TalonSRX(2);

	//positioning:
	const double wheelRadius = 76.2f;			//random value for now
	PiEncoder *piEncoder = new PiEncoder(_lEncoder, _rEncoder, wheelRadius);
	PiPosition *position = new PiPosition(piEncoder);

	//functions:
	PiPowerUp *power = new PiPowerUp();
	PiUltrasoon *Ultra1 = new PiUltrasoon(6, 7);

	///driving:
	PiMovement *piMovement = new PiMovement(position);

	//tele op:
	frc::Joystick m_stick { 0 };	//first controller for driving
	frc::Joystick boxStick { 1 };	//second controller for box pickup
	//speed reduction:
	double speedReductionFactor = 0.7;

	//box pickup:
	bool armState = false, lastButtonValue = false;

	//for the dashboard
	PiDashboard *dashboard = new PiDashboard();
	//NetworkTable table;
	//SendableChooser<Command> chooser = new SendableChooser();

	double testX = 0;

	void TeleopPeriodic() {

		// drive with arcade style
		piMovement->move(m_stick.GetY() * speedReductionFactor,
				m_stick.GetZ() * 0.7);

		//box intake:
		intakeSystem();

		// utlrasonic sensor stuf
		/*double c = Ultra1->UltrasoonValue(1, 20);
		 std::cout << "This is the distance in front of ultra1: " << c
		 << std::endl;
		 */

		/*if (leftRPM || rightRPM)
		 std::cout << "Left RPM: " << leftRPM << " Right RPM: " << rightRPM
		 << "\n";
		 */
		if (!piEncoder->calibrate()) {
			//calibrate encoders
		} else {
			position->updatePosition();

			std::cout << "Distance travelled: " << position->getDistance()
					<< "\n";
			std::cout << "angle: " << position->Get()->rotation->z << '\n';
			std::cout << "coordinates: " << position->Get()->position->x
					<< " , " << position->Get()->position->y << "\n";

		}
		dashboard->xEntry.SetDouble(testX++);
		//dashboard->xEntry.SetDouble(position->Get()->position->x);
		dashboard->yEntry.SetDouble(position->Get()->position->y);
		dashboard->angleEntry.SetDouble(position->Get()->rotation->z);

		//refreshed the dashboard values
		dashboard->Refresh();
	}

	void AutoPeriodic() {
		//do auto stuff
	}
	void RobotInit() {

		//Dashboard
		//chooser.addDefault("Open Piston", new changeButtonValue(true));
		//chooser.addDefault("Close Piston", new changeButtonValue(false));
		CameraServer::GetInstance()->StartAutomaticCapture();

		//SmartDashboard.putData("Auto mode", chooser);

		//robot
		piMovement->init();
		dashboard->Refresh();
	}

	void intakeSystem() {
		//all the box intake stuff and pneumatics here:

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
		std::cout << "OpenPiston: " << dashboard->OpenPiston.GetValue()
				<< std::endl;
		if (dashboard->OpenPiston.GetValue()) {
			armState = !armState;
			if (armState) {
				//if 1, then open:
				power->openPistons();
			} else {
				//close:
				power->closePistons();
			}

			dashboard->OpenPiston.SetBoolean(false);
		}
	}

	void changeButtonValue(bool value) {
		lastButtonValue = value;
	}
}
;

START_ROBOT_CLASS(Robot)
