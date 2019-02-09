

#include "PI_Pixy.h"

PI_Pixy::PI_Pixy(frc::I2C::Port, int address)
{

  i2cBus = new ArduinoI2C(frc::I2C::Port::kOnboard, 8);
}

void PI_Pixy::Update()
{
  std::cout << "arduino value  ";
  uint8_t check[5];
  i2cBus->read(check, 5);

  PI_Vector newVector(check);
  

  for (int i = 0; i < 5; i++)
    std::cout << (int)check[i] << "\n";
  std::cout << "\n";

  if(vectorList.size != 0){
    for(int i = 0; i<vectorList.size; i++){
      if(index == vectorList.at(i).index){
        vectorList.at(i) = newVector;
        break;
      }
      if(i == (vectorList.size-1))
        vectorList.push_back(newVector);
    }
  }
  else{
    vectorList.push_back(newVector);
  }
}