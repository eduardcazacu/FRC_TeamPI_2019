/*
 * PiRobot.h
 *
 *  Created on: 6 Dec 2018
 *      Author: eddyc
 */

#ifndef SRC_PIROBOT_H_
#define SRC_PIROBOT_H_


#include "PiVector3.h";

//Store all the robot properties here:
class PiRobot{
private:

public:
	PiRobot();

	const PiVector3 size{600, 870, 0};
	const double wheelBase = 570;


};



#endif /* SRC_PIROBOT_H_ */
