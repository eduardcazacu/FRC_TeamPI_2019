

#include "C04_PI_Pixy.h"

C04_PI_Pixy::C04_PI_Pixy(frc::I2C::Port port, int address)
{
  i2cBus = new ArduinoI2C(port, address);
}

void C04_PI_Pixy::Update()
{
  std::cout << "arduino value  ";
  uint8_t check[5];
  i2cBus->read(check, 5);

  PI_Vector* newVector = new PI_Vector(check);
  

  for (int i = 0; i < 5; i++)
    std::cout << (int)check[i] << "\n";
  std::cout << "\n";

  latestVector = newVector;


  if(vectorList->size() != 0){
    for(int i = 0; i<vectorList->size(); i++){
      if(newVector->index == vectorList->at(i).index){
        AddVector(*newVector);
        break;
      }
      if(i == (vectorList->size()-1))
        AddVector(*newVector);
    }
  }
  else{
    AddVector(*newVector);
  }
}

void C04_PI_Pixy::AddVector(PI_Vector vector){
  vectorList->push_back(vector);
  latestVector = &vector;
}