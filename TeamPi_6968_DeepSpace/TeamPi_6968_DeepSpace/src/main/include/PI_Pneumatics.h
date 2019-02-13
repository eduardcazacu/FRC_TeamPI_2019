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
#include "frc/DoubleSolenoid.h"

class PI_Pneumatics//make a class called PI_Pneumatics
{
private: 
 frc::DoubleSolenoid *piston;

public:

/*
    Constructor:    setup one piston controlled with a double solenoid
    Input:          CAN pneumatics controller channels 
    output:         none
*/
PI_Pneumatics(uint8_t fwd, uint8_t rev);


void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
bool PistonStatus();
};

