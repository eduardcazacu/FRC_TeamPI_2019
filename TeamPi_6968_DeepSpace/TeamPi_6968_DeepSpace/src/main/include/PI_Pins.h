#pragma once


const int PCMID = 10;
const int GRAB_PCMID = 10;

const int grabber_piston_channel_fwd = 1;
const int grabber_piston_channel_rev = 0;
const int grabber_reed_extended = 9;
const int grabber_reed_retracted = 8;
const int grabber_servo_pin = 0;

const int climb_piston_F_channel_fwd = 2;
const int climb_piston_F_channel_rev = 3;
const int climb_piston_F_reed_extended = 2;
const int climb_piston_F_reed_retracted = 3;

const int climb_piston_B_channel_fwd = 5;
const int climb_piston_B_channel_rev = 4;
const int climb_piston_B_reed_extended = 5;
const int climb_piston_B_reed_retracted = 4;




const int climb_victor_CANID = 8;


const int liftLimitSwitchId = 0;
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