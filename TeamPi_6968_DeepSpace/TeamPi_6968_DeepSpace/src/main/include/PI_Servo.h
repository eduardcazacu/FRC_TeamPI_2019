/*
 * Pi_Servo.h
 *
 *  Created on: 13 march 2019
 *      Author: Bas Dieben
 *
 *      To controle the servo
 *
 */
#pragma once
#include <frc/WPILib.h> //include WPILib.h file

class PI_Servo
{
    private:
    frc::Servo *_servo;//difine an object

    public:
    PI_Servo(int Chanel);//constructor (output pin for controling the servo)
    void PositionControle(double pos);//controling the servo with a value between 1 and 0
    void AngleControle(double Angle);//controling the servo with an angle
    void TurnClockwise();//turn max clockwise
    void TurnCounterClockwise();//turn max counterclockwise
    double GetPosition();//Returns the position given with a number between 1 and 0
    double GetAngle();//Returns the angle of the servo 

    double tester();

};