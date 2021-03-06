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
#include "S07_PI_AutoClimb.h"
#include "S05_PI_Lift.h"
#include "S04_PI_Drivetrain.h"
#include "C04_PI_Pixy.h"
#include "S09_PI_Aim.h"
#include <iostream>

#define GRABBER_SERVO_PIN 0
#define START_GRAB_RATIO 0.5
#define GRAB_RATIO_INCREMENT 0.1
#define GRAB_RATIO_LIMIT 1

#define GRABBER_TIMEOUT 3   //how long before proceeding to the next state in case of sensor failure
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

typedef enum PlaceOnLvlState
{
    POL_idle = 0

} PlaceOnLvlState;

class M01_PI_Auto
{
  public:
    /*
        Description:    Constructor. Create all the objects needed for auto here.
        Input:          None;
        Output:         none;
    */
    M01_PI_Auto(S06_PI_Grabber *grabber, S05_PI_Lift *lift, S04_PI_Drivetrain *drivetrain, S09_PI_Aim *aiming, C04_PI_Pixy *pixy);

    /*
        Description:    Call this periodically. It handles the auto operations when 
                        requested
        Input:          none
        Output:         none;
    */
    void functions();
    /*
        Description:    Reset all functions to their default states and positions
        Input:          none;
        OutputL         none;
    */
    void reset();

    //is there an auto action happening?
    bool on;
    /*
        Description:    call this method to enable the grabHatch sequence;
        Input:          None;
        Output:         None;
    */
    void grabHatchEnable();
    /*
        Reset the hatch grabbing sequence;
        It will move all mechanisms to default position
    */
    void grabHatchReset();

    /*
        Description:    call this method to enable the placeHatch sequence;
        Input:          None;
        Output:         None;
    */
    void placeHatchEnable();
    /*
        Reset the hatch placing sequence;
        It will move all mechanisms to default position
    */
    void placeHatchReset();

    /*
        Description:    Complete sequence to place a hatch on a certain level:
        Input:          [int] level. Bottom level is 0
        Output:         none'
    */
    void placeHatchOnLevel(int lvl);

    /*
        Description:    Start the auto aiming sequence;
        Input:          none;
        Output:         none;
    */
    void autoAimStart();
    void rotateDegreesEnable(double angle);

    /*
        Description:    Drive the robot to the correct distance from the game piece:
        Input:          none
        Output:         none;
    */
   void ultrasoundDriveRocket();
   void ultrasoundDriveCargo();

  private:
    //timeoutTimer
    frc::Timer *timeOutTmr;

    //hatch grabbing:
    S06_PI_Grabber *grabber;
    bool grabbingInProgress;
    GrabState grabState = GrabState::grab_idle;
    bool grabRatio;

    /*
            Description:    This sequence will try to grab the hatch automatically. 
                            Needs to be called periodically until it is done
            Input:          None 
            Output:         [bool] done, optional [bool*] error in grabbing the hatch
        */
    bool grabHatch();
    bool grabHatch(bool *error);

    //hatch placing:
    bool placingInProgress;
    PlaceState placeState = PlaceState::place_idle;

    /*
            Description:    This sequence will place a hatch. Will return an error if no hatch is on
                            Call periodically until done.
            Input:          none
            Output:         [bool] done, optional [bool*] error in placing the hatch

        */
    bool placeHatch();
    bool placeHatch(bool *error);

    /*
        Description:    The routine being periodically called waiting to be activated
        Input:          int target level.
        Output:         [bool] done
    */
    bool placeHatchOnLevelRoutine(int lvl);

    //drivetrain
    S04_PI_Drivetrain *_drivetrain;
    bool rotateDegrees();

    bool _rotationDone = true;
    double _rotationAngle;

    //lift:
    bool liftResetDone = false;
    S05_PI_Lift *_lift;

    //auto aim:
    C04_PI_Pixy *_pixy;
    S09_PI_Aim *_aiming;
    bool autoAimDone = true;
    bool autoAim();

    //allign with ultrasound:
    const double distToCargo = 335;
    const double distToRocket = 200;
    /*
        Description:    drive with ultrasound to a certain distance
        Input:          the target distance from the object
        Output:         done?

    */
    bool ultrasoundDrive();
    double targetUltrasoundDist;
    bool ultrasoundDriveDone = false;
};
