/*
 * PiTransform.cpp
 *
 *  Created on: 6 Dec 2018
 *      Author: eddyc
 */



#include "PiTransform.h"

PiTransform::PiTransform(){
	this->position =  new PiVector3();
	this->rotation = new PiVector3();
	this->velocity = new PiVector3();
	this->acceleration = new PiVector3();
}
PiTransform::PiTransform(PiVector3 posiion){
	this->position =  new PiVector3(position.x,position->y,position.z);
	this->rotation = new PiVector3();
	this->velocity = new PiVector3();
	this->acceleration = new PiVector3();
}
PiTransform::PiTransform(PiVector3 position, PiVector3 rotation)
{
	this->position =  new PiVector3(position.x,position.y,position.z);
	this->rotation = new PiVector3(rotation.x,rotation.y,rotation.z);
	this->velocity = new PiVector3();
	this->acceleration = new PiVector3();
}
