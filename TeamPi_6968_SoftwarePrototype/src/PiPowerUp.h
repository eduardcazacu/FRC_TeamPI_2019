/*
 * PiPowerUp.h
 *
 *  Created on: 22 Nov 2018
 *      Author: eduard cazacu
 *
 *      All the special functions needed by blinky for the FIRST Power up competition
 *
 *      -opening penumatic box grabber
 *      -loading the boxes
 *      -unloading the boxes
 */

#ifndef SRC_PIPOWERUP_H_
#define SRC_PIPOWERUP_H_

#include <WPIlib.h>
#include <Spark.h>
#include <Solenoid.h>


using namespace frc;

class PiPowerUp{
private:
	Spark intakeR{0};
	Spark intakeL{1};

	Spark boxPushR{2};
	Spark boxPushL{3};

	DoubleSolenoid pistons{0,1};


public:
	/*
	 * DESCRIPTION:		constructor
	 */
	PiPowerUp();

	void openPistons();
	void closePistons();

	/*
	 * DESCRIPTION:		runs the belt system for the box movement inside the robot
	 * INPUT:			double speed - the speed and direction(from the sign) of the intake
	 * OUTPUT:			void
	 */
	void moveBox(double speed);
	/*
	 * DESCRIPTION:		runs spinning wheels at intake
	 * INPUT:			double speed - the speed and direction(from the sign) of the intake
	 * OUTPUT:			void
	 */
	void intakeBox(double speed);
};


#endif /* SRC_PIPOWERUP_H_ */
