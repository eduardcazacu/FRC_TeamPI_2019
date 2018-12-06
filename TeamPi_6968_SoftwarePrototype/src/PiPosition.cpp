/*
 * piPosition.cpp
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 */

#include "PiPosition.h"

PiPosition::PiPosition(PiEncoder *encoders) {
	this->encoders = encoders;

//set defaults:
	dist = 0;
}


PiTransform *PiPosition::Get(){
return this->robot;
}

void PiPosition::updatePosition() {
	double rDist = encoders->distanceRight();
	double lDist = encoders->distanceLeft();

	//find the radius
	double rLeft = ((properties.wheelBase * lDist / rDist)
			/ (1 - (lDist / rDist)));
	double radius = rLeft+properties.wheelBase/2;			//radius of the robot turn

	//find the angle:
	double angl = lDist*360/2*M_PI*rLeft;

	//find the distance travelled
	double distance = 2*M_PI*radius*angl/360;


	//update the variables:
	this->robot->rotation = new PiVector3(robot->rotation->x,robot->rotation->y, robot->rotation->z+angl);
	this->dist+=abs(distance);
}

double PiPosition::getDistance() {
	return this->dist;
}
