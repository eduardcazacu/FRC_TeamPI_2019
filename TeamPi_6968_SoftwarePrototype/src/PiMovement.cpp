/*
 * PiMovement.cpp
 *
 *  Created on: 22 Nov 2018
 *      Author: eddyc
 *
 *	All the cool code goes here. Please comment
 *
 */

#include "PiMovement.h"

PiMovement::PiMovement(PiPosition *positioningObj)
{
	//constructor
	this->position = positioningObj;
	startDistance=startAngle = 0;
	autoDriving=false;
	autoRotating=false;

	goodToGo=true;

}

void PiMovement::init() {
	//initialise motors with the correct configuration:

	_rightFollower->Follow(*_rightFront);
	//_leftFollower->Follow(*_leftFront);

	/* [3] Adjust inverts so all motor drive in the correction direction */
	_rightFront->SetInverted(false);
	_rightFollower->SetInverted(false);
	//_leftFront->SetInverted(false);
	//_leftFollower->SetInverted(false);

}

void PiMovement::move(double speed, double zRotation) {

	m_robotDrive.ArcadeDrive(speed, zRotation);
}

/*
 * DESCRIPTION: go forward a given distance
 * PARAMETERS: 	distance to drive
 * RETURN:		point reached or not.
 */
bool  PiMovement::driveFor(double dist,double speed){
	bool gotThere = false;
	if(!autoDriving){
		//store start position:
		startDistance = position->getDistance();
		autoDriving=true;
	}
	if(goodToGo){
		//if allowed to by obstacle avoidance systems, move:
		move(speed, 0);
	}

	//check if there yet:
	if(position->getDistance() >=startDistance+dist-DIST_TOLERANCE){
		//stop the robot
		move(0, 0);
		gotThere=true;
		autoDriving=false;
	}

	return gotThere;
}

/*
 * DESCRIPTION:	rotate a certain number of degrees
 * PARAMETERS:	degrees to rotate
 * RETURN:		orientation reached or not
 */
bool  PiMovement::rotate(double angle,double speed){
	bool gotThere = false;
	if(!autoRotating){
		//store start position:
		startAngle = position->Get()->rotation->z;;
		autoRotating = true;
	}
	if(goodToGo){
		//if allowed to by obstacle avoidance systems, move:
		move(speed, 0);
	}

	//check if there yet:
	if((angle<0 && position->Get()->rotation->z <= startAngle + angle + ANGL_TOLERANCE) || (angle>=0 && position->Get()->rotation->z >= startAngle + angle - ANGL_TOLERANCE) ){
		//stop the robot
		move(0, speed * (angle/abs(angle)));
		gotThere=true;
		//reset:
		autoRotating = false;
	}

	return gotThere;
}

void PiMovement::pause(){
	goodToGo=false;
}
void PiMovement::resume(){
	goodToGo = true;
}
