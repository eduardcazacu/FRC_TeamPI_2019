/*----------------------------------------------------------------------------      */
/*  Copyright (c) 2019 TEAM PI 6968                                                 */
/*  IR sensor class                                                                 */

#pragma once

#include <frc/AnalogInput.h>

#define IR_DIST_THRESHOLD  500          //IR sensor step detection threshold

class PI_IR
{
  private:
    frc::AnalogInput* _analogInput; //the analog pin
    int _triggerValue;    //value at which to consider or not an object detected


    int analogReadIR(void);   //helper function for reading the analog pin

  public:
    // Constructor
    /*  input:  pin [int] the pin to which the IR sensor is connected               */
    /*          triggerValue [int][0,1023] = the default value at which an object   */
    /*          is considered to be in range.                                       */
    /*  Output: none                                                                */
    PI_IR(int pin, int triggerValue);

    /*  Description:    check if there is anything in front of the IR sensor        
        Input:          triggerValue[int] = the threshold for detecting an object 
        Output:         object in range? [bool]
    */
    bool objectInRange(int triggerValue);
    bool objectInRange();

    /*  Description:    change the default trigger value
        Input:          int triggerValue [0,1023]
        Output:         void
    */
    void setTRiggerValue(int triggerValue);
};