#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//--------------------------------------------------------------------------------------------------------------------------------//
//
//		TODO LIST:
//
//		1. Add 4 Motor Support
//		2. Configure pragmas for the new motors (motorF and motorG)
//
//--------------------------------------------------------------------------------------------------------------------------------//

#include "JoystickDriver.c" //Joystick is included in this program
int threshold = 10; //to avoid unnecessary movement
int joy1[4], joy2[4];  //controller 1 integers  //controller 2 integers
int mSpeed = 1; //motor speed


bool useAutonomous = true; //should always be true

void motors(int time, int motorDPower, int motorEPower){
	motor[motorD] = motorDPower;
	motor[motorF] = motorDPower;
	motor[motorE] = motorEPower;
	motor[motorG] = motorEPower;
	wait1Msec(time);
	motor[motorD] = 0;
	motor[motorE] = 0;
}

void moveForwardTime(int time, int power){
	motors(time, power, power);
}

void turn90Degrees(int motorspeed){
	motors(1440, 100, 0);
}

void autonomous(){
	//moveForwardTime(5000, 100);
	//turn90Degrees(100);
}

task main()
{
	int threshold = 15; //to avoid unnecessary movement(both controllers)

	/*if(useAutonomous)
	{
		autonomous();
	}*/
	while(true) //infinite loop

	{
		getJoystickSettings(joystick); //retrieves data from the joystick
		joy1[0] = joystick.joy1_x1; // index 0 = x1, 1 = x2, 3 = y1, 4 = y2
		joy1[1] = joystick.joy1_x2;
		joy1[2] = joystick.joy1_y1;
		joy1[3] = joystick.joy1_y2;
		joy2[0] = joystick.joy2_x1;
		joy2[1] = joystick.joy2_x2;
		joy2[2] = joystick.joy2_y1;
		joy2[3] = joystick.joy2_y2;
		if(abs(joy1[2]) > threshold)
		{
			motor[motorD] = (joy1[2] * 100) / 127; //y1 controller moves motorD\
			motor[motorF] = (joy1[2] * 100) / 127;
		}
		else
		{
			motor[motorD] = 0;
			motor[motorF] = 0;
		}
		if(abs(joy1[3]) > threshold)
		{
			motor[motorE] = (joy1[3] * 100) / 127; //y2 controller moves motorE
			motor[motorG] = (joy1[3] * 100) / 127;
		}
		else
		{
			motor[motorE] = 0;
			motor[motorG] = 0;
		}


		/*if(joy1Btn(4) == 1){
			wait1Msec(10);
			servo[servo2] = servo[servo2]-mSpeed;
		} else if(joy1Btn(2) == 1){
			wait1Msec(10);
			servo[servo2] = servo[servo2]+mSpeed;
		} if(joy1Btn(3) == 1){
			wait1Msec(10);
			servo[servo1] = servo[servo1]-mSpeed;
		} else if(joy1Btn(1) == 1){
			wait1Msec(10);
			servo[servo1] = servo[servo1]+mSpeed;
		}*/
	}
}