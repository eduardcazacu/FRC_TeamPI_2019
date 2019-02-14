
#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include <iostream>
#include <vector>



/*

1.First ask for an ID and store it (The String is the location in the table just like your file explorer)
2.Use this id together with your veriable to update the networkTable

//example:

int networkID;

setup(){
    networkID = networkTable->GetEntryId("/test");
}
loop(){
    number++;
    networkTable->changeValue(networkID,number);
}


*/

class S00_PI_Network{

    private:

    static NetworkTable* dashboardTable;
    std::vector<nt::NetworkTableEntry> entries;
    

    public:

    S00_PI_Network();

    //put in your location (You can use "/" in the string to add an sub location)
    //it returns the id of the entry
    int GetEntryId(std::string location);

    //change the value of the entry
    void changeValue(int id,double value);

    //get the value of the entry
    double getValue(int id);
    

};