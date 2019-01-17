/*
 * PiMPU6050.cpp
 * created on: 6 Dec 2018
 * 		Author: Bas Dieben, Jorn Veenendaal
 */

#ifndef SRC_PIMPU6050_CPP_
#define SRC_PIMPU6050_CPP_

#include "PiMPU6050.h"

#include "WPILib.h"
#include <DigitalInput.h>
#include <DigitalOutput.h>

PiMPU6050::PiMPU6050(int adr){
	//this->MPU_addr = adr;
}

double PiMPU6050::GetCurrent_x_deg(){
	return this->current_x_deg;
}
double PiMPU6050::GetCrurrent_y_deg(){
	return this->current_y_deg;
}
double PiMPU6050::GetCrurrent_Z_deg(){
	return this->current_z_deg;
}
int16_t PiMPU6050::GetAcX(){
	return this->AcX;
}
int16_t PiMPU6050::GetAcY(){
	return this->AcY;
}
int16_t PiMPU6050::GetAcZ(){
	return this->AcZ;
}
int16_t PiMPU6050::GetGyX(){
	return this->GyX;
}
int16_t PiMPU6050::GetGyY(){
	return this->GyY;
}
int16_t PiMPU6050::GetGyZ(){
	return this->GyZ;
}

void PiMPU6050::MPUTrensmision(){
	//if (!(MPUI2C->Transaction(0x3B,14,MPUReseved,14)())){

	//}
}

// t_new still has to be difined.
void PiMPU6050::DataConversionGyro(){
	this->current_x_deg = (this->GyX / 131.0) * (/*t_new */1/1000) + this->current_x_deg;
	this->current_y_deg = (this->GyY / 131.0) * (/*t_new */1/1000) + this->current_y_deg;
	this->current_z_deg = (this->GyZ / 131.0) * (/*t_new */1/1000) + this->current_z_deg;
}


#endif
