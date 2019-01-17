/*
 * PiPathfinding.h
 *
 *  Created on: 18 Dec 2018
 *      Author: NickD
 */

#ifndef SRC_PIPATHFINDING_H_
#define SRC_PIPATHFINDING_H_

#include "PiRobot.h"
#include "TimedRobot.h"

class PiPathfinding{
private:

	int index = 0;
	float angleToGo = 0;
	float distance = 0;
	float oldX = 0;
	float oldY = 0;
	float oldDir = 0;

	void calcAngleToGo(float dx,float dy);

public:


	PiPathfinding();


	void GoTo(PiRobot * robot, PiPosition * destination);

};


#endif /* SRC_PIPATHFINDING_H_ */

