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
#include "CANTalon.h"
#include "ctre/Phoenix.h"
#include "Constance.h"

class C00_PI_Talon : public WPI_TalonSRX{
    private:
        /*the variables*/
        double TotalDistance, DeltaDistance, Speed, Acceleration;
        double CalibrationMultiplication, RotateRadios, TalonRPM;
        TalonSRX *PiTalon;
        

    public: 
        /* constructor */
        C00_PI_Talon(int CanBusDeviceID, double _RotateRadios, double _CalibrationMultiplication);
        
        /* Set the amount of encoders that have to turn */
        void TravelEncoderSteps(int amount);

        /* Set a distance to travel */
        void TravelDistance(int amount);

        /*Read the the encoder value and assign and determen delta theta = corner and deltaDistance*/
        void ReadEncoder();        


        TalonSRX GetTalonObject();
        double GetDeltaDistance();
        double GetSpeed();
        double GetAcceleration();
        
};