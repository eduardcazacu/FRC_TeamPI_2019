#include "C00_PI_Talon.h"

C00_PI_Talon::C00_PI_Talon(int CanBusDeviceID, double _RotateRadios, double _CalibrationMultiplication,double kPIDLoopIdx, double kSlotIdx){
    this->PiTalon = new WPI_TalonSRX(CanBusDeviceID); 

    /*setting up sensors */
    this->PiTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
    this->PiTalon->SetSensorPhase(true); /* check this still not sure about seeting */
    this->rotateRadios = _RotateRadios; 
    this->calibrationMultiplication = _CalibrationMultiplication;

    /*PID Setup*/ 
    /* lets grab the 360 degree position of the MagEncoder's absolute position */
    int absolutePosition = PiTalon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    this-PiTalon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);
}


void C00_PI_Talon::ReadEncoder(){
    // get the rotation speed of talon.
    double magVel_UnitsPer100ms = this->PiTalon->GetSelectedSensorVelocity(0);
    /* convert to RPM */
	// https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
	//MagRPM = magVel [units/kT] * 600 [kTs/minute] / 4096(units/rev), where kT = 100ms
	this->talonRPM = magVel_UnitsPer100ms * 600 / 4096;

    //ad callibration 
    this->talonRPM = this->calibrationMultiplication*this->talonRPM;
    this->speed = (2*3.14159265359/60)*this->talonRPM;
    
}

void C00_PI_Talon::TravelEncoderSteps(int amount){
    //return TravelEncoderSteps;     
}

void C00_PI_Talon::TravelDistance( int amount){
    //return TravelDistance;
}

WPI_TalonSRX* C00_PI_Talon::GetTalonObject(){
    return PiTalon;
}

double C00_PI_Talon::GetDeltaDistance(){
    return this->deltaDistance;
}

double C00_PI_Talon::GetSpeed(){
    return this->speed;
}

double C00_PI_Talon::GetAcceleration(){
    return this->acceleration;
}
