#include "PI_PIDSource.h"

double PI_PIDSource::PIDGet()
{
    return _value;
}

void PI_PIDSource::Set(double value)
{
    this->_value = value;
}