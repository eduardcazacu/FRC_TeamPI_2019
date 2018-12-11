/*
 * piPosition.cpp
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 */

#include "PiPosition.h"
#include <math.h>

PiPosition::PiPosition(PiEncoder *encoders) {
	this->encoders = encoders;

//set defaults:
	dist = 0;
}

PiTransform *PiPosition::Get() {
	return this->robot;
}

void PiPosition::updateEncoderPosition(PiVector3 *angle, PiVector3 *position) {
	double rDist = -encoders->distanceRight();	//on blinky this one is reversed
	double lDist = encoders->distanceLeft();

	//find the distance
	double distance = (lDist - rDist) / 2 + rDist;
	double tempAngle = atan((lDist - rDist) / properties.wheelBase);
	tempAngle = tempAngle * (180.0 / M_PI);

	//reset angles
	if (angle->z >= 360)
		angle->z -= 360;
	else if (angle->z <= -360)
		angle->z += 360;

	//add the angle
	angle->z += tempAngle;

	//x-y position:
	position->y += sin(tempAngle)*distance;
	position->x += cos(tempAngle)*distance;

	//add to distance:
	this->dist += abs(distance);
}

void PiPosition::updatePosition() {
	updateEncoderPosition(robot->rotation, robot->position);
}

double PiPosition::getDistance() {
	return this->dist;
}
