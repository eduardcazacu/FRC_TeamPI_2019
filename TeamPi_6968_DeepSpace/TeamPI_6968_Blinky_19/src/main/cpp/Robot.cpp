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
#include <frc/I2C.h>

//Our own libraries
#include <iostream>
#include "PiMovement.h"
#include "PiPowerUp.h"
#include "PiPosition.h"
#include "PiEncoder.h"
#include "PiUltrasoon.h"
#include "MPU9250.h"
#include "PiBuiltInAccelerometer.h"
#include "PiMicroDelay.h"
#include "PiMap.h"
#include "PiDashboard.h"
#include "TimedRobot.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "PiPathfinding.h"


class Robot: public frc::IterativeRobot {
public:

	WPI_TalonSRX * _rEncoder = new WPI_TalonSRX(4);
	WPI_TalonSRX * _lEncoder = new WPI_TalonSRX(2);

	//positioning:
	const double wheelRadius = 76.2f;			//random value for now
	PiEncoder *piEncoder = new PiEncoder(_lEncoder, _rEncoder, wheelRadius);
	PiPosition *position = new PiPosition(piEncoder);

	//PiBuiltInAccelerometer *A = new PiBuiltInAccelerometer();
	PiMicroDelay *Delay = new PiMicroDelay();

	//functions:
	PiPowerUp *power = new PiPowerUp();
	PiUltrasoon *Ultra1 = new PiUltrasoon(0, 1);
	//MPU9250 *accel = new MPU9250(0x68);
	//PiBuiltInAccelerometer *accelIntern = new PiBuiltInAccelerometer();

	//frc::DigitalOutput* TriggerPin = new frc::DigitalOutput(6);
	//frc::DigitalInput* EchoPin = new frc::DigitalInput(7);
	//Ultrasonic *Ultra2 = new Ultrasonic(TriggerPin,EchoPin,Ultrasonic::kMilliMeters);

	///driving:
	PiMovement *piMovement = new PiMovement(position);

	//tele op:
	frc::Joystick m_stick { 0 };	//first controller for driving
	frc::Joystick boxStick { 1 };	//second controller for box pickup



	//auto stuff:
    PiPathfinding *pathfinding = new PiPathfinding(piMovement);
    PiTransform *autoTarget;

    PiTransform *autoTarget0 = new PiTransform(PiVector3(0, 1000, 0),
            PiVector3(0, 0, 0));
    PiTransform *autoTarget1 = new PiTransform(PiVector3(500, 1000, 0),
            PiVector3(0, 0, 0));
    PiTransform *autoTarget2 = new PiTransform(PiVector3(500, 2000, 0),
                PiVector3(0, 0, 0));
    PiTransform *autoTarget3 = new PiTransform(PiVector3(0, 3000, 0),
                   PiVector3(0, 0, 0));

	int nOfTargets = 2;
	int currentTarget = 0;

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
		if(m_stick.GetThrottle() > 0.5){
			piMovement->move(m_stick.GetY() * speedReductionFactor, m_stick.GetZ() * 0.65);
		}
		else{
			piMovement->move(m_stick.GetY() * speedReductionFactor, m_stick.GetX()*0.65);
		}
		//box intake:
		intakeSystem();

		// utlrasonic sensor stuf
			//double c = Ultra1->UltrasoonMasurment(1, 1);
			//std::cout << "This is the distance in front of ultra1: " << c << std::endl;
		std::cout<<"Object: "<<Ultra1->UltrasoonObject(10)<<std::endl;
		positioningStuff();
	}

	void positioningStuff() {
			if (!piEncoder->calibrate()) {
				//calibrate encoders
			} else {
				/*double leftRPM = piEncoder->RPMLeft();
				 double rightRPM = piEncoder->RPMRight();

				 if (leftRPM || rightRPM)
				 std::cout << "Left RPM: " << leftRPM << " Right RPM: " << rightRPM
				 << "\n";

				 */
				position->updatePosition();
				/*
				 std::cout << "Distance travelled: " << position->getDistance()
				 << "\n";
				 std::cout << "angle: " << position->Get()->rotation->z << '\n';
				 std::cout << "coordinates: " << position->Get()->position->x
				 << " , " << position->Get()->position->y << "\n";
				 */

			}
			//dashboard->xEntry.SetDouble(testX++);
			dashboard->xEntry.SetDouble(position->Get()->position->x);
			dashboard->yEntry.SetDouble(position->Get()->position->y);
			dashboard->angleEntry.SetDouble(position->Get()->rotation->z);

			//refreshed the dashboard values
			dashboard->Refresh();
		}

	void AutonomousInit() {
			autoTarget = autoTarget0;
		}

	void AutonomousPeriodic() {
			positioningStuff();
			//do auto stuff
			//piMovement->autoMove(0, 0.2);
			//std::cout << Ultra1->UltrasoonObject(30) << '\n';
			/*if(Ultra1->UltrasoonObject(20)){	//in centimeters
				piMovement->pause();
			}
			else{*/
				piMovement->resume();


				if (pathfinding->GoTO(position, autoTarget)) {
					std::cout << "Going new places \n";
					//go to next target:
					currentTarget++;
				}
			//}

			switch (currentTarget) {
			case 0:
				autoTarget = autoTarget0;
				break;
			case 1:
				autoTarget = autoTarget1;
				break;
			case 2:
				autoTarget = autoTarget2;
				break;
			case 3:
				autoTarget = autoTarget3;
				break;
			default:
				break;

			}


			/*pathfinding->GoTO(position, new PiTransform(PiVector3(dashboard->XDestination, dashboard->YDestination, 0),
		            PiVector3(0, 0, 0))))*/

		}
	void RobotInit() {

		//Dashboard
		//chooser.addDefault("Open Piston", new changeButtonValue(true));
		//chooser.addDefault("Close Piston", new changeButtonValue(false));
		CameraServer::GetInstance()->StartAutomaticCapture(0);

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

		// utlrasonic sesnor stuf
		//double c = Ultra1->UltrasoonMasurment(1,20);
		//std::cout << "This is the distance in front of ultra2: " << c << std::endl;
		//accel->readSensor();
		//double W = accel->getAccelX_mss();
		//std::cout << "This is the x of the accelerometer: "<< W << std::endl;

		//std::cout<<"this is acceleration in X: "<< accel2->GetX()<<'\n' <<"this is accelerometer Y: "<<accel2->GetY()<<'\n'<<"this is accelerometer Z: "<<accel2->GetZ()<< std::endl;

		//accelIntern->AdvancedCalculation();

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
		/*
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
		}*/
	}

	void changeButtonValue(bool value) {
		lastButtonValue = value;
	}
}
;

START_ROBOT_CLASS(Robot)
