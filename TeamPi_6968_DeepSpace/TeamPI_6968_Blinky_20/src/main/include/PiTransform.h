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
PiVector3 *position;
PiVector3 *rotation;
PiVector3 *velocity;
PiVector3 *acceleration;

PiTransform();
PiTransform(PiVector3 position);
PiTransform(PiVector3 position, PiVector3 rotation);
};




#endif /* SRC_PITRANSFORM_H_ */
