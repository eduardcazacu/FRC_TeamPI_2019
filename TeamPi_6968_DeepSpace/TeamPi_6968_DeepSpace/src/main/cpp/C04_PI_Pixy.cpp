

#include "C04_PI_Pixy.h"

C04_PI_Pixy::C04_PI_Pixy(frc::I2C::Port port, int address, uint8_t _id)
{
  i2cBus = new ArduinoI2C(port, address);
  id = _id;
}

void C04_PI_Pixy::Update()
{
  i2cBus->write(&id, 1);

  //std::cout << "arduino value  ";
  uint8_t check[5];
  i2cBus->read(check, 5);

  PI_Vector *newVector = new PI_Vector(check);
  //newVector->Print();

  AddVector(*newVector);
  if (vectorList.size() > AMOUNTOFVECTORS)
    vectorList.pop_back();

  //std::cout << (int)LatestVector().index << "\n";
}

void C04_PI_Pixy::AddVector(PI_Vector vector)
{
  if (vectorList.empty())
  {
    vectorList.push_back(vector);
  }
  else
  {
    bool found = false;
    for (int i = 0; i < vectorList.size(); i++)
    {
      if (vectorList.at(i).index == vector.index)
      {
        //the vector already exist
        vector.lifeTime = vectorList.at(i).lifeTime + 1;
        vectorList.erase(vectorList.begin() + i);
      }
    }
    vectorList.insert(vectorList.begin(), vector);
  }
}

PI_Vector C04_PI_Pixy::LatestVector()
{
  return vectorList.front();
}

PI_Vector C04_PI_Pixy::BestVector()
{
  PI_Vector bestVector = vectorList.at(0);
  for (int i = 1; i < vectorList.size(); i++)
  {
    if (bestVector.lifeTime < vectorList.at(i).lifeTime)
      bestVector = vectorList.at(i);
  }
  return bestVector;
}

bool C04_PI_Pixy::AimReady(){
  return (BestVector().lifeTime > LIFETIMETRESHHOLD);
}