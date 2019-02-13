/*
    this class is written for ... the 2019 frc robot of team pi. this clase 
    will make the different actions that the sub system grabber can under take.
    Important actions are: extend, grab, release, retraced'

    Make sure that all the motors are properly connected. and the pneumatic 
    cyllenders have enaugh air

    Created by Jorn Veenendaal 11 of February 2019
    team pi 6869 
*/

#include <C01_PI_Victor.h> 

class S06_PI_Grabber
{
private:
    bool MotorType; // 0 = servo, 1 = dc
    bool CylinderPosition =0; // 0 = retracted, 1 = extended
    int ServoPosition = 90;

    // actuators !edit when classes are clear
    int servo;
    C01_PI_Victor VictorDC;
    int Cylinder;
    
    //standard values
    int ServoservoClosed = 0;
    int ServoStandartOpen   = 180;
    double VictorStatus; 

public:
    /*
        description:    Constructor servo
        Paremeters:     PneumaticValveCanbusID, Motor  
        Output:         -
    */
    S06_PI_Grabber(/* PneumaticValveCanbusID, Servo*/);
   
     /*
        description:    Constructor DcMotor
        Paremeters:     PneumaticValveCanbusID, Motor  
        Output:         -
    */
    S06_PI_Grabber(/* PneumaticValveCanbusID, Victor*/);

    /*
        Description:     Extending gripper 
        Paremeters:      -
        Output:          -
    */
    void ExtendGripper();

    /*
        Description:    Retract gripper
        Parmeters:      -
        Output:         -
    */
    void RetectGripper();

    /*
        Description:    gripper control move the gripper to its disired position(in or out)
        Paremeters:     ServoPosition[-1 = standerd close, -2 standerd open, [0,180]Range in degrees]
        Output:         -
    */
    void clamping(int _servoPosition);

    /*
        Description:    Gripper will switch stats, so retracted will become extended and visa versa
        Paremeters:     -
        Output:         -
    */
    void toggle();

    /*
        Description:    Gripper position is it retracted or extended
        Paremeters:     -
        output:         0 = retracted1 = extended
    */
    bool getGrippercylender();

    /*
        Description:    Get Gripper position is it retracted extended or some were in between
        Parameters:     -
        Output:         -1 = closed, -2 = Standard open, value[0,180] = servo position
    */
    int getClampPosition();
};