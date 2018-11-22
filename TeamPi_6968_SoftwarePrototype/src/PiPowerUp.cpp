/*
 * PiPowerUp.cpp
 *
 *  Created on: 22 Nov 2018
 *      Author: eddyc
 */

#ifndef SRC_PIPOWERUP_CPP_
#define SRC_PIPOWERUP_CPP_

#include "PiPowerUp.h"

PiPowerUp::PiPowerUp(){

}

void PiPowerUp::moveBox(double speed){
	boxPush1.Set(-speed);
	boxPush2.Set(speed);
}

void PiPowerUp::intakeBox(double speed){
	intake1.Set(-speed);
	intake2.Set(speed);
}

void PiPowerUp::openPistons(){
	pistons.Set(DoubleSolenoid::Value::kForward);
}

void PiPowerUp::closePistons(){
	pistons.Set(DoubleSolenoid::Value::kReverse);
}

#endif /* SRC_PIPOWERUP_CPP_ */
