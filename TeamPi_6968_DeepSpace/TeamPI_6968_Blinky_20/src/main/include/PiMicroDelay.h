/*
 * PiMicroDelay.h
 *
 *  Created on: 6 Dec 2018
 *      Author: Jorn Veenendaal
 *
 */

#ifndef PIMICRODELAY_H_
#define PIMICRODELAY_H_

#include "frc/WPILib.h"  // i do not jet know if this library is necessary but for safety i include it
#include <frc/Timer.h>

class PiMicroDelay{
private:
	int timeMax = 1000;
public:
	PiMicroDelay();

	void DelayTime(int Time);
};

#endif
