/*
 * PiGameObject.h
 *
 * Created on: 8 Dec 2018
 * 		Author: NickD
 *
 * 		This object is used to combine all the information for the objects
 */

#ifndef SRC_PIGAMEOBJECT_H_
#define SRC_PIGAMEOBJECT_H_


#include "PiTransform.h"
#include "PiProperties.h"


class PiGameObject{

private:
	//string name;
	PiTransform transform;
	PiProperties properties;

public:
	//constructor:
	PiGameObject( PiTransform transform, PiProperties properties);


};

#endif /* SRC_PIGAMEOBJECT_H_ */
