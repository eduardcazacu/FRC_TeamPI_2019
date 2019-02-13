/*
 * Pi_Pneumatics.h
 *
 *  Created on: 2 FEB 2019
 *      Author: Bas Dieben
 *
 *      to controle the pneumatics 
 *
 */
#pragma once
#include <WPILib.h> //include WPILib.h file
#include <DoubleSolenoid.h> //include the DoubleSolenoid.h file
#include <DigitalInput.h> 
#include <PI_Pins.h>

class PI_Pneumatics//make a class called PI_Pneumatics
{
private: 
int _one;
int _two;
int _ex;
int _re;

public:
PI_Pneumatics(int one,int two, int re, int ex);
void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
bool PistonStatus();
};

