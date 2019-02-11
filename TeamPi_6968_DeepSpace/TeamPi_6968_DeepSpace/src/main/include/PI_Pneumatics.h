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
#include <WPILib.h>
#include <DoubleSolenoid.h>

class PI_Pneumatics
{
private: 
 frc::DoubleSolenoid pistons{0,1};


public:
PI_Pneumatics();
void OpenValve();
void CloseValve();
};

