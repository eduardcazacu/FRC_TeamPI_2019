/*----------------------------------------------------------------------------      */
/*  Copyright (c) 2019 TEAM PI 6968                                                 */
/*  IR sensor class                                                                 */

#pragma once

class PI_IR
{
  private:
    int _roboRioPin;
    int _triggerValue;
    int analogReadIR();

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
};