#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     topLeft,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     topRight,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     bottomRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     bottomLeft,    tmotorTetrix, openLoop)

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
	return;
	// Place motor positioning here ABOVE the return statement duh
}

void movement(int topLeftP, int topRightP, int bottomLeftP, int bottomRightP){
	motor[topLeft] = topLeftP;
	motor[topRight] = topRightP;
	motor[bottomLeft] = bottomLeftP;
	motor[bottomRight]  = bottomRightP;
}

void rotateTime(int power, int direction, int time){
	movement(direction * power, -direction * power, direction * power, -direction * power);
	wait1Msec(time);
	movement(0, 0, 0, 0);
}

void moveTime(int topLeftP, int topRightP, int bottomLeftP, int bottomRightP, int timeInMillis){
	movement(topLeftP, topRightP, bottomLeftP, bottomRightP);
	wait1Msec(timeInMillis);
	movement(0, 0, 0, 0);
}

task main()
{
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.

	moveTime(100, 100, 100, 100, 2000); //goes forward for 2 secs

	while (true)
	{

	}

}
