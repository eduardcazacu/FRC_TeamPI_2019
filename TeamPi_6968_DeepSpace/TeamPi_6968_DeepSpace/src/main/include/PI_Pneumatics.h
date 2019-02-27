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
<<<<<<< HEAD
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
=======
  private:
    int _one; //pin one for controle
    int _two; //pin two for controle

    frc::DigitalInput *_ex;
    frc::DigitalInput *_re;

    frc::DoubleSolenoid *solenoid;

  public:
    /*
    Description:    Constructor. creates a new pneumatic object;
    Input:          PCMID - the ID of the pneumatics control module (We are using multiples);
                    one - forward solenoid;
                    two - reverse solenoid;
                    re = reed switch for extended;
                    ex = reed switch for retracted;

*/
    PI_Pneumatics(int PCMID, int one, int two, int re, int ex);
    void OpenPiston();  //difine function for fully opening the piston
    void ClosePiston(); //difine function for fully closing the piston

    /*
    Description:    Return the state of the piston
    Input:          None;
    Output:         [int] state, -1 = retracted, 1 = extended, 0 = in progress;
    */
    int PistonStatus();
};
>>>>>>> 91d8fd2a66004bb59f268df6619a2b4436bab4e7
