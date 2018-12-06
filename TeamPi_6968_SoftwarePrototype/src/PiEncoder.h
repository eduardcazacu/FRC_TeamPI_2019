/*
 * PiEncoder.h
 *
 *  Created on: 4 Dec 2018
 *      Author: eddyc
 */

#ifndef SRC_PIENCODER_H_
#define SRC_PIENCODER_H_

//for tallon
#include "ctre/Phoenix.h"
#include <WPILib.h>
#include <cmath>

class PiEncoder{
private:
	WPI_TalonSRX *lEnc, *rEnc;

	unsigned long lastReading;

	double *wheelRadius;

	Timer *tmr = new Timer();

public:
	//constructor
	PiEncoder(WPI_TalonSRX* lEnc, WPI_TalonSRX* rEnc, double wheelRadius);

	//DESCRIPTION:		Return the raw data from the left encoder:
	//PARAMETERS:
	//RETURN:			[Double] raw data from the encoder
	double RPMLeft();

	//DESCRIPTION:		Return the raw data from the right encoder:
	//PARAMETERS:
	//RETURN:			[Double] raw data from the encoder
	double RPMRight();

	/*DESCRIPTION:		It returns the distance travelled since the last time
						the method has been called assuming the speed was constant.
						To get accurate measurements this should be sampled at very
						small time intervals.

	RETURN:				Distance travelled since last call in mm.
	*/
	double distanceLeft();

	double distanceRight();

};


#endif /* SRC_PIENCODER_H_ */
