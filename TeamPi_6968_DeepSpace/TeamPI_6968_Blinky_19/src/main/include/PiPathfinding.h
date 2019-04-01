/*
 * PiPathfinding.h
 *
 *  Created on: 18 Dec 2018
 *      Author: eddyc
 */

#ifndef SRC_PIPATHFINDING_H_
#define SRC_PIPATHFINDING_H_

#include "TimedRobot.h"
#include "PiRobot.h"
#include "PiPosition.h"
#include "PiTransform.h"
#include "PiMovement.h"
#include <math.h>

class PiPathfinding {
private:

	int index = 0;
	float angleToGo = 0;
	float distance = 0;
	float oldX = 0;
	float oldY = 0;
	float oldDir = 0;
	double dx, dy;

	double calcAngleToGo(double dx, double dy);

	PiMovement *move;

	double speed = 0.2;

public:

	PiPathfinding(PiMovement *move);

	bool GoTO(PiPosition * robotPos, PiTransform * destination);

};

#endif /* SRC_PIPATHFINDING_H_ */
