#include <PI_Servo.h>

PI_Servo::PI_Servo(int Channel)
{
    _servo = new frc::Servo(Channel);
}

void PI_Servo::PositionControle(double Position)
{
    _servo->Set(Position);
}

void PI_Servo::AngleControle(double Angle)
{
    _servo->SetAngle(Angle);
}

void PI_Servo::TurnClockwise()
{
    _servo->Set(1);
}

void PI_Servo::TurnCounterClockwise()
{
    _servo->Set(0);
}

double PI_Servo::GetPosition()
{
    return _servo->Get();
}

double PI_Servo::GetAngle()
{
    return _servo->GetAngle();
}

double PI_Servo::tester()
{
    return _servo->GetMaxAngle();
}