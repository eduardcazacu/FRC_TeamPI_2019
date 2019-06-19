

#include "C04_PI_Pixy.h"

C04_PI_Pixy::C04_PI_Pixy(frc::I2C::Port port, int address)
{
  i2cBus = new ArduinoI2C(port, address);
}


uint8_t * C04_PI_Pixy::GetBlocks(){
  static uint8_t check[2];
  i2cBus->read(check,2);
  return check;

}

