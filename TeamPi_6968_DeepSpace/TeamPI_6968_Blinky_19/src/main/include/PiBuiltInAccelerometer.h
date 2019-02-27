/*
 * PIbuiltinaccelerometer.h
 *
 *  Created on: 13 Dec 2018
 *      Author: Bas Dieben
 *
 *      this is a libery for the acceleormeter build in in the RoboRio, the calculations ar based on
 *      what is needed for team pi.
 *
 *		functions are
 *      -get...
 *      -get...
 *      -set...
 */


#ifndef PIBUILTINACCELEROMETER_H_
#define PIBUILTINACCELEROMETER_H_

#include "WPILib.h"  // i do not jet know if this library is neccisarey but for safety i include it
#include <iostream>
#include <cmath>

class PiBuiltInAccelerometer{
	private:
	double gxn,gxo, gyn, gyo,gzn,gzo;
	double axn, axo, ayn, ayo, azn, azo;
	double axnavg, aynavg, aznavg;
	double axWorldn, ayWorldn, azWorldn;
	double axWorldo, ayWorldo, azWorldo;
	double vxn =0, vxo =0 , vyn =0,vyo=0, vzn=0, vzo=0;
	double zconst =1000;
	double teta = 0;
	double phi = 0;
	double yofset = 0;
	double xofset = 0;
	uint64_t timeN = 0;
	uint64_t timeO = 0;
	frc::BuiltInAccelerometer *accel = new frc::BuiltInAccelerometer();

	public:
	double Getaxn();
	double Getaxo();
	double Getayn();
	double Getayo();
	double Getazn();
	double Getazo();
	PiBuiltInAccelerometer();
	void Sample();
	void SimpleCalculation();
	void AdvancedCalculation();
	void Callibaration();

};

#endif
