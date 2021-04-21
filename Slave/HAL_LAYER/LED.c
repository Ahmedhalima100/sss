/*
 * LED.c
 *
 *  Created on: Apr 17, 2021
 *      Author: ahmed Halima
 *      */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include  "LED.h"
#define PORT_NO DIO_PORTA

void HAL_TURN_ON_LED_1(){
	      MCAL_DIO_u8SetPinDir(DIO_PORTD,led1,1);
	      MCAL_DIO_u8SetPinValue(DIO_PORTD,led1,1);
}
void HAL_TURN_OFF_LED_1(){
	       MCAL_DIO_u8SetPinDir(PORT_NO,led1,1);
		   MCAL_DIO_u8SetPinValue(DIO_PORTD,led1,0);}
void HAL_TURN_ON_LED_2(){
			MCAL_DIO_u8SetPinDir(DIO_PORTD,led2,1);
			MCAL_DIO_u8SetPinValue(DIO_PORTD,led2,1);
}
void HAL_TURN_OFF_LED_2(){
			MCAL_DIO_u8SetPinDir(PORT_NO,led2,1);
			MCAL_DIO_u8SetPinValue(DIO_PORTD,led2,0);
}
void HAL_TURN_ON_LED_3(){
			MCAL_DIO_u8SetPinDir(DIO_PORTD,led3,1);
			MCAL_DIO_u8SetPinValue(DIO_PORTD,led3,1);
}
void HAL_TURN_OFF_LED_3(){
			MCAL_DIO_u8SetPinDir(PORT_NO,led3,1);
			MCAL_DIO_u8SetPinValue(DIO_PORTD,led3,0);
}
