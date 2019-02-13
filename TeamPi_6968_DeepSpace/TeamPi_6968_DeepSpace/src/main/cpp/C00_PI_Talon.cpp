#include "C00_PI_Talon.h"

C00_PI_Talon::C00_PI_Talon(int CanBusDeviceID,  double _CalibrationMultiplication, double kPIDLoopIdx, double kSlotIdx, int _PDPChannel)
{
    this->PiTalon = new WPI_TalonSRX(CanBusDeviceID);
     /*Factory default to make sure that the all settings are set the right way*/
    this->PiTalon->ConfigFactoryDefault();
    this->PiTalon->SetInverted(false); //this is to set the derection of the value, -values or plus values
    
    /*to do setting control mode! how will we define our control input */
    //this->PiTalon->set(ControlMode::PercentOutput,input);

    /*setting up sensors */
    this->PiTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
    this->PiTalon->SetSensorPhase(true); /*value so that motor output and sensor velocity are the same polarity. Do this before closed-looping

    /* Setting up system properties */
    this->rotateRadios = _RotateRadios;
    this->calibrationMultiplication = _CalibrationMultiplication;

    /*PID Setup 
    lets grab the 360 degree position of the MagEncoder's absolute position */
    int absolutePosition = PiTalon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    this->PiTalon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);
}
c00_PI_Talon::c00_PI_Talon(int CanBusDeviceID, double _CalibrationMultiplication, double kPIDLoopIdx = 0, double kSlotIdx = 0,double _kF, double _kP, double _kI, double kD){
    this->PiTalon = new WPI_TalonSRX(CanBusDeviceID);
     /*Factory default to make sure that the all settings are set the right way*/
    this->PiTalon->ConfigFactoryDefault();
    this->PiTalon->SetInverted(false); //this is to set the derection of the value, -values or plus values
    
    /*to do setting control mode! how will we define our control input */
    //this->PiTalon->set(ControlMode::PercentOutput,input);

    /*setting up sensors */
    this->PiTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
    this->PiTalon->SetSensorPhase(true); /*value so that motor output and sensor velocity are the same polarity. Do this before closed-looping

    /* Setting up system properties */
    this->rotateRadios = _RotateRadios;
    this->calibrationMultiplication = _CalibrationMultiplication;

    /*PID Setup 
    lets grab the 360 degree position of the MagEncoder's absolute position */
    int absolutePosition = PiTalon->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    this->PiTalon->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);
//////////////////////////////setup pid ////////////////////////////////////////////////
    /*Setting the current values for the PIDF max and minimum values*/
    this->PiTalon->ConfigNominalOutputForward(0, kTimeoutMs);
    this->PiTalon->ConfigNominalOutputReverse(0, kTimeoutMs);
    this->PiTalon->configPeakOutputForward(1, kTimeoutMs);
    this->PiTalon->configPeakOutputReverse(-1, kTimeoutMs);

    /*Set closed loop Gains so the Kf, Kp, Ki, Kd*/
    this->PiTalon->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
    this->PiTalon->Config_kP(kPIDLoopIdx, 0.1, kTimeoutMs);
    this->Pitalon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
    this->PiTalon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}

void C00_PI_Talon::closedLoopControl(int EncoderSteps)
{
     // 20A current max
    this->PiTalon->set(ControlMode::Current, Vector * 20);
    if(this->setpointEncoders != EncoderSteps){
        this->setpointEncoders = encoderSteps;
        this->encoderPref = this->PiTalon->getSelectedSensorPosition();
    }
    
    /* Position mode - button just pressed */
    //targetPositionRotations = distance / (2 * pi) * 4096;        /* 10 Rotations in either direction */
    
    /*set the amount of encoder steps we would like to make*/ 

    //needs to be tested if it will tget stuk on this line of code or if it will go on 
    Pitalon->Set(ControlMode::Position, EncoderSteps); /* 10 rotations in either direction */
}

bool C00_PI_Talon::Arrived(){
    if(this->encoderPref + this->setpointEncoder<= this->PiTalon->getSelectedSensorPosition()){
        return true;
    }
    else{
        return false;
    }
}
double C00_PI_Talon::ReadEncoder()
{
    this->PiTalon->getPulseWithPosition();
    //this->PiTalon->getSelectedSensorVelocity(); // sensor velocity
    //this->PiTalon->getSelectedSensorPosition(); // sensor position
    //this->PiTalon->getMotorOutputPercent();     // Motor precentage
    //this->PiTalon->SensorOutOfPhase();          // out of phase
    // get the rotation speed of talon.
    this->DeltaT = (NT::Now()-this->PrefTime)/1000; // time in ms
    double magVel_UnitsPer100ms = this->PiTalon->GetSelectedSensorVelocity(0);
    /* convert to RPM */
    // https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
    //MagRPM = magVel [units/kT] * 600 [kTs/minute] / 4096(units/rev), where kT = 100ms
    return this->talonRPM = magVel_UnitsPer100ms * 600 / 4096;

    //ad calibration
    //this->talonRPM = this->calibrationMultiplication * this->talonRPM;
    //this->speed = (2 * 3.14159265359 / 60) * this->talonRPM;
}

WPI_TalonSRX *C00_PI_Talon::GetTalonObject()
{
    return PiTalon;
}

double C00_PI_Talon::GetSpeed()
{
    return this->speed;
}

double C00_PI_Talon::GetAcceleration()
{
    this->acceleration = (this->talonRPM*60/(2*3.1415))/this->deltaT;
    return this->acceleration;
}
double C00_PI_Talon::getTotalEncoderDistance();
/*double C00_PI_Talon::getMotorCurrent(){
    return this->PDPchanel->getCurrent()
}
*/
/*test of Jorn dont look do not take serious */
void C00_PI_Talon::PIDFControl(double Target)
{
    double error = target - this->current;
}

/*Jorns research maybe interesting: 

 Peak Current and Duration must be exceeded before current limit is activated.
When activated, current will be limited to Continuous Current.
Set Peak Current params to 0 if desired behavior is to immediately current-limit. */
//talon.ConfigPeakCurrentLimit(35, 10); /* 35 A */
//talon.ConfigPeakCurrentDuration(200, 10); /* 200ms */
//talon.ConfigContinuousCurrentLimit(30, 10); /* 30A */
//talon.EnableCurrentLimit(true); /* turn it on */



//int sensorPos = 0; // sensor units
//talon.SetSelectedSensorPosition(sensorPos, 0, 10);

//double value = 1; // 1-on, 0-off
//talon.ConfigSetParameter(ParamEnum::eClearPositionOnQuadIdx, value, 0x00, 0x00, 10);
//talon.ConfigSetParameter(ParamEnum::eClearPositionOnLimitF, value, 0x00, 0x00, 10);
//talon.ConfigSetParameter(ParamEnum::eClearPositionOnLimitR, value, 0x00, 0x00, 10);
///* Slot 0 => allowable error = 409 units (10% or a rotation if using CTRE MagEncoder)*/
//talon.ConfigAllowableClosedloopError(0, 409, 10);

// presition or precentageOutput ...
//talon.getSelectedSensorVelocity());
//System.out.println("Sensor Pos:" + _talon.getSelectedSensorPosition());
//System.out.println("Out %" + _talon.getMotorOutputPercent());
//System.out.println("Out Of Phase:" + _faults.SensorOutOfPhase);
