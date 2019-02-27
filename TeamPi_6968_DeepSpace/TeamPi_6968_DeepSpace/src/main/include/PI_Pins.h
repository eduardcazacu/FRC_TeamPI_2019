#pragma once


const int PCMID = 10;
const int GRAB_PCMID = 11;

const int grabber_piston_channel_fwd = 0;
const int grabber_piston_channel_rev = 1;
const int grabber_reed_extended = 0;
const int grabber_reed_retracted = 1;
const int grabber_servo_pin = 0;

const int climb_piston_FL_channel_fwd = 0;
const int climb_piston_FL_channel_rev = 1;
const int climb_piston_FL_reed_extended = 2;
const int climb_piston_FL_reed_retracted = 3;


const int climb_piston_BL_channel_fwd = 4;
const int climb_piston_BL_channel_rev = 5;
const int climb_piston_BL_reed_extended = 4;
const int climb_piston_BL_reed_retracted = 5;

const int climb_piston_FR_channel_fwd = 2;
const int climb_piston_FR_channel_rev = 3;
const int climb_piston_FR_reed_extended = 2;
const int climb_piston_FR_reed_retracted = 3;

const int climb_piston_BR_channel_fwd = 6;
const int climb_piston_BR_channel_rev = 7;
const int climb_piston_BR_reed_extended = 4;
const int climb_piston_BR_reed_retracted = 5;




const int climb_victor_CANID = 8;


const int liftLimitSwitchId = 9;
//--------------------------------DIO Pins----------------------------
#define END_SWITCH_PNEUMATICS_EX 0
#define END_SWITCH_PNEUMATICS_RE 1
//--------------------------------PWM Pins----------------------------

//-------------------------------Relay Pins---------------------------

//-------------------------------Analog Pins--------------------------
//Ir distance sensors:
#define IR_FRONT 0
#define IR_BACK 1
//---------------------------------Can id------------------------------

//---------------------------------I2C id------------------------------
//ultrasound current sensors
#define US_LEFT 0x40
#define US_RIGHT 0x41

//Arduino for pixy
#define ARDUINO_PIXY 8

//--------------------------------SPI SS pin---------------------------
#define PIXY_ARDUINO_I2C 0x8