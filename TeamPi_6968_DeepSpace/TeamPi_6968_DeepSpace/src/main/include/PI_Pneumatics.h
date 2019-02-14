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
#include <WPILib.h> //include WPILib.h file
#include <DoubleSolenoid.h> //include the DoubleSolenoid.h file
#include <DigitalInput.h> //include the DigitalInput.h file

class PI_Pneumatics//make a class called PI_Pneumatics
{
private: 
int _one;//pin one for controle
int _two;//pin two for controle
int _ex;//extendsion endswitch
int _re;//retraction endswitch

public:
PI_Pneumatics(int one,int two, int re, int ex);
void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
int PistonStatus(); // gives the status of the piston 0 is retrected 1 is extended 2 is neutral
};

