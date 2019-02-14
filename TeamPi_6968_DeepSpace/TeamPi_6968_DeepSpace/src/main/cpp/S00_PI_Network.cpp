
#include "S00_PI_Network.h"


S00_PI_Network::S00_PI_Network(){

}

int S00_PI_Network::GetEntryId(std::string path){
    auto inst = nt::NetworkTableInstance::GetDefault();
	auto table = inst.GetTable("data");
    nt::NetworkTableEntry entry = table->GetEntry(path);
    entries.push_back(entry);
    return (entries.size() - 1);
}

void S00_PI_Network::changeValue(int id,double value){
    entries.at(id).SetDouble(value);
}

double S00_PI_Network::getValue(int id){
    entries.at(id).GetValue();
}