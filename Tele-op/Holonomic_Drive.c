#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     topLeft,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     topRight,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     bottomRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     bottomLeft,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

// NOTE: Some of to most of this code was made on npp, so the pragmas couldn't be setup and the selection of motors will likely change when a complete prototype of a bidirectional/holonomic drive robot has been built. - Nate

int speed; // Speed of the robot, used as a multiplier for speed. Should be positive
int threshold; // the "dead zone" of the controller joysticks

// All constant variables go here
const int FULLSPEED = 100; // a constant value for the maximum speed for the robot. Since this code doesn't have a precision mode, (yet), we only need fullspeed as a speed constant. Not neseccary at the moment, but will be later.
const int PRECISIONMODESPEED = 10; // for precise movement!

//Initialize Variables
void initializeVariables(){
	speed = FULLSPEED; // In the start of the program, the speed is the maximum.
	threshold = 10; // Just to keep unescessary movement.
}

// this is run before the main loop, to intitialize things for startup I. E. set servos to preffered starting positions
void initializeRobot(){
	initializeVariables();
}

// main method for movement.
void movement(int x1, int y1, int x2, int y2){
	// we are only using x2 and y2 for the actual movement, x1 and y1 are for rotation. Optional, but reccomended and usef	ul.
	if(abs(y2) > threshold || abs(x2) > threshold || abs(x1) > threshold && joy1Btn(8) == 0){ // make sure joystick is not in dead zone. I know, it only checks y2, but it is long a tedious to check for more, I'll do it later. ------------------------------------TODO-----------------------------------------------------------
		speed = FULLSPEED;
		motor[topLeft] = ((y2 * speed) / 127) + ((x1 * speed) / 127) + ((x2 * speed) / 127);		// ATTENTION!!!! THIS IS NOT WORKING CODE! THIS IS JUST FOR EASIER CODING WHEN THE PROTOTYPE IS DONE! SAME FOR CODE BELOW!
		motor[topRight] = ((y2 * speed) / 127) - ((x1 * speed) / 127) - ((x2 * speed) / 127);
		motor[bottomLeft] = ((y2 * speed) / 127) + ((x1 * speed) / 127) - ((x2 * speed) / 127);
		motor[bottomRight] = ((y2 * speed) / 127) - ((x1 * speed) / 127) + ((x2 * speed) / 127);
	}
	else if(abs(y2) > threshold || abs(x2) > threshold || abs(x1) > threshold && joy1Btn(08) == 1){ // Is the same as the above if statement, but also detects precsion mode
		speed = PRECISIONMODESPEED;
		motor[topLeft] = ((y2 * speed) / 127) + ((x1 * speed) / 127) - ((x2 * speed) / 127);		// ATTENTION!!!! THIS IS NOT WORKING CODE! THIS IS JUST FOR EASIER CODING WHEN THE PROTOTYPE IS DONE! SAME FOR CODE BELOW!
		motor[topRight] = ((y2 * speed) / 127) + ((x1 * speed) / 127) + ((x2 * speed) / 127);
		motor[bottomLeft] = ((y2 * speed) / 127) - ((x1 * speed) / 127) + ((x2 * speed) / 127);
		motor[bottomRight] = ((y2 * speed) / 127) - ((x1 * speed) / 127) - ((x2 * speed) / 127);
	} else {
		motor[topLeft] = 0;
		motor[topRight] = 0;
		motor[bottomLeft] = 0;
		motor[bottomRight] = 0;
	}
}

//same movement methods, but with parameters for power instead of joystick position
void movementPower(int topRightP, int topLeftP, int bottomRightP, int bottomLeftP){

		motor[topRight] = topRightP;	// ATTENTION!!!! THIS IS NOT WORKING CODE! THIS IS JUST FOR EASIER CODING WHEN THE PROTOTYPE IS DONE! SAME FOR CODE BELOW!
		motor[topLeft] = topLeftP;
		motor[bottomRight] = bottomRightP;
		motor[bottomLeft] = bottomLeftP;
}

// Autonomous Methods go here

void moveForward(int power){
	movementPower(100, 100, 100, 100);
}

void stopMotors(bool stopTopRight, bool stopTopLeft, bool stopBottomRight, bool stopBottomLeft){
	if(stopTopRight){
		motor[topRight] = 0;
	}
	if(stopTopLeft){
		motor[topLeft] = 0;
	}
	if(stopBottomRight){
		motor[bottomRight] = 0;
	}
	if(stopBottomLeft){
		motor[bottomLeft] = 0;
	}
}

task main(){
	initializeRobot();

	while(true){
		getJoystickSettings(joystick); // this should be run before joystick detection, since, well, the whole tele-op depends on the joystick.
		int y1 = joystick.joy1_y1; int y2 = joystick.joy1_y2; int x1 = joystick.joy1_x1; int x2 = joystick.joy1_x2; // Makes joystick positions easier to use
		movement(x1, y1, x2, y2); // Pass the joystick coordinates to movement method

		// The whlie loop doesnt need to be THAT fast... and it makes processing faster
		wait1Msec(1);
	}

}
