#include "S03_PI_Positioning.h"

S03_PI_Positioning::S03_PI_Positioning(S00_PI_Network *network, C00_PI_Talon *leftEnc, C00_PI_Talon *rightEnc, double drivetrainWidth)
{
    _lEnc = leftEnc;
    _rEnc = rightEnc;

    _pos = new PiTransform();

    _drivetrainWidth = drivetrainWidth;

    this->totalDistance = 0;

    _network = network;

    networkX = _network->GetEntryId("/position/x");
    networkY = _network->GetEntryId("/position/y");
    networkR = _network->GetEntryId("/position/r");
}

void S03_PI_Positioning::refresh()
{
    double rDist = -_rEnc->deltaDistance(); //one of the sides needs to be reversed
    double lDist = _lEnc->deltaDistance();

    //find the distance
    double distance = (rDist - lDist) / 2 + lDist;
    double tempAngle = atan((rDist - lDist) / this->_drivetrainWidth);

    //reset angles
    if (_pos->rotation->z >= 360)
        _pos->rotation->z -= 360;
    else if (_pos->rotation->z <= -360)
       _pos->rotation->z += 360;

    tempAngle = tempAngle * (180.0 / M_PI);
    //add the angle
    this->_pos->rotation->z += tempAngle;


    //x-y position:
    this->_pos->position->y += cos((_pos->rotation->z * M_PI / 180)) * distance;
    this->_pos->position->x += sin((_pos->rotation->z * M_PI / 180)) * distance;

    //add the distance to the total distance:
    totalDistance += distance;

    //update the network:
    _network->changeValue(networkX, _pos->position->x);
    _network->changeValue(networkY, _pos->position->y);
    _network->changeValue(networkR, _pos->rotation->z);
}

PiTransform *S03_PI_Positioning::Get()
{
    return this->_pos;
}

double S03_PI_Positioning::getDistance()
{
    totalDistance;
}
void S03_PI_Positioning::reset(PiTransform newPos)
{
    *_pos = newPos;
}

void S03_PI_Positioning::reset()
{
    _pos->position->x = 0;
    _pos->position->y = 0;
    _pos->position->z = 0;
}