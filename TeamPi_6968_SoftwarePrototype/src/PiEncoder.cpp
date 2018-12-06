/*
 * PiEncoder.cpp
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 */

#include "PiEncoder.h"

PiEncoder::PiEncoder(WPI_TalonSRX* lEnc, WPI_TalonSRX* rEnc,
		double wheelRadius) {
	//setup everything:
	/* nonzero to block the config until success, zero to skip checking */
	const int kTimeoutMs = 30;

	this->lEnc = lEnc;
	this->rEnc = rEnc;

	//Configure talon to read tachometer values
	this->lEnc->ConfigSelectedFeedbackSensor(
			FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	this->rEnc->ConfigSelectedFeedbackSensor(
			FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);

	this->wheelRadius = new double(wheelRadius);

	tmrL->Start();
	tmrR->Start();
}

double PiEncoder::RPMLeft() {

	// get the velocity of left channle encoder
	double magVel_UnitsPer100ms = this->lEnc->GetSelectedSensorVelocity(0);

	/* convert to RPM */
	// https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
	//MagRPM = magVel [units/kT] * 600 [kTs/minute] / 4096(units/rev), where kT = 100ms
	double magRPM = magVel_UnitsPer100ms * 600 / 4096;

	return magRPM;
}

double PiEncoder::RPMRight() {

	// get the velocity of left channle encoder
	double magVel_UnitsPer100ms = this->rEnc->GetSelectedSensorVelocity(0);

	/* convert to RPM */
	// https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
	//MagRPM = magVel [units/kT] * 600 [kTs/minute] / 4096(units/rev), where kT = 100ms
	double magRPM = magVel_UnitsPer100ms * 600 / 4096;

	return magRPM;
}

double PiEncoder::distanceLeft() {
	//if tmr is off start it (first reading will not be valid)

	//get raw reading:
	double magVel_UnitsPer100ms = this->lEnc->GetSelectedSensorVelocity(0);
	//find out how much of a rotation happens in 1ms:
	double encVel = magVel_UnitsPer100ms / 4096 / 100;

	//find the distance travelled since the last reading in mm:
	double wheelVel = *wheelRadius * 2.0 * M_PI * encVel*tmrL->Get()*1000; //speed in mm/ms
	double dist = wheelVel;

	//reset tmr:
	tmrL->Reset();

	return dist;

}

double PiEncoder::distanceRight() {
	//if tmr is off start it (first reading will not be valid)

	//get raw reading:
	double magVel_UnitsPer100ms = this->rEnc->GetSelectedSensorVelocity(0);
	//find out how much of a rotation happens in 1ms:
	double encVel = magVel_UnitsPer100ms / 4096 / 100;

	//find the distance travelled since the last reading in mm:
	double wheelVel = *wheelRadius * 2.0 * M_PI * encVel*tmrR->Get()*1000; //speed in mm/ms
	double dist = wheelVel;

	//reset tmr:
	tmrR->Reset();

	return dist;

}

