/*
 * PiBuiltInAccelerometer.cpp
 *
 *
 */

#ifndef SRC_PIBUILTINACCELEROMETER_CPP_
#define SRC_PIBUILTINACCELEROMETER_CPP_

#include "PiBuiltInAccelerometer.h"
#include "WPILib.h"
#include "PiMicroDelay.h"

PiMicroDelay *delayA = new PiMicroDelay();
PiBuiltInAccelerometer::PiBuiltInAccelerometer(){
}

void PiBuiltInAccelerometer::Callibaration(){
	double m;
		for(int x = 0; x<200; x++){
			m = m+ this->accel->GetZ();
		}
		this->zconst = m/201;
}
//get functions
double PiBuiltInAccelerometer::Getaxn(){
	return ayn;
}
double PiBuiltInAccelerometer::Getaxo(){
	return ayo;
}
double PiBuiltInAccelerometer::Getayn(){
	return ayn;
}
double PiBuiltInAccelerometer::Getayo(){
	return ayo;
}
double PiBuiltInAccelerometer::Getazn(){
	return azn;
}
double PiBuiltInAccelerometer::Getazo(){
	return azo;
}

void PiBuiltInAccelerometer::Sample(){
	this->gxo = this->gxn;
	this->gyo = this->gyn;
	this->gzo = this->gzn;

	timeO = timeN;

	this->gxn = this->accel->GetX();
	this->gyn = this->accel->GetY();
	this->gzn = this->accel->GetZ();

	std::cout<<"gxn: "<<gxn<<"gyn "<<gyn<<"gzn "<<gzn<<std::endl;
	timeN = nt::Now();
}

void PiBuiltInAccelerometer::SimpleCalculation(){
	this->axo = this->axn;
	this->ayo = this->ayn;
	this->azo = this->azn;
	this->vxo = this->vxn;
	this->vyo = this->vyn;
	this->vzo = this->vzn;

	Sample();

	this->axn = this->gxn*9.81;
	this->ayn = this->gyn*9.81;
	this->azn = this->gzn*9.81;

	this->axnavg = (this->axo+this->axn)/2;
	this->aynavg = (this->ayo+this->ayn)/2;
	this->aznavg = (this->azo+this->azn)/2;

	double dt1 = ((this->timeN)-(this->timeO));
	double dt = dt1/1000000;

	this->vxn = this->axnavg*dt + this->vxo;
	this->vyn = this->aynavg*dt + this->vxo;
	this->vzn = this->aznavg*dt + this->vxo;
	//std::cout<<"this is ax "<<this->azn<<"this is vx"<<this->vzn<< std::endl;

}

