/*
 * PiUltrasoon.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Jorn Veenendaal
 */

#ifndef SRC_PIULTRASOON_CPP_
#define SRC_PIULTRASOON_CPP_

#include <Timer.h>
#include <DigitalOutput.h>
#include <DigitalInput.h>
#include <iostream>
#include <ctime>
#include <chrono>

#include "PiUltrasoon.h"
#include "WPILib.h"

//decleration of object with pin Deffinition Trigger and Echo
PiUltrasoon::PiUltrasoon(int _T, int _E){
	//T = _T;
	//E = _E;
}

//get functions
double PiUltrasoon::GetLastAverageUltra(){
	return LastAverageUltra;
}
double PiUltrasoon::GetLastSampleUltra(){
	return LastsampleUltra;
}
double PiUltrasoon::GetLastTimeUltra(){
	return LastTimeUltra;
}

//set functions
void PiUltrasoon::SetLastAverageUltra(double SetAvg){
	LastAverageUltra = SetAvg;
}
void PiUltrasoon::SetLastSampleUltra(double SetSample){
	LastsampleUltra = SetSample;
}
void PiUltrasoon::SetLastTimeUltra(double SetTime){
	LastTimeUltra = SetTime;
}

double PiUltrasoon::UltrasoonValue(int What, int samples){
	//double SampleTotal = 0.0;
	double distance = 0.0;
	double Duration;
	uint64_t endTimeUsec;
	uint64_t startTimeUsec;
	//std::cout<<"this is the status of echo pin at the stard of the for loop:  " << EchoPin->Get()<< std::endl;
	/*for(int x= 0; x < samples; x++)
	{} */
		TriggerPin->Set(0);
		uint64_t startTime = nt::Now();
		while(nt::Now() <= startTime+15);
		TriggerPin->Set(1);
		while(nt::Now() <= startTime+30);
		TriggerPin->Set(0);

		uint64_t Start1 = nt::Now();
		  while ((EchoPin->Get()== 0 )&& (nt::Now() < Start1+ 500))
		  {
		    startTimeUsec = nt::Now();
		    while ( EchoPin->Get() == true);
		     endTimeUsec = nt::Now();
		  }
		Duration = endTimeUsec - startTimeUsec;
		distance = Duration*0.34/2;
	/*	if (Duration < 25){
			Duration = 0;
		}*/
		//distance calculations:
		//std::cout<<"this is the duration of the sample: "<< Duration << std::endl;
		//std::cout<<"this is the durration of the Get loop in p: "<< p <<std::endl;
		//distance = Duration*0.341/2; //Duration *0.000341/2; // d = v*t in mm / 2 for twice the distance
		//SampleTotal = SampleTotal + distance;
		//while(nt::Now() <= startTime+100000);

	//double batchAVG = SampleTotal/samples;
	SetLastAverageUltra(distance);
	SetLastSampleUltra(distance);
	//SetLastTimeUltra(nt::Now()));
	if(What == 1){
		return GetLastAverageUltra();
	}
	else if (What == 2){
		return GetLastSampleUltra();
	}
	else if(What == 3){
		return PiUltrasoon::GetLastTimeUltra();
	}
	else{
		return 10000000;
	}
	return 10;
}
#endif
