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
	double distance = (rDist - lDist) / 2 + lDist;
	double tempAngle = atan((rDist - lDist) / properties.wheelBase);

	//reset angles
	if (angle->z >= 360)
		angle->z -= 360;
	else if (angle->z <= -360)
		angle->z += 360;

	tempAngle = tempAngle * (180.0 / M_PI);
	//add the angle
	angle->z += tempAngle;


	//x-y position:
	position->y += cos((angle->z * M_PI / 180)) * distance;
	position->x += sin((angle->z * M_PI / 180)) * distance;

	//add to distance:
	this->dist += abs(distance);
}

void PiPosition::updatePosition() {
	updateEncoderPosition(robot->rotation, robot->position);
}

double PiPosition::getDistance() {
	return this->dist;
}