void PiBuiltInAccelerometer::AdvancedCalculation(){

	this->axWorldo = this->axWorldn;
	this->ayWorldo = this->ayWorldn;
	this->azWorldo = this->azWorldn;
	this->vxo = this->vxn;
	this->vyo = this->vyn;
	this->vzo = this->vzn;

	Sample();

	this->axn = this->gxn*9.8;
	this->ayn = this->gyn*9.8;
	this->azn = this->gzn*9.8;
	double graphetyisch = 9.8;
	double resultant = roundf(sqrt(pow(axn,2)+pow(ayn,2)+pow(azn,2))*10)/10;
	if (resultant<9.7){
		double graphetyisch = this->azn* cos(this->teta);
		double fzhorizontal = this->azn* sin(this->teta);
		this->xofset = fzhorizontal*cos(this->phi);
		this->xofset = fzhorizontal*sin(this->phi);
	}
	std::cout<<"this is resultant: "<< resultant << std::endl;
	if(resultant > 9.7 && resultant<9.9){
		this->teta = acos(this->azn/9.8);
		this->phi = atan(this->ayn/this->axn);
		this->xofset = axn*cos(phi);
		this->yofset = ayn*sin(phi);
		this->axWorldn = 0;
		std::cout<<"this is the angle Teta: "<<teta<<"this is xofset "<<this->xofset<<std::endl;
		this->axWorldn = 0;
		this->ayWorldn = 0;
	}
	else{
		 if(axn>=0 && ayn >=0){
				//first quadrant
				double Fn = sqrt(pow(resultant,2)-pow(graphetyisch,2));
				if(abs(axn) > abs(xofset)){
					this->axWorldn = sqrt(pow(Fn,2)-pow(this->ayn,2))-this->xofset;
					std::cout<<"this is Fn: "<< Fn << std::endl;
				}
				if(abs(ayn)>abs(yofset)){
					this->ayWorldn = sqrt(pow(Fn,2)-pow(this->axn,2))-this->yofset;
				}
			std::cout<<"this is axWorld: " << this->axWorldn<< '\t'<<"this is ayWorldn: "<<this->ayWorldn<<std::endl;
			}
		 else if(axn< 0 && ayn > 0){
					//second quadrant
					double Fn = sqrt(pow(resultant,2)-pow(graphetyisch,2));
					if(abs(axn)> abs(xofset)){
						this->axWorldn = -(sqrt(pow(Fn,2)-pow(this->ayn,2))-(-1*this->xofset));
						std::cout<<"this is Fn: "<< Fn << std::endl;
					}
					if(abs(ayn)>abs(yofset)){
						this->ayWorldn = sqrt(pow(Fn,2)-pow((this->axn-this->yofset),2));
					}
				std::cout<<"this is axWorld: " << this->axWorldn<< '\t'<<"this is ayWorldn: "<<this->ayWorldn<<std::endl;
		 	 }
		 else if(axn<0 && ayn < 0){
					//third quadrant
					double Fn = sqrt(pow(resultant,2)-pow(graphetyisch,2));
					if(abs(axn) > abs(xofset)){
						this->axWorldn = -(sqrt(pow(Fn,2)-pow(this->ayn,2))-(-1*this->xofset));
						std::cout<<"this is Fn: "<< Fn << std::endl;
					}
					if(abs(ayn)>abs(yofset)){
						this->ayWorldn = -sqrt(pow(Fn,2)-pow((this->axn-this->yofset),2));
					}
				std::cout<<"this is axWorld: " << this->axWorldn<< '\t'<<"this is ayWorldn: "<<this->ayWorldn<<std::endl;
		 	 }
		 else if(axn>0&& ayn<0){
			 //forth quadrant
			 	double Fn = sqrt(pow(resultant,2)-pow(graphetyisch,2));
			 	if(abs(axn)> abs(xofset)){
			 		this->axWorldn = sqrt(pow(Fn,2)-pow(this->ayn,2))-this->xofset;
			 		std::cout<<"this is Fn: "<< Fn << std::endl;
			 		}
			 	if(abs(ayn)>abs(yofset)){
			 		this->ayWorldn = sqrt(pow(Fn,2)-pow((this->axn-this->yofset),2));
			 		}
			 	std::cout<<"this is axWorld: " << this->axWorldn<< '\t'<<"this is ayWorldn: "<<this->ayWorldn<<std::endl;
			 	}
	}
	double sumAx = sumAx + axWorldn;
	double sumAy = sumAy + ayWorldn;


	double dt1 = ((this->timeN)-(this->timeO));
	double dt = dt1/1000000;

	this->vxn = this->axWorldn*dt + this->vxo;
	this->vyn = this->ayWorldn*dt + this->vxo;
	this->vzn = this->azWorldn*dt + this->vxo;

	std::cout<<"this is the sum of acceleration: "<<sumAx<<std::endl;
	std::cout<<"this is the speeeeeeed X "<<this->vxn<<std::endl;
	std::cout<<"this is the speeeeeeed y "<<this->vyn<<std::endl;
	//this->axWorldn = sqrt(pow(resultant,2)-pow(9.81,2));
	//this->axWorldn = sqrt(sqrt(pow(pow(resultant,2)-pow(9.81,2),2)));
	//std::cout<<"this is axworldN "<<axWorldn<< std::endl;
}
/*
 * 1g = 9.81......m/s2
 * dt over eerste meting voorige meting.
 * axo axn
 * vxn= (ax0+axn)/2*dt+vxo
 * vxo is optioneel
 * sxn = ((vxn_vxo)/2)*dt + sxo;
 * sxo is optie
 * vxo = vxn
 *
 *
 */

#endif
