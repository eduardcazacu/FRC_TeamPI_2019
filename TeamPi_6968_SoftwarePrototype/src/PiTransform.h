/*
 * PiTransform.h
 *
 *  Created on: 6 Dec 2018
 *      Author: eddyc
 */

#ifndef SRC_PITRANSFORM_H_
#define SRC_PITRANSFORM_H_

#include "PiVector3.h"

class PiTransform{
private:

public:
PiVector3 *position =  new PiVector3(0,0,0);
PiVector3 *rotation = new PiVector3();
PiVector3 *velocity = new PiVector3();
PiVector3 *acceleration = new PiVector3();
};


#endif /* SRC_PITRANSFORM_H_ */
