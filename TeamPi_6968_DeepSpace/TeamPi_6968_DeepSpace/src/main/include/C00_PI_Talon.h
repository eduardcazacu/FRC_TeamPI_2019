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
//#include "Constance.h"

class C00_PI_Talon{
    private:
        /*the variables*/
        double totalDistance, deltaDistance, speed, acceleration;
        double calibrationMultiplication, rotateRadios, talonRPM;

        WPI_TalonSRX *PiTalon;
        

    public: 
        /* constructor */
        C00_PI_Talon(int CanBusDeviceID, double _RotateRadios, double _CalibrationMultiplication, double kPIDLoopIdx = 0, double kSlotIdx = 0);
        
        /* Set the amount of encoders that have to turn */
        void TravelEncoderSteps(int amount);

        /* Set a distance to travel */
        void TravelDistance(int amount);

        /*Read the the encoder value and assign and determen delta theta = corner and deltaDistance*/
        void ReadEncoder();        


        WPI_TalonSRX* GetTalonObject();
        double GetDeltaDistance();
        double GetSpeed();
        double GetAcceleration();
        
};