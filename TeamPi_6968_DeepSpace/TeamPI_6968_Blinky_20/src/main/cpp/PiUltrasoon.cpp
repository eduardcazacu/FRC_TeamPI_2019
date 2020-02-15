/*
 * PiUltrasoon.cpp
 *
 *  Created on: 1 Dec 2018
 *      Author: Jorn Veenendaal
 */

#ifndef SRC_PIULTRASOON_CPP_
#define SRC_PIULTRASOON_CPP_

#include <frc/Timer.h>
#include <frc/DigitalOutput.h>
#include <frc/DigitalInput.h>
#include <iostream>
#include <ctime>
#include <chrono>

#include "PiUltrasoon.h"
#include "frc/WPILib.h"

//decleration of object with pin Deffinition Trigger and Echo
PiUltrasoon::PiUltrasoon(int _T, int _E){
	this->TriggerPin = new frc::DigitalOutput(_T);  // chack if this works !
	this->EchoPin= new frc::DigitalInput(_E);
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

double PiUltrasoon::UltrasoonMasurment(int what, int Samples){
	double AllSamples[Samples];
	int SampleSum;
	for(int x= 0; x < Samples; x++){
			// sending pulse
			this->TriggerPin->Set(0);
			uint64_t startTime = nt::Now();
			while(nt::Now() <= startTime+15);
			this->TriggerPin->Set(1);
			while(nt::Now() <= startTime+30);
			this->TriggerPin->Set(0);

			// detecting pulse
			uint64_t endTimeUsec;
			uint64_t startTimeUsec;
			uint64_t Start1 = nt::Now();
			while ((EchoPin->Get()== 0 )&& (nt::Now() < Start1+ 500)){
			    startTimeUsec = nt::Now();
			    while (EchoPin->Get() == true);
			    endTimeUsec = nt::Now();
			   }
			double Duration = endTimeUsec - startTimeUsec;
			AllSamples[x]= Duration/58;
	}

	for(int y=0; y<Samples; y++){
		SampleSum = SampleSum+ AllSamples[y];
	}
	double average = SampleSum/Samples;
	double PrevAvg;
	for(int z = 0; z< this->arrSize; z++){
		if(this->previousValues[z] == 0){
			previousValues[z] = 50;
		}
		PrevAvg += this->previousValues[z];
	}
	PrevAvg = PrevAvg/this->arrSize;
	if(average == 0){
		average = PrevAvg;
	}
	if(average > 400){
		average = PrevAvg;
	}

	//updating prev value
	double RememberPrevVal = average;
	for(int w = 0; w<this->arrSize; w++){
		double valNow = this->previousValues[w];
		this->previousValues[w] = RememberPrevVal;
		RememberPrevVal = valNow;
	}
	if(average < PrevAvg*0.5||average>PrevAvg*1.5){
		return PrevAvg;
	}
	return average;
}

bool PiUltrasoon::UltrasoonObject(double Distance){
	std::cout << UltrasoonMasurment(1,1) << '\n';
	if(UltrasoonMasurment(1,1) < Distance){
		return true;
	}
	else{
		return false;
	}
}

double PiUltrasoon::UltrasoonValue(int What, int samples){
	double SampleTotal = 0.0;
	double distance = 0.0;
	double Duration;
	unsigned int p= 0; // error provention variable
	uint64_t endTimeUsec;
	uint64_t startTimeUsec;
	//std::cout<<"this is the status of echo pin at the stard of the for loop:  " << EchoPin->Get()<< std::endl;
	for(int x= 0; x < samples; x++)
	{
		p++;
		// sending pulse
		this->TriggerPin->Set(0);
		uint64_t startTime = nt::Now();
		while(nt::Now() <= startTime+15);
		this->TriggerPin->Set(1);
		while(nt::Now() <= startTime+30);
		this->TriggerPin->Set(0);

		// detecting pulse
		uint64_t Start1 = nt::Now();
		  while ((EchoPin->Get()== 0 )&& (nt::Now() < Start1+ 500))
		  {
		    startTimeUsec = nt::Now();
		    while (EchoPin->Get() == true);
		     endTimeUsec = nt::Now();
		  }

		//calculating distance
		Duration = endTimeUsec - startTimeUsec;

	    distance =(Duration*0.34)/2;

		// error correction.
		// false reading
		if ((Duration < 25)||(Duration > 1000))
		{
			x--;
		}
		// if all the reading are false this will profent it of getting stuk in the loop
		if (p >= samples*1.1)
		{
			x= samples;
		}

		//std::cout<<"this is the duration of the sample: "<< Duration << std::endl;
		//std::cout<<"this is the durration of the Get loop in p: "<< p <<std::endl;
		SampleTotal = SampleTotal + distance;
		}
	//end of samples, average calculation
	double batchAVG = SampleTotal/samples;

	// assigning values
	SetLastAverageUltra(batchAVG);
	SetLastSampleUltra(distance);
	SetLastTimeUltra(nt::Now());

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
}
#endif
