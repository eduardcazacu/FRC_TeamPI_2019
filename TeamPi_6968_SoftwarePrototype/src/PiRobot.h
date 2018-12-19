/*
 * PiRobot.h
 *
 *  Created on: 6 Dec 2018
 *      Author: eddyc
 */

#ifndef SRC_PIROBOT_H_
#define SRC_PIROBOT_H_


#include "PiTransform.h"

//Store all the robot properties here:
class PiRobot{
private:
PiTransform *  transform;
public:
	PiRobot();

	const PiVector3 size{600, 870, 0};
	const double wheelBase = 580;

	//PiTransform transform;	//the location/rotation/velocity/acceleration of the robot

};



#endif /* SRC_PIROBOT_H_ */
