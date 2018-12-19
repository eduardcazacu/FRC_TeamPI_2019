/*
 * PiDashboard.cpp
 *
 *  Created on: 11 Dec 2018
 *      Author: NickD
 */


#include "PiRobot.h"
#include "PiDashboard.h"
#include "TimedRobot.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"


PiDashboard::PiDashboard()
{
	auto inst = nt::NetworkTableInstance::GetDefault();
	auto table = inst.GetTable("data");

	//table->PutString("autoMode/selectedMode", "backward");
	//table->PutNumber("Gyro Angle", 90);
	//table->PutNumber("Jorn/Piet", true);
	xEntry = table->GetEntry("Position/X");
	yEntry = table->GetEntry("Position/Y");
	angleEntry = table->GetEntry("Position/Angle");
	OpenPiston = table->GetEntry("pistons");
	OpenPiston.SetBoolean(true);

	XDestination = table->GetEntry("Destination/X");
	YDestination = table->GetEntry("Destination/Y");
	DirDestination = table->GetEntry("Destination/Dir");

	/*table.AddEntryListener("pistons", (table,key, entry, value, flags) -> {
		Syst
	}, EntryListenerFlags.kNew | EntryListenerFlags.kUpdate);

	table.AddEntryListener()*/
	Refresh();


}

void PiDashboard::Refresh(){
	//OpenPiston.SetBoolean((bool) table.GetValue("/data/Piston"));
	//dashboardTable.putNumber("match/time", Timer.getMatchTime());
	//table->putNumber("match/time", Timer.getMatchTime());
	//SmartDashboard.putData("Turn on field oriented drive", new DrivetrainGyroOn());
}


