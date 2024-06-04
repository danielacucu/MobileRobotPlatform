/*
 * DrivingAPIs.c
 *
 *  Created on: May 8, 2024
 *      Author: paul.contis
 */
/*************************************************************************************************************************************************/
#include "DrivingAPIs.h"

/*************************************************************************************************************************************************/
void SoftStart(uint8_t Speed);

static Wheels_t Wheels = {0};
static RotateDir_t Directions = {0};
static Speeds_t Speeds = {0};


/*************************************************************************************************************************************************
 *					                 							APIs implementation
 *************************************************************************************************************************************************/
void DrivingAPIs_LineMove(uint16_t Speed, uint8_t Direction)
{

	ServoSG90_SteeringWheelCtrl(TURN_BACK);
	Wheels.BackLeftWheel = ENABLE;
	Wheels.BackRightWheel = ENABLE;

	if (Direction == FORWARD)
	{
		Directions.RotateBackward.BackLeftWheel = DISABLE;
		Directions.RotateBackward.BackRightWheel = DISABLE;
		Directions.RotateForward.BackLeftWheel = ENABLE;
		Directions.RotateForward.BackRightWheel = ENABLE;

	}
	else if (Direction == BACKWARD)
	{
		Directions.RotateForward.BackLeftWheel = DISABLE;
		Directions.RotateForward.BackRightWheel = DISABLE;
		Directions.RotateBackward.BackLeftWheel = ENABLE;
		Directions.RotateBackward.BackRightWheel = ENABLE;
	}

	Speeds.Speeds.BackLeftWheel = Speed;
	Speeds.Speeds.BackRightWheel = Speed;

	//SoftStart(Speed); //TODO
	HBridge_MotorControl(&Wheels, &Directions, &Speeds);
	//HAL_Delay(1000);
}


void DrivingAPIs_TurnMove(uint16_t Dir, uint8_t Angle, uint16_t Speed)
{


	static uint8_t flag;
	static uint8_t flag2;
	static uint8_t last_Dir;

	/*if(Dir != last_Dir)
			{
				flag2=0;
			}
*/
	if( (Dir != last_Dir)/*&&(flag2<10)*/)
	{
		ServoSG90_SteeringWheelCtrl(Dir);
		last_Dir = Dir;
	}


	Wheels.BackLeftWheel = ENABLE;
	Wheels.BackRightWheel = ENABLE;

	Directions.RotateBackward.BackLeftWheel = DISABLE;
	Directions.RotateBackward.BackRightWheel = DISABLE;
	Directions.RotateForward.BackLeftWheel = ENABLE;
	Directions.RotateForward.BackRightWheel = ENABLE;

	if(Dir == TURN_LEFT)
	{
		Speeds.Speeds.BackLeftWheel = HALF(Speed); // speed/2
		Speeds.Speeds.BackRightWheel = Speed;

	}
	else if(Dir == TURN_RIGHT)
	{
		Speeds.Speeds.BackLeftWheel = Speed;
		Speeds.Speeds.BackRightWheel = HALF(Speed);; // speed/2
	}
	/*else
	{
		Speeds.Speeds.BackLeftWheel = Speed;
		Speeds.Speeds.BackRightWheel = Speed;
	}*/



		HBridge_MotorControl(&Wheels, &Directions, &Speeds);

	/*	if ((flag == 40)&&(last_Dir = Dir))
		{

		ServoSG90_SteeringWheelCtrl(TURN_BACK);
		flag=0;
		flag2 = 0;

		}
		else
		{
			flag++;
			flag2= 20;
		}*/
		//Wheels.BackLeftWheel = DISABLE;
		//Wheels.BackRightWheel = DISABLE;
		//HBridge_MotorStop(&Wheels);

}


void DrivingAPIs_Break(uint8_t BreakType)
{


	switch(BreakType)
	{
	case 1:
		Wheels.BackLeftWheel = BREAK;
		HBridge_MotorStop(&Wheels);
		break;
	case 2:
		Wheels.BackRightWheel = BREAK;
		HBridge_MotorStop(&Wheels);
		break;
	default:
		Wheels.BackLeftWheel = BREAK;
		Wheels.BackRightWheel = BREAK;
		HBridge_MotorStop(&Wheels);
	}

}

/*************************************************************************************************************************************************
 *					                 							Private functions
 *************************************************************************************************************************************************/
void SoftStart(uint8_t Speed) //TODO
{

}
