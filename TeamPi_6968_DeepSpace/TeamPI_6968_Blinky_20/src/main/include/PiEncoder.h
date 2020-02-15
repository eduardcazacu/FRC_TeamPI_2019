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
#include <frc/WPILib.h>
#include <cmath>
#include <iostream>


#define CAL_READINGS 100

class PiEncoder{
private:
	WPI_TalonSRX *lEnc, *rEnc;
	double *wheelRadius;
	frc::Timer *tmrR = new frc::Timer();
	frc::Timer *tmrL = new frc::Timer();

	double calMulL, calMulR; //calibration
	bool calibrated=true; //don't go into calibration
	const int calReadings = 100; //how many readings before calibration
	int calReadingsMade;
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

	//adjust the calibration values for the two encoders.
	/*
	 * For this to work the robot must be driven in a straight line
	 * it return true when the robot has been calibrated.
	 */
	bool calibrate();

	/*
	 *write calibration multiplier values for the encoders
	 */
	void setCalibration(double calL, double calR);
};


#endif /* SRC_PIENCODER_H_ */
