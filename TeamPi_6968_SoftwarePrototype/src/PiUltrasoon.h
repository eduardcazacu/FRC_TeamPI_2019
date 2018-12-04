/*
 * PiUltrasoon.h
 *
 *  Created on: 1 Dec 2018
 *      Author: Jorn Veenendaal
 *
 *      this library contains contains the functions assosiated with initialising and using a
 *      ultrasonic  sensor.  this version is developed for the HC-SRO4 ultrasonic sensor.
 *
 *		functions are
 *      -initialisation
 *      -get distance in mm with x samples
 */

#ifndef PIULTRASOON_H_
#define PIULTRASOON_H_

#include "WPILib.h"  // i do not jet know if this library is neccisarey but for safety i include it
#include <DigitalInput.h>
#include <DigitalOutput.h>
#include <Timer.h>

class PiUltrasoon{
	//declare all the variables and functions which don't need to be exposed to the main program
	private:
		//object destinction
		//int T = 6;
		//int E = 7;

		// Variables:
		double LastsampleUltra, LastAverageUltra, LastTimeUltra;

		// digital input, output pointer definition.
		frc::DigitalOutput* TriggerPin = new frc::DigitalOutput(6);
		frc::DigitalInput* EchoPin = new frc::DigitalInput(7);

		//declare pins as new objects. T = trigger pin from User decleration E is echopin from user decleration
		//TriggerPin = new frc::DigitalOutput::DigitalOutput(T);
		//EchoPin = new frc::DigitalInput(E);


	public:
		//define all the methods which are needed inside other classes and in the main file.
		//NO VARIABLES SHOULD BE PLACED HERE. Variables should be kept private.

		/*
		 * DESCRIPTION:		Constructor. Creates the object and initializes variables.
		 * INPUT:			Trigger pin and echo pin example: PiUltrasoon(1,2); 1 = trigger pin 2 = echo pin
		 * OUTPUT:			Void
		 */
		PiUltrasoon(int _T, int _E);

		// get functions
		double GetLastAverageUltra();
		double GetLastSampleUltra();
		double GetLastTimeUltra();

		//Set funcitons
		void SetLastAverageUltra(double SetAvg);
		void SetLastSampleUltra(double SetSample);
		void SetLastTimeUltra(double SetTime);

		/*
		 * DESCRIPTION:		Sample function. taks x samples and calculates average
		 * INPUT:			What? amount of samples: example: UltrasoonValue(1,50); 1 = average value 50 samples
		 * 					possibles what's: Avg, 2=Sample, 3=time
		 * OUTPUT:			What value? (double)
		 */
		double UltrasoonValue(int What, int samples);
};
#endif
