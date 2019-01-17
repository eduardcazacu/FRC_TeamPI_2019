/*
 * piVector3.cpp
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 */

#include <PiVector3.h>

//setup the variables
PiVector3::PiVector3(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

PiVector3::PiVector3(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
