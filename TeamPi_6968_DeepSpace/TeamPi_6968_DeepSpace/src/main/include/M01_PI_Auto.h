/*
This class defines all the automatic operations that can be done by the robot
Create all objects in the constructor.
For pins and constants use the #define's found bellow the #include's.

Created by Eduard Cazacu on 15 February 2019
Team Pi 6968

*/

#pragma once

//libraries:
#include "S06_PI_Grabber.h"
#include <ctre/Phoenix.h>

//Pins and constants:
#define GRABBER_CONTROLLER_ID 0
#define GRABBER_PISTON_FWD_PIN 0
#define GRABBER_PISTON_REV_PIN 1
//CHANGE THESE!
#define GRABBER_RETRACT_REED_PIN 0
#define GRABBER_EXTEND_REED_PIN 1
//---------------------
#define GRABBER_SERVO_PIN 0
#define START_GRAB_RATIO 0.5
#define GRAB_RATIO_INCREMENT 0.1
#define GRAB_RATIO_LIMIT 1     




//grab sequence states
typedef enum GrabState
{
    grab_idle = 0,
    grab_extend = 1,
    grab_grab = 2,
    grab_secured = 3,
    grab_retract = 4,
    grab_done = 5
} GrabState;

typedef enum PlaceState
{
    place_idle = 0,
    place_extend = 1,
    place_place = 2,
    place_cleared = 3,
    place_retract = 4,
    place_done = 5
} PlaceState;

class M01_PI_Auto
{
  public:
    /*
        Description:    Constructor. Create all the objects needed for auto here.
        Input:          None;
        Output:         none;
    */
    M01_PI_Auto();

    //is there an auto action happening?
    bool on;

    /*
            Description:    This sequence will try to grab the hatch automatically. 
                            Needs to be called periodically until it is done
            Input:          None 
            Output:         [bool] done, optional [bool*] error in grabbing the hatch
        */
    bool grabHatch();
    bool grabHatch(bool *error);

    /*
            Description:    This sequence will place a hatch. Will return an error if no hatch is on
                            Call periodically until done.
            Input:          none
            Output:         [bool] done, optional [bool*] error in placing the hatch

        */
    bool placeHatch();
    bool placeHatch(bool *error);

  private:
    //hatch grabbing:
    S06_PI_Grabber *grabber;
    bool grabbingInProgress;
    GrabState grabState = GrabState::grab_idle;
    bool grabRatio;
    

    //hatch placing:
    bool placingInProgress;
    PlaceState placeState = PlaceState::place_idle;
};
