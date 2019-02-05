#include "C05_PI_Ultrasoon.h"

C05_PI_Ultrasoon::C05_PI_Ultrasoon(frc::I2C::Port i2c_port, uint8_t address, double rangeMin, double rangeMax)
{
    this->_currentSensor = new Adafruit_INA219(i2c_port, address);

    this->_rangeMin = rangeMin;
    this->_rangeMax = rangeMax;
}
C05_PI_Ultrasoon::C05_PI_Ultrasoon(uint8_t address, double rangeMin, double rangeMax)
{
    this->_currentSensor = new Adafruit_INA219(DEFAULT_PORT, address);

    this->_rangeMin = rangeMin;
    this->_rangeMax = rangeMax;
}

double C05_PI_Ultrasoon::getDist()
{
    //get the current
    double current = getCurrent();
    //by thefault the sensor has a range of 4 to 20 mA maped to 100 to 900mm;
    //use calibration to map:
    return map(current, I_MIN, I_MAX, _rangeMin, _rangeMax);

}

double C05_PI_Ultrasoon::getCurrent()
{
    return (double)_currentSensor->getCurrent_mA();
}

double C05_PI_Ultrasoon::map(double x, double xMin, double xMax, double yMin, double yMax){
    return(yMin+ (x-xMin)*(yMax-yMin)/(xMax-xMin));
}