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
#include "PiPosition.h"

PiMovement::PiMovement(){
//constructor

}

void PiMovement::init(){
	//initialise motors with the correct configuration:

	_rightFollower->Follow(*_rightFront);
	//_leftFollower->Follow(*_leftFront);


	/* [3] Adjust inverts so all motor drive in the correction direction */
	_rightFront->SetInverted(false);
	_rightFollower->SetInverted(false);
	//_leftFront->SetInverted(false);
	//_leftFollower->SetInverted(false);

}

void PiMovement::move(double speed, double zRotation){

	m_robotDrive.ArcadeDrive(speed, zRotation);
}


void PiMovement::moveDistance(PiPosition position, double distance){
	switch(this->index){
	case 0:
		this->oldDistance = position.getDistance();
		index++;
		break;
	case 1:
		if(position.getDistance() >= oldDistance){
			index++;
			break;
		}
		this->move(this->speed, 0);
		break;
	case 2:
		this->move(0,0);
		break;
	}
}

