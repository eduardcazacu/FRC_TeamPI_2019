/*
 * piPosition.h
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 *
 *      This class contains all the methods and variables that have to do with the positioning of the robot.
 */

#ifndef SRC_PIPOSITION_H_
#define SRC_PIPOSITION_H_

#include "PiEncoder.h"
#include "PiVector3.h"
#include "PiTransform.h"
#include "PiRobot.h"

class PiPosition {
private:
	PiTransform* robot = new PiTransform();
	double dist;


	//sensors:
	PiEncoder *encoders;

	//properties:
	PiRobot properties;

public:

	PiPosition(PiEncoder *encoders);
	/*
	 * DESCRIPTION:		Get the distance travelled by the robot.
	 * 					Does not take orientation into account.
	 *
	 */
	double getDistance();
	/*
	 * DESCRIPTION:		Main method. Will check all the sensors.
	 */
	void updatePosition();

	PiTransform *Get();
};

#endif /* SRC_PIPOSITION_H_ */
