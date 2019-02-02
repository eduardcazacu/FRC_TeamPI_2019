/*
 * Pi_Pneumatics.h
 *
 *  Created on: 2 FEB 2019
 *      Author: Bas Dieben
 *
 *      to controle the pneumatics 
 *
 */
#ifndef SRC_PI_PNEUMATICS_H_
#define SRC_PI_PNEUMATICS_H_

#pragma once
#include <WPILib.h>
#include <Solenoid.h>

using namespace frc;

class PI_Pneumatics
{
private: 
 DoubleSolenoid pistons{0,1};


public:

void OpenPiston();
void ClosePiston();
};

#endif