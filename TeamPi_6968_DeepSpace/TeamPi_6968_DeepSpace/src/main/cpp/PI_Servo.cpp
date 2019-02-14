#include <PI_Servo.h>

PI_Servo::PI_Servo(int Channel)
{
    Pin = Channel;
}

void PI_Servo::PositionControle(double Position)
{
    frc::Servo(Pin).Set(Position);
}

void PI_Servo::AngleControle(double Angle)
{
    frc::Servo(Pin).SetAngle(Angle);
}

void PI_Servo::TurnClockwise()
{
    frc::Servo(Pin).Set(1);
}

void PI_Servo::TurnCounterClockwise()
{
    frc::Servo(Pin).Set(0);
}

double PI_Servo::GetPosition()
{
    return frc::Servo(Pin).Get();
}

double PI_Servo::GetAngle()
{
    return frc::Servo(Pin).GetAngle();
}