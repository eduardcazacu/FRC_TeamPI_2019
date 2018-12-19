/*
 * PiPathfinding.h
 *
 *  Created on: 18 Dec 2018
 *      Author: NickD
 */

#include "PiPathfinding.h"

PiPathfinding::PiPathfinding(PiMovement *move) {
	this->move = move;
	dy = 0;
	dx = 0;

}

bool PiPathfinding::GoTO(PiPosition * robotPos, PiTransform * destination) {

	bool gotThere = false;

	if (oldX != destination->position->x || oldY != destination->position->y)
		index = 0;

	switch (index) {
	case 0: //calculate de veriables
		oldX = destination->position->x;
		oldY = destination->position->y;
		oldDir = (int) (robotPos->Get()->rotation->z + 360) % 360;
		dx = oldX - robotPos->Get()->position->x;
		dy = oldY - robotPos->Get()->position->y;
		angleToGo = calcAngleToGo(destination->position->x,
				destination->position->y);
		distance = sqrt(pow(dx, 2) + pow(dy, 2));

		index++;
		//no break because it needs to do this always just 1 time
	case 1: //turn around
		if (move->rotate((angleToGo), speed)) {
			index++;
		}
		break;
	case 2: //move forward
		if (move->driveFor(distance, speed)) {
			oldDir = robotPos->Get()->rotation->z;
			index++;
		}
		break;
	case 3: //turn to designated angle
		if (move->rotate(
				(int) (destination->rotation->z - oldDir + 5 * 360) % 360,
				speed)) {
			index++;
		}
		break;
	}
	//case 4:
	//gotThere = true;
	//break;

	return gotThere;
}

double PiPathfinding::calcAngleToGo(double dx, double dy) {
	double angle = atan2(dy, dx) / M_PI * 180 * -1 + 90; //to degrees
	while (angle < 0) {
		angle += 360;
	}
	angle = (int) angle % 360;
	return (angle - oldDir);
}

