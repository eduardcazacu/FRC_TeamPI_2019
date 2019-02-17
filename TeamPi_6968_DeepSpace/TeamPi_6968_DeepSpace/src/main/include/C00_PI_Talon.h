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
#include <frc/PIDBase.h>

//#include "Constance.h"

class C00_PI_Talon
{
  private:
    /*the variables*/
    double totalDistance, speed, acceleration;
    double calibrationMultiplication, rotateRadius, talonRPM, MotorCurrent;
    int setpointEncoder, encoderPrev;
    uint64_t PrefTime = 0;
    uint64_t DeltaT; // time in ms
    WPI_TalonSRX *PiTalon;
    /*can later be added for better control over the motors*/
    //PowerDistributionPanel *PDPChanel;
    frc::Timer *tmr;

  public:
    /* Description: constructor 
            Paramaters: CanbusDeviceID[addres on canbus], CalibrationMultiplication[ motor offset] default value = 1, double kPIDLoopIdx = pid configuration can be multipal so selection 0,1,2 standard = 0, double kSlotIdx amount of feedback loops) 
            Returns: -
            Possible addition in the future PDP chanel.
        */
    C00_PI_Talon(int CanBusDeviceID, double _CalibrationMultiplication, double radius, double kPIDLoopIdx = 0, double kSlotIdx = 0);

    /*Description: PIDFContstructor if you want to harness the power of the PID control you need initialise these functions
         Parementers:  CanbusDeviceID[addres on canbus], CalibrationMultiplication[ motor offset] default value = 1, double kPIDLoopIdx = pid configuration can be multipal so selection 0,1,2 standard = 0, double kSlotIdx amount of feedback loops, kf, kp, kI,kD)
         returns:      -  
        */
    C00_PI_Talon(int CanBusDeviceID, double _CalibrationMultiplication, double radius, double _kP, double _kI, double kD, double _kF, double kPIDLoopIdx = 0, double kSlotIdx = 0);

    /*
            Description:    The RPM of the motor
            parameters:     none
            Return:         RPM

        */
    double ReadEncoder();

    /*
        Description:     this function will return true when the motor has reached his set point
        Parameter:       -
        output:         True if reached, false if not reached.
       */
    bool Arrived();

    void closedLoopControl(double encoderRevs);

    /*
        Returns talon object for wpiLip manipulations
        */
    WPI_TalonSRX *GetTalonObject();
    /* get exeleration of the talons in alpha (rads/s^2)
        */
    double GetAcceleration();

    double GetSpeed();

    /*
        Description:    Return the distance travelled since last function call;
                        For precise values it should be called every loop;

        Input:          none;
        Output          [double] distance since last call
    */
    double deltaDistance();
    void SetFPID(double _kP, double _kI, double _kD, double _kF, double kPIDLoopIdx = 0, double kSlotIdx = 0);

    // double getMotorCurrent();

    /*testing prerpeses*/
    void PIDFControl(double target);
};