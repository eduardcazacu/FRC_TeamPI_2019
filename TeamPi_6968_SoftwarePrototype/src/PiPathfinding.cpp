/*
 * PiPathfinding.h
 *
 *  Created on: 18 Dec 2018
 *      Author: NickD
 */
#ifndef SRC_PIPATHFINDING_H_
#define SRC_PIPATHFINDING_H_

#include "PiPathfinding.h"
#include "PiRobot.h"
#include "PiPosition.h"



PiPathfinding::PiPathfinding()
{
	


}

void PiPathfinding::GoTO(PiRobot * robot, PiPosition * destination){

	if(oldX != destination.x || oldY != destination.y)
      index = 0;



    switch(index){
      case 0: //calculate de veriables
        oldX = destination.x;
        oldY = destination.y;
        oldDir = (robot.dir+360)%360;
		dx = x-robot.x;
		dy = y-robot.y;
        angleToGo = calcAngleToGo(destination.x,destination.y);
        distance = sqrt(pow(dx,2),pow(dy,2));

        index++;
        //no break because it needs to do this always just 1 time
      case 1://turn around
        if(robot.turn(angleToGo)){
          index++;
        }
        break;
      case 2://move forward
        if(robot.drive(distance)){
          oldDir = robot.dir;
          index++;
        }
        break;
      case 3://turn to designated angle
        if(robot.turn((destination.dir-oldDir+5*360)%360)){
          index++;
        }
        break;
    }
}

float PiPathfinding::calcAngleToGo(float dx,float dy){
    var angle = p.atan2(dy,dx)/p.PI*180*-1+90;//to degrees
    while(angle < 0){
      angle += 360;
    }
    angle = angle%360;
    return (angle - oldDir);
  }
}

#endif
