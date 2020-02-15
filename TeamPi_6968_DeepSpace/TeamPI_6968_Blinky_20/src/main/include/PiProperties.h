/*
 * PiProperties.h
 *
 * Created on: 8 Dec 2018
 * 		Author: NickD
 *
 * 		This object is used to combine all the properties that the gameobjects can have
 */

#ifndef SRC_PIPROPERTIES_H_
#define SRC_PIPROPERTIES_H_


class PiProperties{

private:


public:
	bool 	pickable,	//can we pick the object up?
			dynamic;	//will it go away if we drive into it?

	//constructor:
	PiProperties();		//default settings

};

#endif /* SRC_PIPROPERTIES_H_ */
