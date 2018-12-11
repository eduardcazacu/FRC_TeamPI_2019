/*
 * PiDashboard.cpp
 *
 *  Created on: 11 Dec 2018
 *      Author: NickD
 */
#ifndef SRC_PIPOSITION_H_
#define SRC_PIPOSITION_H_

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

	table->PutString("autoMode/selectedMode", "backward");
	table->PutNumber("Gyro Angle", 90);
	table->PutNumber("Jorn/Piet", true);
	//SmartDashboard.putNumber("Gyro Angle", Robot.mecanumDrive.getAngle());
	//xEntry = table->GetEntry("X");
	//dashboardTable.putString("Connection", "connected");

	Refresh();


}

void PiDashboard::Refresh(){
	//dashboardTable.putNumber("match/time", Timer.getMatchTime());
	//table->putNumber("match/time", Timer.getMatchTime());
	//SmartDashboard.putData("Turn on field oriented drive", new DrivetrainGyroOn());
}

#endif
