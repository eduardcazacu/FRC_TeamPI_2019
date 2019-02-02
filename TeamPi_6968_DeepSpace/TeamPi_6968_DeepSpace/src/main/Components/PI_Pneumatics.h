// daadwerkelijk maken van de klas
//overzicht van je code 
//maak een overzicht van de methodes
//beging met pragma once



#pragma once

class PI_Pneumatics
{
private: 
  dititalInput OpenPin; 
public:
    PI_Pneumatics(int Pneu_pin);
    void OpeningValve();
    
};