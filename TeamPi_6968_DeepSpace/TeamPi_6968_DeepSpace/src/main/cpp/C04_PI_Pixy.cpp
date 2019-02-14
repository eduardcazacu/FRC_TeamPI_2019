

#include "C04_PI_Pixy.h"

C04_PI_Pixy::C04_PI_Pixy(frc::I2C::Port port, int address)
{
  i2cBus = new ArduinoI2C(port, address);
}

void C04_PI_Pixy::Update()
{
  //std::cout << "arduino value  ";
  uint8_t check[5];
  i2cBus->read(check, 5);

  PI_Vector* newVector = new PI_Vector(check);
  //newVector->Print();
  
  AddVector(*newVector);
  if(vectorList.size()>AMOUNTOFVECTORS)
    vectorList.pop_back();

  std::cout<<(int)LatestVector().index<<"\n";
  //LatestVector().Print();
  /*
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
  }*/
}

void C04_PI_Pixy::AddVector(PI_Vector vector){
  if(vectorList.empty()){
    vectorList.push_back(vector);
  }
  else{
    bool found = false;
    for(int i = 0; i<vectorList.size(); i++){
      if(vectorList.at(i).index==vector.index){
        //the vector already exist
        vectorList.erase(vectorList.begin()+i);
      }
    }
    vectorList.insert(vectorList.begin(),vector);
  }
}

PI_Vector C04_PI_Pixy::LatestVector(){
  return vectorList.front();
}