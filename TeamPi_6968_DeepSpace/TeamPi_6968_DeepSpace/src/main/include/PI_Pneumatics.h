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

class PI_Pneumatics//make a class called PI_Pneumatics
{
private: 
 frc::DoubleSolenoid pistons{0,1};//difine the output pins for the solonoids

public:
PI_Pneumatics();
void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
void PistonStatus();
};

