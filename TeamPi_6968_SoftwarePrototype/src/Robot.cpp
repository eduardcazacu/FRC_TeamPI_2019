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
#include <I2C.h>

//Our own libraries
#include <iostream>
#include "PiMovement.h"
#include "PiPowerUp.h"

#include "PiEncoder.h"
#include "PiUltrasoon.h"
#include "MPU9250.h"
#include "PiBuiltInAccelerometer.h"
#include "PiMicroDelay.h"

class Robot: public frc::IterativeRobot {
public:
	//PiBuiltInAccelerometer *A = new PiBuiltInAccelerometer();
	PiMicroDelay *Delay = new PiMicroDelay();

	//driving:
	PiMovement *piMovement = new PiMovement();

	WPI_TalonSRX * _rEncoder = new WPI_TalonSRX(4);
	WPI_TalonSRX * _lEncoder = new WPI_TalonSRX(2);

	//positioning:
	const double wheelRadius = 76.2f;			//random value for now
	PiEncoder *piEncoder = new PiEncoder(_lEncoder, _rEncoder, wheelRadius);

	//functions:
	PiPowerUp *power = new PiPowerUp();
	PiUltrasoon *Ultra1 = new PiUltrasoon(6, 7);
	//MPU9250 *accel = new MPU9250(0x68);
	//PiBuiltInAccelerometer *accelIntern = new PiBuiltInAccelerometer();

	//frc::DigitalOutput* TriggerPin = new frc::DigitalOutput(6);  // chack if this works !
	//frc::DigitalInput* EchoPin = new frc::DigitalInput(7);
	//Ultrasonic *Ultra2 = new Ultrasonic(TriggerPin,EchoPin,Ultrasonic::kMilliMeters);
	//tele op:
	frc::Joystick m_stick { 0 };
	frc::Joystick boxStick { 1 };	//second controller for box pickup
	//speed reduction:
	double speedReductionFactor = 0.7;

	//box pickup:
	bool armState = false, lastButtonValue = false;
	//auto:

	void TeleopPeriodic() {
		// drive with arcade style
		piMovement->move(m_stick.GetY() * speedReductionFactor,
				m_stick.GetX() * 0.7);

		//handle the intake system for the box
		power->moveBox(boxStick.GetY());
		power->intakeBox(boxStick.GetY());

		// utlrasonic sesnor stuf
		double c = Ultra1->UltrasoonMasurment(1,20);
		std::cout << "This is the distance in front of ultra2: " << c << std::endl;
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

		double leftRPM = piEncoder->RPMLeft();
		double rightRPM = -piEncoder->RPMRight();
		if (leftRPM || rightRPM)
			std::cout << "Left RPM: " << leftRPM << " Right RPM: " << rightRPM
					<< "\n";

	}

	void RobotInit() {
		piMovement->init();
		CameraServer::GetInstance()->StartAutomaticCapture();
	}
};

START_ROBOT_CLASS(Robot)
