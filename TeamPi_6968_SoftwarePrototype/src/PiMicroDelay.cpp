/*
 * PiUltrasoon.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Jorn Veenendaal
 */

#ifndef SRC_PIMICRODELAY_CPP_
#define SRC_PIMICRODELAY_CPP_

#include <Timer.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <DigitalOutput.h>
#include <DigitalInput.h>

#include "PiMicroDelay.h"
#include "WPILib.h"

//declaration of object with pin Definition Trigger and Echo
PiMicroDelay::PiMicroDelay(){

}

void PiMicroDelay::DelayTime(int Time){
	uint64_t startTimeUsec = nt::Now();

	while((nt::Now()<= startTimeUsec + Time)||(nt::Now()<= startTimeUsec +timeMax));
}

#endif
