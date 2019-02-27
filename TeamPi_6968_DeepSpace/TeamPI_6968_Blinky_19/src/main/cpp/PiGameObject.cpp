/*
 * PiGameObject.h
 *
 * Created on: 8 Dec 2018
 * 		Author: NickD
 *
 */

#include <PiGameObject.h>

PiGameObject::PiGameObject( PiTransform transform, PiProperties properties){
	/*this->name = name;*/
	this->transform = transform;
	this->properties = properties;
}
