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
<<<<<<< HEAD
#include <WPILib.h> //include WPILib.h file
#include <DoubleSolenoid.h> //include the DoubleSolenoid.h file
#include <DigitalInput.h> 
#include <PI_Pins.h>
=======
#include "frc/DoubleSolenoid.h"
>>>>>>> f0e9bb8107631b7c1f0ae5e62eb79c7e8c217fa7

class PI_Pneumatics//make a class called PI_Pneumatics
{
private: 
<<<<<<< HEAD
int _one;
int _two;
int _ex;
int _re;

public:
PI_Pneumatics(int one,int two, int re, int ex);
=======
 frc::DoubleSolenoid *piston;

public:

/*
    Constructor:    setup one piston controlled with a double solenoid
    Input:          CAN pneumatics controller channels 
    output:         none
*/
PI_Pneumatics(uint8_t fwd, uint8_t rev);


>>>>>>> f0e9bb8107631b7c1f0ae5e62eb79c7e8c217fa7
void OpenPiston();//difine function for fully opening the piston
void ClosePiston();//difine function for fully closing the piston
bool PistonStatus();
};

