/*
    this class is written for ... the 2019 frc robot of team pi. this clase 
    will make the different actions that the sub system grabber can under take.
    Important actions are: extend, grab, release, retraced'

    Make sure that all the motors are properly connected. and the pneumatic 
    cyllenders have enaugh air

    Created by Jorn Veenendaal 11 of February 2019
    team pi 6869 
*/
#pragma once

#include "C01_PI_Victor.h"
#include "frc/DoubleSolenoid.h"
#include <frc/AnalogInput.h>
#include "frc/Servo.h"
#include <frc/DigitalInput.h>

#define SERVO_FULL_GRIP 0.85
#define SERVO_FULL_RELEASE 0.2


//bellow which value do we condider the hatch in a safe position. (12 bit values)
#define GRAB_SENSOR_THRESHOLD 3500

class S06_PI_Grabber
{
  private:
    bool motorType =0;      // 0 = servo, 1 = dc
    bool pistonPos = 0;     // 0 = retracted, 1 = extended
    bool gripState = 0;     // 0 = released, 1 = extended 

    bool usePressureSensor = 0;    //does the system use a pressure sensor

    frc::DigitalInput *_retractedReed;
    frc::DigitalInput *_extendedReed;

    frc::DoubleSolenoid *_piston;
    frc::Servo *_servo;
    C01_PI_Victor *_victor;
    frc::AnalogInput *_pressureSensor; //the pressure sensor.

  public:
    /*
        description:    Constructor servo
        Paremeters:     PneumaticValveCanbusID, fwd channel, reverse channel,Motor  
        Output:         -
    */
    S06_PI_Grabber(int moduleID,int fwdID,int revID,int retractedReedPin,int extendedReedPin, int servoPin, int forceSensorPin);
    S06_PI_Grabber(int moduleID,int fwdID,int revID,int retractedReedPin,int extendedReedPin, int servoPin);

    /*
        description:    Constructor DcMotor
        Paremeters:     PneumaticValveCanbusID,fwd channel, reverse channel, Motor  
        Output:         -
    */
    S06_PI_Grabber(int moduleID,int fwdID,int revID,int retractedReedPin,int extendedReedPin, C01_PI_Victor *victor, int forceSensorPin);
    S06_PI_Grabber(int moduleID,int fwdID,int revID,int retractedReedPin,int extendedReedPin, C01_PI_Victor *victor);

    /*
        Description:     Extending gripper 
        Paremeters:      -
        Output:          -
    */
    void extendGripper();

    /*
        Description:    Retract gripper
        Parmeters:      -
        Output:         -
    */
    void retractGripper();

    /*
        Description:    Gripper will switch stats, so retracted will become extended and visa versa
        Paremeters:     -
        Output:         -
    */
    void toggleArm();

    /*
        Description:    Gripper position is it retracted or extended
        Paremeters:     -
        output:         -1 = retracted, 0= in motion,1 = extended
    */
    int getArm();
    /*
        Description:    gripper the hatch
        Paremeters:     [double] servo position (0..1). Where 1 is the largest circumference.
        Output:         -
    */
    void grip(double ratio);
    void grip();

    /*
        Description:    release the hatch
        Paremeters:     -
        Output:         -
    */
    void release();

    /*
        Description:    Get grabber status. Is it open closed etc.
        Parameters:     -
        Output:         -1 = closed, -2 = Standard open, value[0,1] = gripper rate
    */
    int getGripper();

    /*
        Description:    Check if the hatch is secured or still on the grabber
        Parameters:     none
        Return:         secured state. True = on , false =off;
    */
    bool hatchSecured();
};