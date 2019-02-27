/*
This class controls the functions of the climb system. Motors, pistons etc.
Use this in tha Manual class Or in the Auto-> auto class.
The object is to be declared only once in robot.cpp an passed to the other objects
as a pointer!

AVOID CREATING MULTIPLE OBJECTS OF THIS BECAUSE WE ONLY HAVE ONE PHYSICAL CLIMB SYSTEM


Created by Eduard Cazacu on 16 February 2019
Team Pi 6968
*/

#pragma once

#include "PI_Pneumatics.h"
#include "C01_PI_Victor.h"
class PI_Climb
{
public:
  //constants:
  const double rampTime = 0.3;

  /*Description:  Constructor. Creates a new Climb object                 */
  /*Input:        4 pneumatic objects for each piston, one PI_Victor      */
  /*              for the motors.                                         */
  /*Output:       None.                                                   */
  PI_Climb(PI_Pneumatics *LFront, PI_Pneumatics *_RFront, PI_Pneumatics *LBack, PI_Pneumatics *RBack, C01_PI_Victor *motorDriver);

  /*
    Description:    Extend all pistons to lift the whole robot up at the same time.
    Input:          None;
    Output:         None;    
    */
  void extendAll();

  //extend the front pistons
  void extendFront();
  //extend the back pistons
  void extendBack();

  /*
    Description:    Retract all pistons at once to get the whole robot down.
    Input:          None;
    Output:         None;
    */
  void retractAll();

  /*
    Description:    Retract the front pistons.
    Input:          None;
    Output:         None;
   */
  void retractFront();
  /*
    Description:    Retract the back pistons.
    Input:          None;
    Output:         None;
   */
  void retractBack();

  /*
    Get the state of the pistons. -1 = retracted, 0 = unknown, 1 extended
    */
  int getAll();
  /*
    Get the state of the front pistons. -1 = retracted, 0 = unknown, 1 extended
    */
  int getFront();
  /*
    Get the state of the back pistons. -1 = retracted, 0 = unknown, 1 extended
    */
  int getBack();

  /*
    Description:    Drive both motors with a certain speed.
    Input:          [double ]Speed (-1,1)
    POutput:        none;
    */
  void drive(double speed);

private:
  PI_Pneumatics *_LFront;
  PI_Pneumatics *_RFront;
  PI_Pneumatics *_LBack;
  PI_Pneumatics *_RBack;

  C01_PI_Victor *_motorDriver;
};