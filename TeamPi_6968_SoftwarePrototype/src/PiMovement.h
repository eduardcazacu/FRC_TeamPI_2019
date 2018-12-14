/*
 * PiMovement.h
 *
 *  Created on: 22 Nov 2018
 *      Author: Eduard Cazacu, Team Pi
 *
 *
 *  This library encloses the PiMovement class which handles all movement of the robot
 *  such as moving forward,backwards, rotate etc.
 *
 *	for each method comment a definition, the input parameters and outputs for clarity and usability.
 *	Keep in mind that no
 *
 */

#ifndef PIMOVEMENT_H_
#define PIMOVEMENT_H_

//dependencies:
#include <Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"
#include <Spark.h>
#include "PiPosition.h"

using namespace frc;

class PiMovement{
private:
	//declare all the variables and functions which don't need to be exposed to the main program

	//motors
	//left side borken, using PWM controllers
	//not ideal but heck
	//WPI_TalonSRX * _leftFront = new WPI_TalonSRX(2);
	//WPI_VictorSPX * _leftFollower = new WPI_VictorSPX(5);

	//right side still using CAN
	WPI_TalonSRX * _rightFront = new WPI_TalonSRX(4);
	WPI_VictorSPX * _rightFollower = new WPI_VictorSPX(3);

	Spark *leftPWM = new Spark(5); //both motors are controlled from the same PWM pin

	frc::DifferentialDrive m_robotDrive{*leftPWM, *_rightFront};
	double speed = 0.1;
	double oldDistance;
	int index = 0;

public:
	//define all the methods which are needed inside other classes and in the main file.
	//NO VARIABLES SHOULD BE PLACED HERE. Variables should be kept private.


	/*
	 * DESCRIPTION:		Constructor. Creates the object and initializes variables.
	 * INPUT:			No parameters at the moment
	 * OUTPUT:			Void
	 */
	PiMovement();

	/*
	 * DECRIPTION:		initialise everything that is needed
	 * INPUT:
	 * OUTPUT:			void
	 */
	void init();

	/*
	 * DESCRIPTION:
	 * INPUT:
	 * OUTPUT:
	 */
	void move(double speed, double zRotation);

	//use this function before you start the moveDistance
	void moveDistance(PiPosition position, double distance);


};

#endif /* PIMOVEMENT_H_ */
