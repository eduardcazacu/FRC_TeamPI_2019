/*
 * Pi_Pneumatics.h
 *
 *  Created on: 2 FEB 2019
 *      Author: Bas Dieben
 *
 *      to control the pneumatics 
 *
 */
#pragma once
#include <frc/DoubleSolenoid.h> //include the DoubleSolenoid.h file
#include <frc/DigitalInput.h>   //include the DigitalInput.h file

class PI_Pneumatics //make a class called PI_Pneumatics
{
private: 
frc::DoubleSolenoid *_solenoid;
frc::DigitalInput *_extended;
frc::DigitalInput *_retrected;

public:
PI_Pneumatics(int pin1,int pin2, int re, int ex);
void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
int PistonStatus(); // gives the status of the piston 0 is retrected 1 is extended 2 is neutral
};
