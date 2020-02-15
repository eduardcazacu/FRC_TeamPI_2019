/*
 * PiUltrasoon.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Jorn Veenendaal
 */

#ifndef SRC_PIMICRODELAY_CPP_
#define SRC_PIMICRODELAY_CPP_

#include <frc/Timer.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <frc/DigitalOutput.h>
#include <frc/DigitalInput.h>

#include "PiMicroDelay.h"
#include "frc/WPILib.h"

//declaration of object with pin Definition Trigger and Echo
PiMicroDelay::PiMicroDelay(){

}

void PiMicroDelay::DelayTime(int Time){
	uint64_t startTimeUsec = nt::Now();
	timeMax = 10000;

	while((nt::Now()<= startTimeUsec + Time)||(nt::Now()<= startTimeUsec +timeMax));
}

#endif
