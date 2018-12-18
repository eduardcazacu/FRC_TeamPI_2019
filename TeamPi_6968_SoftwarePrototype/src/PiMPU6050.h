/*
 * PIMPU6050.h
 * 	created on: 6 dec 2018
 * 		Author: Bas Dieben, Jorn Veenendaal
 *
 * 		This library contains...
 *
 * 		functions are:
 * 			-
 * 			-
 * 			-
 */

#ifndef PIMPU6050_H_
#define PIMPU6050_H_

//#include <MPU9250.h>
#include <WPILib.h>
#include <DigitalInput.h>
#include <DigitalOutput.h>
#include <I2C.h>


class PiMPU6050{
private:
	int MPU_addr =0x68;
	int I2CPort = 0;
	int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
	unsigned long t_new = 0;
	unsigned long t_old = 0;
	double current_x_deg = 0;
	double current_y_deg = 0;
	double current_z_deg = 0;



	frc::I2C * MPUI2C = new frc::I2C(frc::I2C::kOnboard, this->MPU_addr); //kOnboard = 0-> so this one is conected to the on board special


public:
	// consturctor:
	PiMPU6050(int);
	// the gets:
	double GetCurrent_x_deg();
	double GetCrurrent_y_deg();
	double GetCrurrent_Z_deg();
	int16_t GetAcX();
	int16_t GetAcY();
	int16_t GetAcZ();
	int16_t GetGyX();
	int16_t GetGyY();
	int16_t GetGyZ();

	// the Sets:
	void SetCurrent_x_deg();
	void SetCurrent_y_deg();
	void SetCurrent_z_deg();

	//trensmision
	void MPUTrensmision();

	void DataConversionGyro();

};

#endif
