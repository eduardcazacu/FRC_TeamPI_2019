/*
 * PiDashboard.h
 *
 *  Created on: 11 Dec 2018
 *      Author: NickD
 */

#ifndef SRC_PIDASHBOARD_H_
#define SRC_PIDASHBOARD_H_

#include "PiRobot.h"
#include "TimedRobot.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"


class PiDashboard{
private:
	static NetworkTable dashboardTable;


public:
	nt::NetworkTableEntry xEntry;
	nt::NetworkTableEntry yEntry;
	nt::NetworkTableEntry angleEntry;
	nt::NetworkTableEntry OpenPiston;

	nt::NetworkTableEntry XDestination;
	nt::NetworkTableEntry YDestination;
	nt::NetworkTableEntry DirDestination;





	/*
	* DESCRIPTION:		Constructor. Creates the object and initializes variables.
	* INPUT:			No parameters at the moment
	* OUTPUT:			Void
	*/
	PiDashboard();

	/*
	* DECRIPTION:		Updates all the variables for the Dashboard.
	* 					This function should always get called
	* INPUT:
	* OUTPUT:			void
	*/
	void Refresh();

};


#endif /* SRC_PIDASHBOARD_H_ */
