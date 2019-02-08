#include "C00_PI_Talon.h"

C00_PI_Talon::C00_PI_Talon(int CanBusDeviceID, double _RotateRadios, double _CalibrationMultiplication){
    this->PiTalon = new WPI_TalonSRX(CanBusDeviceID); 

    /*setting up sensors */
    this->PiTalon->configSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, KTimeoutMs);
    this->PiTalon->SetSensorPhase(true); /* check this still not sure about seeting */
    this->RotateRadios = _RotateRadios; 
    this->CalibrationMultiplication = _CalibrationMultiplication;

    /*PID Setup*/ 
    /* lets grab the 360 degree position of the MagEncoder's absolute position */
    int absolutePosition = _talon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    this-PiTalon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);
}


C00_PI_Talon::ReadEncoder(){
    // get the rotation speed of talon.
    double magRPM = this->PiTalon->GetSelectedSensorVelocity(0);
    /* convert to RPM */
	// https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
	//MagRPM = magVel [units/kT] * 600 [kTs/minute] / 4096(units/rev), where kT = 100ms
	this->TalonRPM = magVel_UnitsPer100ms * 600 / 4096;

    //ad callibration 
    this->TalonRPM = this->CalibrationMultiplication*this->TalonRPM;
    this->speed = (2*3.14159265359/60)*this->TalonRPM;
    
}

void C00_PI_Talon::TravelEncoderSteps(int amount){
    return TravelEncoderSteps;     
}

void C00_PI_Talon::TravelDistance( int amount){
    return TravelDistance;
}

*TalonSRX C00_PI_Talon::GetTalonObject(){
    return PiTalon;
}

double C00_PI_Talon::GetDeltaDistance(){
    return this->DeltaDistance;
}

double C00_PI_Talon::GetSpeed(){
    return this->Speed;
}

double C00_PI_Talon::GetAcceleration(){
    return this->Acceleration;
}
