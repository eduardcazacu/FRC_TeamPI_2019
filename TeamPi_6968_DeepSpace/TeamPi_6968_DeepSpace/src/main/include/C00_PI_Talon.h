/*
    this is the PI talon class this class uses the talon librery
    from CTRE/ phoenix and is enriched with pi specific methods
      -  *TravelEncoderSteps(int amount)
      -  *TravelDistance(int amount)
      -  *GetDeltaDistance()
      -  *GetTotalDistance()
      -  *GetSpeed()
      -  *GetAcceleration()
      -  *getTalon()
      x  *this->talon->configContinuousCurrentLimit(amp, ...)
      x  *this->talon->ConfigOpenLoopRamp(...,...)
      x  *set(ControlMode.follower, IDofMotorController)
*/

#pragma once

#define kTimeoutMs 30

#include <ctre/Phoenix.h>
#include <frc/PIDBace.h>
#include <chrono>

//#include "Constance.h"

class C00_PI_Talon
{
  private:
    /*the variables*/
    double totalDistance, deltaDistance, speed, acceleration;
    double calibrationMultiplication, rotateRadios, talonRPM, MotorCurrent;
    int setpointEncoder, encoderPref;
    uint64_t PrefTime = 0;
    uint64_t DeltaT; // time in ms
    WPI_TalonSRX *PiTalon;
    /*can later be added for better control over the motors*/
    //PowerDistributionPanel *PDPChanel;

  public:
    /* Description: constructor 
            Paramaters: CanbusDeviceID[addres on canbus], CalibrationMultiplication[ motor offset] default value = 1, double kPIDLoopIdx = pid configuration can be multipal so selection 0,1,2 standard = 0, double kSlotIdx amount of feedback loops) 
            Returns: -
            Possible addition in the future PDP chanel.
        */
    C00_PI_Talon(int CanBusDeviceID, double _CalibrationMultiplication, double kPIDLoopIdx = 0, double kSlotIdx = 0);

    /*Description: PIDFContstructor if you want to harness the power of the PID control you need initialise these functions
         Parementers:  CanbusDeviceID[addres on canbus], CalibrationMultiplication[ motor offset] default value = 1, double kPIDLoopIdx = pid configuration can be multipal so selection 0,1,2 standard = 0, double kSlotIdx amount of feedback loops, kf, kp, kI,kD)
         returns:      -  
        */
    c00_PI_Talon(int CanBusDeviceID, double _CalibrationMultiplication, double kPIDLoopIdx = 0, double kSlotIdx = 0, double _kF, double _kP, double _kI, double kD);

    /*
            Description:     This method sets the amount of encoder steps to take by the talon it self
            parameters:     Setpoint amount of encoder steps to take 1 full rotation = 4096
            Return:         RPM

        */
    double ReadEncoder();

    /*
        Description:     this function will return true when the motor has reached his set point
        Parameter:       -
        output:         True if reached, false if not reached.
       */
    bool Arrived();
    void closedLoopControl(double setpoint);

    /*
        Returns talon object for wpiLip manipulations
        */
    WPI_TalonSRX *GetTalonObject();
    /* get exeleration of the talons in alpha (rads/s^2)
        */
    double GetAcceleration();

    double getTotalEncoderDistance();

    // double getMotorCurrent();

    /*testing prerpeses*/
    void PIDFControl(double target);
};