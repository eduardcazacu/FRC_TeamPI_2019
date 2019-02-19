/*
Control the lift system of the 2019 Team Pi Robot

The system works by moving the grabber carrige using a winch.
The winch is controlled using a Talon SRX with an SRX magnetic encoder.
This allows it to be controlled by a PID loop making the movement precise.

The Target positions are given in absolute motor turns.These are calibrated
and stored as constants in this file.

The start and end position of the lift can be determined using end switches.


Created by Eduard Cazacu on 11 February 2019
Team Pi 6968
*/

#pragma once

//the heights (in rotations) of all the levels from the bottom:

#include "C00_PI_Talon.h"
#include "frc/DigitalInput.h"

#define WINCH_RADIUS 10 //in mm

#define RAMP_T 0.5

class S05_PI_Lift
{
  public:
    /*
            Description:    Constructor. Create a new lift object
            Input:          [uint8_t] talon driver CAN bus address
                            [uint8_t] the digital pin id of the limit switch
            Output:         none          
        */
    S05_PI_Lift(uint8_t talonCAN, uint8_t limitSwitchID);

    /*
            Description:    Go to a certain position using PID
            Input:          [double] position in absolute rotations in relation to the bottom.
            Output:         none;
        */
    void goTo(double pos);

    /*
            Description:    Go to a certain rocket level.
            Input:          [uint8_t] level index (0,1,2) where 0 is ground level
            output:         none

        */
    void goToLvl(uint8_t index);

    /*
            Description:    go down until the limit switch confirms and reset the current position to 0.
                            Needs to be called until it confirms the reset too be done;
            Input:          none;
            Output:         [bool] reset done
        */
    bool reset();

    /*
            Description:    Change the current position of the lift gradually based on the input. It will not 
                            allow the lift to go out of bounds.
            Input:          [double] (-1,1) the rate at which to change the lift position.
            Output:         none
        */
    void adjustPos(double value);

    C00_PI_Talon *GetTalonObject();

  private:
    bool verbose = true;

    const double kp = 2; // p gain ~0.10*halfrotation/900
    const double kf = 0;     // based on system 
    const double ki = 0.0001; // ki ~ kp/100
    const double kd = 8000.00; //kd ~kp * 10 or *100

    const double LVL0 = 2996;
    const double LVL1 = 15276;
    const double LVL2 = 27984;

    const double liftMax = 30000;
    const double liftMin = 0;

    const double resetIncrement = 2;

    double *oldValue;

    //the speed controller + encoder for the winch.
    C00_PI_Talon *winch;
    double *_pos; //the current position of the robot.
    frc::DigitalInput *limitSwitch;
};
